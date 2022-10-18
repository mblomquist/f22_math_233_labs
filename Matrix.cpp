//
// Created by Matt Blomquist on 10/13/22.
//

#include "Matrix.h"
#include <iostream>
#include "math_tools.h"


SparseMatrix_CRS::SparseMatrix_CRS(){

    values.assign(0, 0.);
    columns.assign(0, 0.);
    index.assign(0,0);

};
// add element to sparse matrix
void SparseMatrix_CRS::add_element(int i, int j, double val) {

    int r_max = index.size() > 0 ? index.size() - 1 : 0;

    // if you are trying to add an element to a row "we have already passed"
    // don't do it
    if (i < r_max){
        throw std::invalid_argument("populate the matrix in correct order!");
    }

    if(i == r_max){
        values.push_back(val);
        columns.push_back(j);
    } else {

        for (int j = r_max; j < i; j++){
            index.push_back(columns.size());
        }

        values.push_back(val);
        columns.push_back(j);
    }

}

double SparseMatrix_CRS::get_element(int i, int j) const {

    if (i > index.size())
        return 0.0;

    int start = i == 0 ? 0 : index[i-1];
    int end   = index[i];

    for (int k = start; k < end; k++)
        if (columns[k] == j)
            return values[k];

    return 0.;

}


void SparseMatrix_CRS::mat_Vec_Product(const std::vector<double> &x, std::vector<double> &Ax) const {

}

void SparseMatrix_CRS::print()
{
    std::cout<<"values "<<std::endl;
    for (int i=0; i<values.size(); i++)
        std::cout<<values[i]<<std::endl;
    std::cout<<"columns "<<std::endl;
    for (int i=0; i<columns.size(); i++)
        std::cout<<columns[i]<<std::endl;
    std::cout<<"index "<<std::endl;
    for (int i=0; i<index.size(); i++)
        std::cout<<index[i]<<std::endl;
    std::cout<<"size of index "<<index.size()<<std::endl;
}

void SparseMatrix_CRS::print_As_Full(){
    int c_max = 0;
    for (int i=0; i<columns.size(); i++)
        c_max  = c_max > columns[i] ? c_max  : columns[i];

    int r_max = index.size() > 0 ? index.size() - 1 : 0;

    std::cout << c_max << std::endl;

    for (int r=0; r<=r_max; r++)
    {
        std::cout << r << std::endl;

        for (int c=0; c<=c_max; c++)
            std::cout << get_element(r,c) << ", ";
        std::cout << std::endl;
    }

}
