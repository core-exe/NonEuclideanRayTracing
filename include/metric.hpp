# pragma once
# include <vecmath.h>

class Metric4 {
    public:
    Metric4(){}
    ~Metric4(){}

    virtual Matrix4f val(Vector4f r);
    Matrix4f inv(Vector4f r);
    virtual void d(Vector4f r, float dg[4][4][4]);
};