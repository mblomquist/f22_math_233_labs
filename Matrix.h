//
// Created by Matt Blomquist on 10/13/22.
//

#ifndef F22_MATH_233_LABS_MATRIX_H
#define F22_MATH_233_LABS_MATRIX_H

#include <vector>

class Matrix {

public:
    virtual void mat_Vec_Product( const std::vector<double> &x, std::vector<double> &Ax ) const =0;
    virtual void add_element(int i, int j,double v ) const =0;
    virtual double get_element(int i, int j ) const =0;



};

// Child Class for Matrix
class SparseMatrix_CRS:Matrix{

private:
    std::vector <double> values;
    std::vector <int> columns;
    std::vector <int> index;

public:
    SparseMatrix_CRS();
    void add_element(int i, int j, double val);
    double get_element(int i, int j);
};

#endif //F22_MATH_233_LABS_MATRIX_H
