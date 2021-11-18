#include <vecmath.h>

class Metric3 {
    public:
    Metric3(){}
    ~Metric3(){}

    virtual Matrix3f val(Vector3f r){
        return Matrix3f::identity();
    }

    Matrix3f inv(Vector3f r){
        return this->val(r).inverse();
    }

    virtual void d(Vector3f r, float dg[][3][3]){
        // X[i][j][k] = g_{ij;k}
        for(int i=0; i<3; i++) 
            for(int j=0; j<3; j++) 
                for(int k=0; k<3; k++) 
                    dg[i][j][k] = 0;
    }

    virtual void dd(Vector3f r, float ddg[][3][3][3]){
        // X[i][j][k][l] = g_{ij;kl}
        for(int i=0; i<3; i++) 
            for(int j=0; j<3; j++) 
                for(int k=0; k<3; k++) 
                    for(int l=0; k<3; l++)
                        ddg[i][j][k][l] = 0;
    }

    void dinv(Vector3f r, float dinv[][3][3]){}
};

class Metric4 {
    public:
    Metric4(){}
    ~Metric4(){}

    virtual Matrix4f val(Vector4f r){
        return Matrix4f::identity();
    }

    Matrix4f inv(Vector4f r){
        return this->val(r).inverse();
    }

    virtual void d(Vector4f r, float dg[][4][4]){
        // X[i][j][k] = g_{ij;k}
        for(int i=0; i<4; i++) 
            for(int j=0; j<4; j++) 
                for(int k=0; k<4; k++) 
                    dg[i][j][k] = 0;
    }

    virtual void dd(Vector4f r, float ddg[][4][4][4]){
        // X[i][j][k][l] = g_{ij;kl}
        for(int i=0; i<4; i++) 
            for(int j=0; j<4; j++) 
                for(int k=0; k<4; k++) 
                    for(int l=0; k<4; l++)
                        ddg[i][j][k][l] = 0;
    }

    void dinv(Vector4f r, float dinv[][4][4]){}
};
