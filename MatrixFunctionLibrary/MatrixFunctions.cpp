//
//  MatrixFunctions.cpp
//  MatrixFunctionLibrary
//
//  Created by Sovann Chak on 9/25/18.
//  Copyright © 2018 Sovann Chak. All rights reserved.
//

#include "MatrixFunctions.hpp"
#include <cmath>

Matrix matrix_functions::projection(Matrix v_point, Matrix v_line)
{
    int iden_size = v_point.get_rows();
    int i;
    Matrix iden_matrix = Matrix(iden_size, iden_size);
    
    for( i = 0; i < iden_size; ++i ) {
        iden_matrix.place(1, i, i);
    }
    
    Matrix proj_m = Matrix(iden_size, iden_size);
    Matrix v_line_t = v_line.transpose();
    proj_m = (v_point*v_line_t) - (v_line*v_point)*iden_matrix;
    
    return proj_m;
}

/*
 Using Crout's algorithm for LU decomposition of matrix A into a lower triangular matrix L
 and an upper triangular matrix U.
 */
void matrix_functions::lu_dcmp(Matrix &A, Matrix &U, Matrix &L)
{
    if(A.get_rows() != A.get_cols()) {
        throw std::runtime_error("The provided matrix must be square.");
    }
    
    int n = A.get_rows();
    int i, j, k, largest_i;
    
    double largest_elem, u_sum, l_sum;
    
    std::vector<double> largest_elems(n);
    
    L = Matrix(n,n);
    U = Matrix(n,n);
    
    //Placing 1s along the diagnol.
    for(i=0; i < n; ++i) {
        L.place(1, i, i);
    }
    
    //Largest element in each row
    for(i=0; i < n; ++i) {
        largest_elem = 0;
        for(j=0; j < n; ++j) {
            if(A(i,j) > largest_elem){
                largest_elem = A(i,j);
            }
        }
        largest_elems[i] = largest_elem;
        
    }
    
    
    for(j=0; j < n; ++j) {
        
        for(i=0; i < j; ++i) {
            u_sum = 0;
            for(k=0; k < i; ++k){
                u_sum += L(i,k)*U(k,j);
            }
            U.place(A(i,j)-u_sum, i, j);
            L.place(0, i, j);

        }
        
        largest_elem = 0;
        largest_i=j;

        for(i=j; i < n; ++i) {
            u_sum=0;
            for(k=0; k < j; ++k) {
                u_sum += L(i,k)*U(k,j);
            }
            
            U.place((A(i,j)-u_sum), i, j);
    

            //Choosing which rows to change
            if(largest_elems[i]*U(i,j) >= largest_elem) {
                largest_elem = largest_elems[i]*U(i,j);
                largest_i = i;
            }
        }
        
        //Pivot
        if(largest_i != j) {
            swap_row(U, largest_i, j);
            swap_row(A, largest_i, j);
            swap_row(L, largest_i, j);
        }
        
        L.place(1, j, j);
        if(j < n-1){
            
            
            for(i=j+1; i < n; ++i) {
                l_sum=0;
                for(k=0; k < j; ++k) {
                    l_sum += L(i,k)*U(k,j);
                }
                
                L.place((1.0/U(j,j))*(A(i,j)-l_sum), i, j);
                U.place(0, i, j);
            }
        }
    }
}

/*
 Used Gaussian method
*/
void matrix_functions::lu_bk_sub(Matrix A, Matrix b) {
    int i, j, k, largest_i;
    int n = A.get_rows();

    double largest_elem;
    double zero_row;
    
    Matrix x = Matrix(n, b.get_cols());

    
    
    for(j=0; j < n; ++j) {
        
        largest_i = j;
        largest_elem = A(largest_i,j);
        
        for(i=j+1; i < n; ++i) {
            if(abs(A(i,j)) > largest_elem) {
                largest_elem = A(i, j);
                largest_i = i;
            }
        }
        
        if(largest_i != j) { swap_row(A, largest_i, j); }
        
        for(i=j+1; i < n; ++i) {
            zero_row = A(i,j)/A(j,j);
            for(k=j+1; k < n; ++k) {
                A.place(A(i,k)-zero_row*A(j,k), i, k);
            }
            A.place(0, i, j);
            b.place(b(i,0)-zero_row*b(j,0), i, 0);
        }
    }
    
    for(i=n-1; i >= 0; --i) {
        zero_row = b(i,0);

        for(j=n-1; j > i; --j) {
            zero_row -= x(j,0)*A(i,j);
        }
        x.place(zero_row/A(i,i), i, 0);
    }
    
    
    x.print();
}


void matrix_functions::swap_row(Matrix &m, int row_a, int row_b)
{
    if(row_a >= m.get_rows() || row_b >= m.get_rows() || row_a < 0 || row_b < 0) {
        throw std::runtime_error("Provided rows are out of bounds.");
    }
    
    std::vector<double> temp(m.get_cols());
    int i;
    
    for(i=0; i < m.get_cols(); ++i) {
        temp[i] = m(row_a,i);
        m.place(m(row_b,i), row_a, i);
        m.place(temp[i], row_b, i);
    }
}
