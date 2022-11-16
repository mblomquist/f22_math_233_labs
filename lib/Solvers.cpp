//
// Created by Matt Blomquist on 11/8/22.
//

#include "Solvers.h"
#include "math_tools.h"
#include <stdio.h>

// Solve Conjugate Gradient
void CG::solve(Matrix &A, std::vector<double> &rhs, std::vector<double> &solution) const {

//    check for symmetry
//    check_symmetry(A, solution);

    // initialize parameters
    std::vector<double> r, p, Ap;
    double alpha, pAp, rr, rr_new;

    int max_itr = 2000;
    double tolerance = 1E-12;
    int itr = 0;
    double error = 1;
    solution.assign(rhs.size(), 0.);
    A.residual(solution, rhs, r);
    p = r;

    // run loop until tolerance threshold met or iterations max out
    while (error > tolerance && itr < max_itr) {
        A.mat_Vec_Product(p, Ap);
        pAp = dot(p, Ap);
        //  std::cout<<pAp<<std::endl;
        rr = dot(r, r);
        alpha = rr / (pAp + 1E-12);
#pragma omp parallel for
        for (int n = 0; n < solution.size(); n++) {
            solution[n] += alpha * p[n];
            r[n] -= alpha * Ap[n];
        }
         rr_new = dot(r, r);
#pragma omp parallel for
        for (int n = 0; n < solution.size(); n++) {
            p[n] = r[n] - rr_new / (rr + 1E-12) * p[n];
        }

        error = rr_new/( solution.size()*solution.size());
    if(itr%10 == 0)
        std::cout << "CG  itr= " << itr << " res = " << error << std::endl;
        itr += 1;
    }

}

void CG::check_symmetry(SparseMatrix_CRS &A, std::vector<double> &solution) const {
    // check for symmetry
    std::vector<double> temp_x, temp_y, temp_Ax, temp_Ay;
    temp_x.assign(solution.size(), 0.);
    temp_y.assign(solution.size(), 0.);

#pragma omp  parallel for
    for (int i = 0; i < solution.size(); i++) {
        temp_x[i] = rand();
        temp_y[i] = rand();
    }
    A.mat_Vec_Product(temp_x, temp_Ax);
    A.mat_Vec_Product(temp_y, temp_Ay);
    double diff = (dot(temp_Ax, temp_y) - dot(temp_Ay, temp_x));
//    if (diff > 1E-10)
//        std::cout << "A is not symmetric, diff = " << diff << std::endl;

}