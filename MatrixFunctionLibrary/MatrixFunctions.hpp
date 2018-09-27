//
//  MatrixFunctions.hpp
//  MatrixFunctionLibrary
//
//  Created by Sovann Chak on 9/25/18.
//  Copyright © 2018 Sovann Chak. All rights reserved.
//

#ifndef MatrixFunctions_hpp
#define MatrixFunctions_hpp

#include <stdio.h>
#include "Matrix.hpp"


namespace matrix_functions
{
    Matrix projection(Matrix v_point, Matrix v_line);


    void lu_dcmp(Matrix&,Matrix &,Matrix&);
    void lu_bk_sub(Matrix,Matrix);
    
    void swap_row(Matrix &,int,int);

   
}
#endif /* MatrixFunctions_hpp */
