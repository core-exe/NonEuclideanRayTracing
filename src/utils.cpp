# include <vecmath.h>
# include "utils.hpp"

float dot(Vector4f a, Vector4f b, Matrix4f g){
    float d = 0;
    for(int i=0; i<4; i++)
        for(int j=0; j<4; j++)
            d+=a[i]*b[j]*g(i,j);
    return d;
}

float dot(Vector3f a, Vector3f b, Matrix4f g){
    float d = 0;
    for(int i=1; i<4; i++)
        for(int j=1; j<4; j++)
            d+=a[i]*b[j]*g(i,j);
    return d;
}

Vector4f get_negative_null_vector(Vector3f v, Matrix4f g){
    float a = g(0,0);
    float b = g(1,0)+g(2,0)+g(3,0);
    float c = Vector3f::dot(v, g.getSubmatrix3x3(1,1)*v);
    float v0 = (-b-sqrt(b*2-4*a*c))/(2*a);
    return Vector4f(v0, v) / (-v0);
}