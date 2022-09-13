#include <iostream>
#include <vector>
#include "Grid2d.h"
#include "FullMatrix.h"



// using namespace std;  < -- Streamline?

int main() {

    std::cout << "Hello, Lab 02" << std::endl;

    FullMatrix A(5);
    A.add_Element(0, 0, 2);
    A.add_Element(1, 1, 3);
//    A.add_Element(6,1,3);
    A.add_Element(2, 3, 5);

    A.display();

    std::vector<double> x, y;

    x.resize(5);
    y.resize(5);

    x.assign(5, 1.);

    y = A.mat_Vec_Prod(x);

    for (int i = 0; i < 5; i++)
        std::cout << y[i] << std::endl;

    return 0;
} 