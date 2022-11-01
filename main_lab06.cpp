//
// Created by Matt Blomquist on 11/1/22.
//

#include <iostream>
#include "cf2.h"
#include "math.h"

class mysinfuction : cf2 {
public :
    virtual double operator()(double x, double y) const
    {
        return sin(x);
    }
};


int main(){

    std::cout << "Hello Lab 6." << std::endl;
    mysinfuction fun;
    std::cout << fun(3.141,0) << std::endl;

    return 0;
}