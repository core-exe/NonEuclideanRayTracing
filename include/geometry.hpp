# pragma once
# include <vecmath.h>

class Hit4;
class Ray4;
class Christoffel4;
class Metric4;

class Geometry4 {
    public:
    Metric4* g;
    Christoffel4* gamma;
    Geometry4(Metric4* _g);
    virtual float get_dt(Vector4f r, Vector4f dr);
    virtual bool is_terminal(Ray4 ray, Hit4& hit);
};