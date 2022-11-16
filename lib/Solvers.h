//
// Created by Matt Blomquist on 11/8/22.
//

#ifndef F22_MATH_233_LABS_SOLVERS_H
#define F22_MATH_233_LABS_SOLVERS_H

#include "Matrix.h"
#include <vector>

class Solvers {

private:

public:
    virtual void solve(Matrix &A, std::vector<double> &rhs, std::vector<double> & solution ) const =0;
};

// Child Class for CG method
class CG : public Solvers{

private:
    void check_symmetry(SparseMatrix_CRS &A, std::vector<double> &solution) const;
public:
    void solve(Matrix &A, std::vector<double> &rhs, std::vector<double> & solution ) const;
};




#endif //F22_MATH_233_LABS_SOLVERS_H
