//
// Created by Matt Blomquist on 10/27/22.
//

#include <iostream>
#include "../lib/cf2.h"
#include "math.h"

class mysinfuction : cf2 {
public :
    virtual double operator()(double x, double y) const
    {
    return sin(x);
    }
};


int main(){

    std::cout << "Hello Lab 5." << std::endl;
    mysinfuction fun;
    std::cout << fun(3.141,0) << std::endl;

    return 0;
}