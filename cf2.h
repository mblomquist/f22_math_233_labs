//
// Created by Matt Blomquist on 10/27/22.
//

#ifndef F22_MATH_233_LABS_CF2_H
#define F22_MATH_233_LABS_CF2_H

// continuous function of 2 variables (i.e. f(x,y))
class cf2 {
public :
    virtual double operator()(double x, double y) const =0;
};


#endif //F22_MATH_233_LABS_CF2_H
