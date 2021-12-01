# pragma once
# include <vecmath.h>
# include "metric.hpp"
# include "christoffel.hpp"
# include "hit.hpp"
# include "ray.hpp"

class Hit4;
class Ray4;
class Geometry3 {
    public:
    Metric3* g;
    Christoffel3* gamma;
    Geometry3(Metric3* _g) {
        g = _g;
        gamma = new Christoffel3(_g);
    }
    virtual float get_dt(Vector3f r, Vector3f dr) {
        return 1.0;
    }
};

class Geometry4 {
    public:
    Metric4* g;
    Christoffel4* gamma;
    Geometry4(Metric4* _g) {
        g = _g;
        gamma = new Christoffel4(_g);
    }
    virtual float get_dt(Vector4f r, Vector4f dr) {
        return 1.0;
    }
    virtual bool is_terminal(Ray4 ray, Hit4& hit){
        return false;
    }
};