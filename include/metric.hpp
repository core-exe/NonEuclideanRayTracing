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

class SchwartzchildMetric: public Metric4 {
    public:
    float radius=1.0;
    SchwartzchildMetric(){}
    SchwartzchildMetric(float _radius);
    ~SchwartzchildMetric(){}

    Matrix4f val(Vector4f r);
    void d(Vector4f r, float dg[4][4][4]);
};