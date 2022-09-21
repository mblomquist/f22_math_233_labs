//
// Created by Matt Blomquist on 9/13/22.
//

#include "FullMatrix.h"
#include <iostream>

FullMatrix::FullMatrix() {

}

FullMatrix::FullMatrix(int N) {
    size = N;
    values.resize(size * size);

    // initialize matrix with zeros
#pragma omp parallel for
    for (int i = 0; i < size * size; i++) {
        values[i] = 0.;
    }

}

void FullMatrix::add_Element(int i, int j, double v) {
    std::cout << size << std::endl;
    if (i >= size || j >= size || i < 0 || j < 0) {
        throw std::invalid_argument("bad index value");
    } else {
        values[i + j * size] += v;
    }
}

void FullMatrix::display() {

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            std::cout << values[i + j * size] << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

double FullMatrix::get_Values(int i, int j) {
    return values[i + j * size];
}

std::vector<double> FullMatrix::mat_Vec_Prod(std::vector<double> &x) {
    std::vector<double> prod;
    prod.resize(size);

#pragma omp parallel for
    for (int i = 0; i < size; i++) {
        double sum = 0.;
        for (int j = 0; j < size; j++) {
            sum += get_Values(i, j) * x[j];
        }
        prod[i] = sum;
    }

    return prod;
}


