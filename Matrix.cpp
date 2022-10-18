//
// Created by Matt Blomquist on 10/13/22.
//

#include "Matrix.h"
#include <iostream>
#include "math_tools.h"

//Matrix::Matrix(){
//
//};
SparseMatrix_CRS::SparseMatrix_CRS() {

    values.assign(0, 0.);
    columns.assign(0, 0.);
    index.assign(0, 0);

};

// add element to sparse matrix
void SparseMatrix_CRS::add_element(int i, int j, double val) {

    int r_max = index.size() > 0 ? index.size() - 1 : 0;

    // for existing elements, add the new value to existing value
    if (position != -1) {
        values[position] += val;
    } else {
        // if you are trying to add an element to a row "we have already passed"
        // don't do it
        if (i < r_max) {
            throw std::invalid_argument("populate the matrix in correct order!");

        }

        if (i == r_max) {
            values.push_back(val);
            columns.push_back(j);
        } else {

            for (int j = r_max; j < i; j++) {
                index.push_back(columns.size());
            }

        values.push_back(val);
        columns.push_back(j);
    }

}

double SparseMatrix_CRS::get_element(int i, int j) const {


    int position = find_position(i, j);
    if (position == -1)
        return 0.;
    else
        return values[position];

}


void SparseMatrix_CRS::mat_Vec_Product(const std::vector<double> &x, std::vector<double> &Ax) const {
    int num_row = get_num_rows();
    Ax.assign(num_row,0.0);

    for (int r = 0; r < num_row; r++) {

        int start = r == 0 ? 0 : index[r - 1];
        int end = r == index.size() ? columns.size() : index[r];

        for (int pos = start; pos < end; pos++) {
            Ax[r] += values[pos] * x[columns[pos]];
        }
    }
}

void SparseMatrix_CRS::print() {
    std::cout << "values " << std::endl;
    for (int i = 0; i < values.size(); i++)
        std::cout << values[i] << std::endl;
    std::cout << "columns " << std::endl;
    for (int i = 0; i < columns.size(); i++)
        std::cout << columns[i] << std::endl;
    std::cout << "index " << std::endl;
    for (int i = 0; i < index.size(); i++)
        std::cout << index[i] << std::endl;
//    std::cout<<"size of index "<<index.size()<<std::endl;
}

void SparseMatrix_CRS::print_As_Full() {
    int c_max = 0;
    for (int i = 0; i < columns.size(); i++)
        c_max = c_max > columns[i] ? c_max : columns[i];

    int r_max = index.size(); // > 0 ? index.size() - 1 : 0;

//    std::cout << "c_max: " << c_max << std::endl;
//    std::cout << "r_max: " << r_max << std::endl;

    for (int r = 0; r <= r_max; r++) {
//        std::cout << "row: " << r << std::endl;

        for (int c = 0; c <= c_max; c++)
            std::cout << get_element(r, c) << ", ";
        std::cout << std::endl;
    }

}
