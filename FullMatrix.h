//
// Created by Matt Blomquist on 9/13/22.
//

#ifndef LAB01_FULLMATRIX_H
#define LAB01_FULLMATRIX_H

#include <vector>

class FullMatrix {
private:
    std::vector<double> values;
    int size;

public:
    FullMatrix();
    FullMatrix(int N);
    void add_Element(int i, int j, double v);

    double get_Values(int i, int j);

    void display();

    std::vector<double> mat_Vec_Prod(std::vector<double> &x);
};


#endif //LAB01_FULLMATRIX_H
