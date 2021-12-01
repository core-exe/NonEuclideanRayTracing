# pragma once
# include <vecmath.h>
# include "metric.hpp"

class Christoffel3 {
    private:
    Metric3* g;
    public:
    Christoffel3(Metric3* _g) {
        g = _g;
    }
    void val(Vector3f r, float gamma[3][3][3])
    {
        // X[i][j][k] = Gamma^i_{jk}
        float dg[3][3][3];
        g->d(r, dg);
        Matrix3f ginv = g->inv(r);
        int i, j, k, m;
        for(i=0; i<3; i++)
            for(j=0; j<3; j++)
                for(k=0,gamma[i][j][k] = 0; k<3; k++) 
                    for(m=0; m<3; m++)
                        gamma[i][j][k] += 0.5*ginv(i,m)*(dg[m][j][k]+dg[m][k][j]-dg[j][k][m]);
    }
};

class Christoffel4 {
    private:
    Metric4* g;
    public:
    Christoffel4(Metric4* _g) {
        g = _g;
    }
    void val(Vector4f r, float gamma[4][4][4])
    {
        // X[i][j][k] = Gamma^i_{jk}
        float dg[4][4][4];
        g->d(r, dg);
        Matrix4f ginv = g->inv(r);
        int i, j, k, m;
        for(i=0; i<4; i++)
            for(j=0; j<4; j++)
                for(k=0,gamma[i][j][k] = 0; k<4; k++) 
                    for(m=0; m<4; m++)
                        gamma[i][j][k] += 0.5*ginv(i,m)*(dg[m][j][k]+dg[m][k][j]-dg[j][k][m]);
    }
};