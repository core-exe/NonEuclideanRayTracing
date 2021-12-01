# pragma once
# include <vecmath.h>

float dot(Vector4f a, Vector4f b, Matrix4f g){
    float d = 0;
    for(int i=0; i<4; i++)
        for(int j=0; j<4; j++)
            d+=a[i]*b[j]*g(i,j);
    return d;
}