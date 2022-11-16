//
// Created by Jocelyn Ornelas on 11/15/22.
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
// Main:
// - set everything
//  FVsolver.solve(solution)
//         build system AX = B
//         create conjugate method object CG
//         CG.solve(solution)
// Today's goal: Implement preconditioner in pipeline

int main() {
    std::cout << "Hello Lab 8." << std::endl;
    return 0;
}