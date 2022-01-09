# pragma once
# include <vecmath.h>

class Hit4;
class Ray4;
class Christoffel4;
class Metric4;
class Observer4;
class Trajectory4;

class Geometry4 {
    public:
    Metric4* g;
    Christoffel4* gamma;

    Geometry4(){}
    Geometry4(Metric4* _g);
    ~Geometry4(){}

    virtual float get_dt(Trajectory4* trajectory);
    virtual bool is_terminal(Ray4 ray, Hit4& hit);
    virtual bool is_terminal(Observer4* observer);
};

class FlatGeometry: public Geometry4 {
    public:
    float max_r;
    
    FlatGeometry(float _max_r = 1e4);
    ~FlatGeometry();

    bool is_terminal(Ray4 ray, Hit4& hit);
};

class SchwartzchildGeometry: public Geometry4{
    public:
    float radius;
    float dt_eps;
    float stop_eps;
    float r_min, r_max;

    SchwartzchildGeometry(float radius, float _dt_eps = 1e-3, float _stop_eps = 1e-3, float _r_min = 0.01, float _r_max = 100);

    float get_dt(Trajectory4* trajectory);
    bool is_terminal(Ray4 ray, Hit4& hit);
    bool is_terminal(Observer4* observer);
};