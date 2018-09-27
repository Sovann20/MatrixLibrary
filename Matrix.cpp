//
//  Matrix.cpp
//  Sovann_Chak_HW2_Prob5
//
//  Created by Sovann Chak on 9/5/18.
//  Copyright © 2018 Sovann Chak. All rights reserved.
//

#include "Matrix.hpp"

Matrix::Matrix(unsigned int rows, unsigned int cols)
: rows_(rows), cols_(cols), size(rows_*cols_)
{
    elements_.resize(rows_*cols_);
}

Matrix::Matrix()
: rows_(0), cols_(0), size(0)
{
    
}


Matrix::~Matrix()
{
    
}

void Matrix::place(double data, int x, int y)
{
    if(x >= rows_ || y >= cols_)
    {
        throw std::out_of_range("Provided indicies out of range.");
    }
    else
    {
        elements_[cols_*x + y] = data;
    }
}

void Matrix::resize(int num_rows, int num_cols)
{
    rows_ = num_rows;
    cols_ = num_cols;
}

void Matrix::print()
{
    int i,j;
    for( i = 0; i < rows_; ++i ) {
        std::cout<<"\n";
        for( j = 0; j < cols_; ++j ) {
            std::cout<<std::setw(10)<<elements_[cols_*i+j]<<" ";
        }
    }
    std::cout<<"\n"<<std::endl;
    
}

Matrix Matrix::transpose()
{
    Matrix transpose = Matrix(cols_, rows_);
    
    transpose.elements_ = elements_;
    
    return transpose;
}

double Matrix::mag()
{
    int i;
    double sum = 0;
    for(i = 0; i < elements_.size(); ++i) {
        sum += elements_[i]*elements_[i];
    }
    
    return sqrt(sum);
}

int Matrix::get_rows()
{
    return rows_;
}

int Matrix::get_cols()
{
    return cols_;
}

int Matrix::get_size()
{
    return size;
}

double Matrix::operator()(int x, int y)
{
    if(x >= rows_ || y >= cols_) {
        throw std::out_of_range("Provided indicies out of range.");
    }
    else {
        return elements_[cols_*x + y];
    }
}

Matrix& Matrix::operator=(std::initializer_list<double> list)
{
    if(list.size() > rows_*cols_)
    {
        throw std::out_of_range("Please provide a matrix in range.");
    }
    else {
        elements_ = list;
        return *this;
    }
}

Matrix& Matrix::operator=(Matrix m)
{
    if(m.size != size)
    {
        size = m.size;
        cols_ = m.cols_;
        rows_ = m.rows_;
        elements_ = m.elements_;
        return *this;
    }
    else {
        elements_ = m.elements_;
        return *this;
    }
}

Matrix Matrix::operator+(Matrix rhs_m)
{
    if(rows_ != rhs_m.rows_ || cols_ != rhs_m.cols_)
    {
        throw std::runtime_error("The matracies must be the same size!");
    }
    
    Matrix m_to_return = Matrix(rows_, cols_);
    
    int i;
    for(i = 0; i < rows_*cols_; ++i){
        m_to_return.elements_[i] = elements_[i]+rhs_m.elements_[i];
    }
    
    return m_to_return;
}

Matrix Matrix::operator-(Matrix rhs_m)
{
    if(rows_ != rhs_m.rows_ || cols_ != rhs_m.cols_)
    {
        throw std::runtime_error("The matracies must be the same size!");
    }
    
    Matrix m_to_return = Matrix(rows_, cols_);
    
    int i;
    for(i = 0; i < rows_*cols_; ++i){
        m_to_return.elements_[i] = elements_[i]-rhs_m.elements_[i];
    }
    
    return m_to_return;
}

Matrix Matrix::operator*(Matrix rhs_m)
{
    
    if( cols_ == 1 && rows_ == 1 )
    {
        Matrix m_to_return = rhs_m*elements_[0];
        return m_to_return;
    }
    else if( rhs_m.cols_ == 1 && rhs_m.rows_ == 1 )
    {
        Matrix m_to_return = *this*rhs_m.elements_[0];
        return m_to_return;
    }
    else if( rows_ == rhs_m.rows_ && cols_ == rhs_m.cols_ && ( cols_ == 1 || rows_ == 1) )
    {
        int i,j;
        double sum;
        Matrix m_to_return = Matrix(1, 1);
        sum = 0;
        for(i = 0; i < rows_; ++i) {
            for (j = 0; j < cols_; ++j) {
                sum+=elements_[rows_*j+i]*rhs_m.elements_[rows_*j+i];
            }
        }
        m_to_return.place(sum, 0, 0);
        return m_to_return;
    }
    else if(cols_ != rhs_m.rows_)
    {
        throw std::runtime_error("The number of columns in the first matrix must be equal to the number of rows in the second matrix.");
    }
    
    
    Matrix m_to_return = Matrix(rows_, rhs_m.cols_);
    
    int i, j, k, count;
    double sum;
    count = 0;
    for( i = 0; i < rows_; ++i ) {
        for( j = 0; j < rhs_m.cols_; ++j ) {
            sum = 0;
            for(k = 0; k < cols_; ++k){
                sum+= elements_[rows_*k+i]*rhs_m.elements_[rhs_m.cols_*k+j];
            }
            m_to_return.place(sum, i, j);
            count++;
        }
    }
    
    if(count == 1){
        m_to_return.resize(1, 1);
    }
    
    return m_to_return;
}

Matrix Matrix::operator*(double c)
{
    int i, j;
    Matrix m_to_return = Matrix(rows_, cols_);
    for( i = 0; i < rows_; ++i ) {
        for(j = 0; j < cols_; ++j){
            m_to_return.place(elements_[rows_*i+j]*c, i, j);
        }
    }
    return m_to_return;
}

Matrix Matrix::operator/(double c)
{
    int i, j;
    Matrix m_to_return = Matrix(rows_, cols_);
    for( i = 0; i < rows_; ++i ) {
        for(j = 0; j < cols_; ++j){
            if(c > 0){
                m_to_return.place(elements_[rows_*i+j]/c, i, j);
            }
            else {
                m_to_return.place(0, i, j);
            }
        }
    }
    return m_to_return;
}

double Matrix::dot(Matrix rhs) {
    int i;
    double product = 0;
    
    if(elements_.size() != elements_.size()) {
        throw std::runtime_error("The columns and rows must be equivalent for dot product");
    }
    
    for( i = 0; i < size; ++i) {
        product += elements_[i]*rhs.elements_[i];
    }
    
    return product;
}


