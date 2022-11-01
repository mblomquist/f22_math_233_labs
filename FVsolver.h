//
// Created by Matt Blomquist on 10/27/22.
//

#ifndef F22_MATH_233_LABS_FVSOLVER_H
#define F22_MATH_233_LABS_FVSOLVER_H

#include <vector>
#include "Matrix.h"
#include "Grid2d.h"
#include "cf2.h"
class FVsolver {
private :
    double alpha;
    double mu;
    double integrate_over_interface(double phi00, double phi10, double phi01, double phi11, double dx, double dy);
    std::vector<double>  rhs;
    SparseMatrix_CRS matrix;
    Grid2d grid;
    cf2 *levelset;
    cf2 *forcing_term;
    cf2 *boundary_term;
    // boundary condition and forcing term
public :
    void set_mu(double new_mu) { mu = new_mu; };

    void set_alpha(double new_alpha) { alpha = new_alpha; };

    void set_Grid(Grid2d new_grid) { grid = new_grid; };
    void set_level_set(cf2 & new_ls){levelset = &new_ls;};
    void set_forcing_term(cf2 & new_forcing_term) {forcing_term = &new_forcing_term;};
    void set_boundary_term(cf2 & new_boundary_term){boundary_term = &new_boundary_term;};
    void solve(std::vector<double> &solution);

    double compute_length(double delta, double phi1, double phi2);

    double compute_area(double phi00, double phi10, double phi01, double phi11, double dx, double dy);
};


#endif //F22_MATH_233_LABS_FVSOLVER_H
