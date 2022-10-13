//
// Created by Matt Blomquist on 10/13/22.
//

#include "Matrix.h"


SparseMatrix_CRS::SparseMatrix_CRS(){

    values.assign(0, 0.);
    columns.assign(0, 0.);
    index.assign(0,0);

};

void SparseMatrix_CRS::add_element(int i, int j, double val) {

    int r_max = index.size() >0 ? index.size() - 1 : 0;

    if (i < r_max){
        throw std::invalid_argument("populate the matrix in correct order!");
    }

    if(i == r_max){
        values.push_back(val);
        columns.push_back(j);
    } else {
        index.push_back(columns.size());
        values.push_back(val);
        columns.push_back(j);
    }

}

double SparseMatrix_CRS::get_element(int i, int j) {

}
