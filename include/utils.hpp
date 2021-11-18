#include <vecmath.h>

void matrix_to_array3(Matrix3f m, float** p){
    for(int i=0; i<3; i++)
        for(int j=0; j<3; j++)
            p[i][j] = m(i, j);
}

Matrix3f array_to_matrix3(float** p){
    Matrix3f m;
    for(int i=0; i<3; i++)
        for(int j=0; j<3; j++)
            m(i, j) = p[i][j];
    return m;
}

void matrix_to_array4(Matrix4f m, float** p){
    for(int i=0; i<4; i++)
        for(int j=0; j<4; j++)
            p[i][j] = m(i, j);
}

Matrix4f array_to_matrix4(float** p){
    Matrix4f m;
    for(int i=0; i<4; i++)
        for(int j=0; j<4; j++)
            m(i, j) = p[i][j];
    return m;
}