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

SchwartzchildMetric::SchwartzchildMetric(float _radius){
    radius = _radius;
}

Matrix4f SchwartzchildMetric::val(Vector4f r){
    float rad = r.yzw().length();
    Vector4f a = Vector4f(rad, r.yzw())*radius/(rad*rad*rad);
    Matrix4f g = Matrix4f(a*rad, a*r[1], a*r[2], a*r[3]);
    g(0,0)-=1;
    g(1,1)+=1;
    g(2,2)+=1;
    g(3,3)+=1;
    return g;
}

void SchwartzchildMetric::d(Vector4f r, float dg[4][4][4]){
    float rad = r.yzw().length();
    Vector4f a = Vector4f(rad, r.yzw());
    float da[4][4]; //a_;i
    da[0][0]=0,da[1][0]=0,da[2][0]=0,da[3][0]=0;
    da[0][1]=r[1]/rad,da[1][1]=1,da[2][1]=0,da[3][1]=0;
    da[0][2]=r[2]/rad,da[1][2]=0,da[2][2]=1,da[3][2]=0;
    da[0][3]=r[3]/rad,da[1][3]=0,da[2][3]=0,da[3][3]=1;
    for(int i=0; i<4; i++){
        for(int j=0; j<4; j++){
            dg[i][j][0] = 0;
            for(int k=1; k<4; k++){
                dg[i][j][k] = -3*radius*r[k]/pow(rad, 5)*a[i]*a[j]+radius/pow(rad,3)*a[i]*da[j][k]+radius/pow(rad,3)*da[i][k]*a[j];
            }
        }
    }
}