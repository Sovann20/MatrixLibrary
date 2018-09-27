//
//  RootFunctions.cpp
//  MatrixFunctionLibrary
//
//  Created by Sovann Chak on 9/27/18.
//  Copyright © 2018 Sovann Chak. All rights reserved.
//

#include "RootFunctions.hpp"

void root_functions::bisection_root_fndr(double (*func)(double), double a, double b)
{
    int i;
    std::cout.precision(6);
    std::vector<double> a_vals;
    std::vector<double> b_vals;
    
    a_vals.push_back(a);
    b_vals.push_back(b);
    
    double m, fa_val, fm_val, fb_val;
    i=0;
    std::cout << "iteration" << std::setw(20) << "[a_i, b_i]" << std::setw(20) << "f(a_i)" << std::setw(20) << "f(b_i)" <<
    std::setw(20) << "(a_i+b_i)/2" << std::setw(20) << "f((a_i+b_i)/2)" << std::endl;
    
    while(abs(func(b_vals[i])) >= .00005){
        m = (a_vals[i]+b_vals[i])/2;
        
        fa_val=func(a_vals[i]);
        fm_val=func(m);
        fb_val=func(b_vals[i]);
        
        if(fa_val*fm_val <= 0){
            a_vals.push_back(a_vals[i]);
            b_vals.push_back(m);
        }
        else {
            a_vals.push_back(m);
            b_vals.push_back(b_vals[i]);
        }
        
        std::cout << i << std::setw(20)
        << "[" << a_vals[i] << ", " << b_vals[i] <<"]"
        << std::setw(20) << fa_val << std::setw(20) << fb_val <<
        std::setw(20) << m << std::setw(20) << fm_val << std::endl;
        
        
        ++i;
    }
    std::cout << i << std::setw(20)
    << "[" << a_vals[i] << ", " << b_vals[i] <<"]"
    << std::setw(20) << fa_val << std::setw(20) << fb_val <<
    std::setw(20) << m << std::setw(20) << fm_val << std::endl;
    std::cout << "\n\n" << std::endl;
}

void root_functions::mrf_root_fndr(double (*func)(double), double a, double b)
{
    int i;
    double F, G, f_w_ip1, w_ip1;
    std::cout.precision(6);
    std::vector<double> w_vals;
    std::vector<double> a_vals;
    std::vector<double> b_vals;
    
    a_vals.push_back(a);
    b_vals.push_back(b);
    w_vals.push_back(a);
    
    F = func(a);
    G = func(b);
    
    i=0;
    std::cout << "iteration" << std::setw(20) << "[a_i, b_i]" << std::setw(20) << "F" << std::setw(20) << "G" <<
    std::setw(20) << "w_i+1" << std::setw(20) << "f(w_i+1)" << std::endl;
    
    while(abs(func(b_vals[i])) >= .00005){
        std::cout << i << std::setw(20)
        << "[" << a_vals[i] << ", " << b_vals[i] <<"]"
        << std::setw(20) << F << std::setw(20) << G;
        
        w_vals.push_back((G*a_vals[i] - F*b_vals[i])/(G-F));
        
        w_ip1 = w_vals[i+1];
        f_w_ip1 = func(w_ip1);
        if(func(a_vals[i])*f_w_ip1 <= 0) {
            a_vals.push_back(a_vals[i]);
            b_vals.push_back(w_ip1);
            G = f_w_ip1;
            if(func(w_vals[i])*f_w_ip1 > 0) {
                F = F/2.0;
            }
        }
        else {
            a_vals.push_back(w_ip1);
            b_vals.push_back(b_vals[i]);
            F = f_w_ip1;
            if(func(w_vals[i])*f_w_ip1 > 0) {
                G = G/2;
            }
        }

        std::cout << std::setw(20) << w_ip1 << std::setw(20) << f_w_ip1 << std::endl;
        
        ++i;
    }
    std::cout << i << std::setw(20)
    << "[" << a_vals[i] << ", " << b_vals[i] <<"]"
    << std::setw(20) << F << std::setw(20) << G;
    std::cout << std::setw(20) << w_ip1 << std::setw(20) << f_w_ip1 << std::endl;

    std::cout << "\n\n" << std::endl;
}

void root_functions::secant_root_fndr(double (*func)(double), double x0, double x1)
{
    std::cout.precision(6);
    std::cout << "iteration" << std::setw(10) << "x_i" << std::setw(20) << "f(x_i)" << std::endl;
    
    int i=0;
    std::vector<double> x_vals;
    
    x_vals.push_back(x0);
    std::cout << i << std::setw(20) << x_vals[i] << std::setw(20) << func(x_vals[i]) << std::endl;
    
    ++i;
    x_vals.push_back(x1);
    
    while(abs(func(x_vals[i])) > .00005) {
        std::cout << i << std::setw(20) << x_vals[i] << std::setw(20) << func(x_vals[i]) << std::endl;
        x_vals.push_back(x_vals[i]-func(x_vals[i])*((x_vals[i]-x_vals[i-1])/(func(x_vals[i])-func(x_vals[i-1]))));
        ++i;
    }
    std::cout << i << std::setw(20) << x_vals[i] << std::setw(20) << func(x_vals[i]) << std::endl;

    std::cout << "\n\n" << std::endl;
}



void root_functions::newton_root_fndr(double (*func)(double), double (*deriv)(double), double x) {
    std::cout.precision(6);
    std::cout << "iteration" << std::setw(10) << "x_i" << std::setw(20) << "f(x_i)" << std::endl;
    
    int i=0;
    std::vector<double> x_vals;
    x_vals.push_back(x);
    
     while(abs(func(x_vals[i])) > .00005) {
         std::cout << i << std::setw(20) << x_vals[i] << std::setw(20) << func(x_vals[i]) << std::endl;
         x_vals.push_back(x_vals[i] - (func(x_vals[i])/deriv(x_vals[i])));
         ++i;
     }
    std::cout << i << std::setw(20) << x_vals[i] << std::setw(20) << func(x_vals[i]) << std::endl;
    std::cout << "\n\n" << std::endl;
}
