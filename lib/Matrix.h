//
// Created by Matt Blomquist on 10/13/22.
//

#ifndef F22_MATH_233_LABS_MATRIX_H
#define F22_MATH_233_LABS_MATRIX_H

#include <vector>

class Matrix {
private:
public:
    Matrix(){};
    virtual void mat_Vec_Product( const std::vector<double> &x, std::vector<double> &Ax ) const =0;
    virtual void residual( const std::vector<double> &x, const std::vector<double> &b, std::vector<double> &residual) const =0;
    virtual void add_element(int i, int j,double v ) {  };
    virtual double get_element(int i, int j ) const = 0;
    virtual ~Matrix(){};



};

// Child Class for Matrix
class SparseMatrix_CRS : public Matrix{

private:
public:

    std::vector <double> values;
    std::vector <int> columns;
    std::vector <int> index;
    SparseMatrix_CRS();
    void add_element(int i, int j, double val);
    double get_element(int i, int j) const;
    void mat_Vec_Product( const std::vector<double> &x, std::vector<double> &Ax )const;
    void residual( const std::vector<double> &x, const std::vector<double> &B, std::vector<double> &residual ) const;
    void print();
    void print_As_Full();
    int find_position(int i, int j) const;
    int get_num_rows() const;
};

class GS_precond_CRS : public Matrix{

private :
    SparseMatrix_CRS Amatrix;
public:
    void mat_Vec_Product( const std::vector<double> &x, std::vector<double> &Ax ) const;
    void set_matrix(SparseMatrix_CRS & A){Amatrix = A;};
    void Linverse(const std::vector<double> &x, std::vector<double> &Linvx ) const ;

};

#endif //F22_MATH_233_LABS_MATRIX_H
