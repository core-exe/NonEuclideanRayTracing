# include "metric.hpp"

Matrix4f Metric4::val(Vector4f r){
    return Matrix4f::identity();
}

Matrix4f Metric4::inv(Vector4f r){
    return val(r).inverse();
}

void Metric4::d(Vector4f r, float dg[4][4][4]){
    // X[i][j][k] = g_{ij;k}
    for(int i=0; i<4; i++) 
        for(int j=0; j<4; j++) 
            for(int k=0; k<4; k++) 
                dg[i][j][k] = 0;
}