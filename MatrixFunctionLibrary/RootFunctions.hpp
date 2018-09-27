//
//  RootFunctions.hpp
//  MatrixFunctionLibrary
//
//  Created by Sovann Chak on 9/27/18.
//  Copyright © 2018 Sovann Chak. All rights reserved.
//

#ifndef RootFunctions_hpp
#define RootFunctions_hpp

#include <stdio.h>
#include <vector>
#include <functional>
#include <iostream>
#include <iomanip>
#include <cmath>


namespace root_functions {
    
    
    /*
     Linear root finding functions
     */
    void bisection_root_fndr(double (*func)(double), double a, double b);
    void mrf_root_fndr(double (*func)(double), double a, double b);
    void secant_root_fndr(double (*func)(double), double, double);
    void newton_root_fndr(double (*func)(double), double (*deriv)(double), double x);
    
}

#endif /* RootFunctions_hpp */
