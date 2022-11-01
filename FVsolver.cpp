//
// Created by Matt Blomquist on 10/27/22.
//

#include "FVsolver.h"
#include "math.h"

void FVsolver::solve(std::vector<double> &solution) {
    // get spacing
    double dx = grid.get_dx();
    double dy = grid.get_dy();

    // initialize right-hand side
    rhs.assign(grid.get_nb_of_nodes(), 0.);
    for (int n = 0; n <= grid.get_nb_of_nodes(); n++) {
        // start building the discretization at the node n
        // for edge cases, subtract half a cell
        double xmin = grid.i_from_n(n) == 0 ? grid.x_from_n(n) : grid.x_from_n(n) - dx / 2.;
        double xmax = grid.i_from_n(n) == grid.get_N() - 1 ? grid.x_from_n(n) : grid.x_from_n(n) + dx / 2;
        double ymin = grid.j_from_n(n) == 0 ? grid.y_from_n(n) : grid.y_from_n(n) - dy / 2.;
        double ymax = grid.j_from_n(n) == grid.get_M() - 1 ? grid.y_from_n(n) : grid.y_from_n(n) + dy / 2;
        // compute area at the four corners of cell
        double volume = compute_area((*levelset)(xmin, ymin),
                                     (*levelset)(xmax, ymin),
                                     (*levelset)(xmin, ymax),
                                     (*levelset)(xmax, ymax),
                                     (xmax-xmin), (ymax-ymin));

        // fill in matrix row by row
        // f -> \int_{V_n} \approx |V_n| f(x_n, y_n)
        matrix.add_element(n, n, alpha * volume);
        rhs[n] = volume * (*forcing_term)(grid.x_from_n(n), grid.y_from_n(n));

        // Left boundary
        if (grid.i_from_n(n) == 0)
            rhs[n] += (*boundary_term)(xmin, grid.y_from_n(n)) * compute_length(ymax-ymin, (*levelset)(xmin, ymin), (*levelset)(xmin, ymax));
        else { // Not on left boundary
            // left neighbor n_l
            int nl = grid.n_from_ij(grid.i_from_n(n) - 1, grid.j_from_n(n));
            double len = compute_length(ymax-ymin, (*levelset)(xmin, ymin), (*levelset)(xmin, ymax));
            matrix.add_element(n, nl, -mu * len / dx);
            matrix.add_element(n, n, mu * len / dx);
        }
        // Right boundary
        if (grid.i_from_n(n) == grid.get_N() - 1)
            rhs[n] += (*boundary_term)(xmax, grid.y_from_n(n)) * compute_length(ymax-ymin, (*levelset)(xmax, ymin), (*levelset)(xmax, ymax));
        else {
            int nr = grid.n_from_ij(grid.i_from_n(n) + 1, grid.j_from_n(n));
            double len = compute_length(ymax-ymin, (*levelset)(xmax, ymin), (*levelset)(xmax, ymax));
            matrix.add_element(n, nr, -mu * len / dx);
            matrix.add_element(n, n, mu * len / dx);

        }
        // Bottom boundary
        if (grid.j_from_n(n) == 0)
            rhs[n] += (*boundary_term)( grid.x_from_n(n),ymin) * compute_length(xmax-xmin, (*levelset)(xmin, ymin), (*levelset)(xmax, ymin));
        else {
            int nb = grid.n_from_ij(grid.i_from_n(n), grid.j_from_n(n)-1);
            double len = compute_length(xmax-xmin, (*levelset)(xmin, ymin), (*levelset)(xmax, ymin));
            matrix.add_element(n, nb, -mu * len / dy);
            matrix.add_element(n, n, mu * len / dy);
        }
        // Top boundary
        if (grid.j_from_n(n) == grid.get_M()-1)
            rhs[n] += (*boundary_term)( grid.x_from_n(n),ymax) * compute_length(xmax-xmin, (*levelset)(xmin, ymax), (*levelset)(xmax, ymax));
        else {
            int nt = grid.n_from_ij(grid.i_from_n(n), grid.j_from_n(n)+1);
            double len = compute_length(xmax-xmin, (*levelset)(xmin, ymax), (*levelset)(xmax, ymax));
            matrix.add_element(n, nt, -mu * len / dy);
            matrix.add_element(n, n, mu * len / dy);
        }

        rhs[n] += (*boundary_term)(grid.x_from_n(n), grid.y_from_n(n)) * integrate_over_interface((*levelset)(xmin, ymin),
                                                                                                  (*levelset)(xmax, ymin),
                                                                                                  (*levelset)(xmin, ymax),
                                                                                                  (*levelset)(xmax, ymax),
                                                                                                  (xmax-xmin), (ymax-ymin));
    }
}

double FVsolver::compute_length(double delta, double phi1, double phi2) {

    double epsilon = 1E-12;

    // displace phi1 and phi2 so they can't be exactly zero
    phi1 = abs(phi1) < epsilon ? epsilon : phi1;
    phi2 = abs(phi2) < epsilon ? epsilon : phi2;

    // both positive (i.e. outside)
    if (phi1 > 0. && phi2 > 0.)
        return 0.;
    if (phi1 < 0. && phi2 < 0.)
        return delta;
    if (phi1 <= 0. && phi2 >= 0.)
        return delta * phi1 / (phi1 - phi2 - epsilon);
    if (phi1 >= 0. && phi2 <= 0.)
        return delta * phi2 / (phi2 - phi1 - epsilon);
}

double FVsolver::integrate_over_interface(double phi00, double phi10, double phi01, double phi11, double dx, double dy){
    if (phi00 > 0. && phi01 > 0. && phi10 > 0. && phi11 > 0.)
        return 0.;
    if (phi00 < 0. && phi01 < 0. && phi10 < 0. && phi11 < 0.)
        return 0.;

    return sqrt(dx*dx+dy*dy);
}


double FVsolver::compute_area(double phi00, double phi10, double phi01, double phi11, double dx, double dy) {
    // Doing low order area computation
    // 01 --- 11
    // |      |
    // |      |
    // 00 --- 10
// Case 1: All are positive
    if (phi00 > 0. && phi01 > 0. && phi10 > 0. && phi11 > 0.)
        return 0.;
    else
        return dx*dy;
}