//
// Created by Matt Blomquist on 11/1/22.
//

#include <iostream>
#include "../lib/cf2.h"
#include "math.h"
#include "../lib/FVsolver.h"
#include "../lib/Grid2d.h"
#include <vector>
#include "../lib/Matrix.h"
#include "../lib/Solvers.h"
#include "../lib/math_tools.h"

class myboundarycondition : public cf2 {
public :
    virtual double operator()(double x, double y) const {
        return 0;
    }
};

class mylevelset : public cf2 {
public :
    virtual double operator()(double x, double y) const {
        return -1;
    }
} levelset;

class myforcingterm : public cf2 {
public :
    virtual double operator()(double x, double y) const {
        return 1.;
    }
} forcingterm;


int main() {

    std::cout << "Hello Lab 6." << std::endl;
    myboundarycondition mybc;
    FVsolver solver;
    Grid2d grid(3, 3, 0, 2, 0, 2);
    solver.set_Grid(grid);
    solver.set_alpha(1.);
    solver.set_mu(1.);
    solver.set_boundary_term(mybc);
    solver.set_level_set(levelset);
    solver.set_forcing_term(forcingterm);

    std::vector<double> solution;
    solver.solve(solution);

    std::cout << "\nFVSolver Solution:\n" << std::endl;
    for (int i = 0; i < grid.get_M(); i++){
        for (int j = 0; j < grid.get_N(); j++){
            std::cout << solution[grid.n_from_ij(i,j)] << ", "<< std::setw(15);
        }
        std::cout << std::endl;
    }


//    int N = 100;
//    SparseMatrix_CRS A;
//    std::vector<double> bvec, x;
//    bvec.assign(N, 1);
//    x.assign(N, 0.);
//
//    //std::cout << dot(bvec,x) << std::endl;
//
//    for (int i = 0; i < N; i++) {
////        if (i == N-1)
////            A.add_element(i,i-1,10);
//        A.add_element(i, i, 2.);
//        if ( i < N-1) {
//            A.add_element( i, i+1, -1.);
//        }
//        if ( i > 0 ) {
//            A.add_element( i, i-1, -1.);
//        }
//    }
//
//
//    CG cg;

//    cg.solve(A, bvec, x);
//    for (int i = 0; i < N; i++) {
//        std::cout << x[i] << std::endl;
//    }


    return 0;
}