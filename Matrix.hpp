//
//  Matrix.hpp
//  Sovann_Chak_HW2_Prob5
//
//  Created by Sovann Chak on 9/5/18.
//  Copyright © 2018 Sovann Chak. All rights reserved.
//

#ifndef Matrix_hpp
#define Matrix_hpp

#include <stdio.h>
#include <vector>
#include <iostream>
#include <iomanip>
#include <initializer_list>

class Matrix{
    std::vector<double> elements_;
    unsigned int rows_, cols_;
    int size;
    
public:
    Matrix(unsigned int, unsigned int);
    Matrix();
    ~Matrix();
    
    void place(double, int, int);
    void resize(int, int);
    void print();
    
    int get_size();
    int get_rows();
    int get_cols();
    
    Matrix transpose();
    
    double operator()(int,int);
    Matrix& operator=(std::initializer_list<double>);
    Matrix operator+(Matrix);
    Matrix operator-(Matrix);
    Matrix operator*(Matrix);
    Matrix operator*(double);

};

Matrix projection(Matrix v_point, Matrix v_line);

#endif
