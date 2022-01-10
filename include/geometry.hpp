# pragma once
# include <vecmath.h>
# include "texture.hpp"

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

    virtual float get_dt_ray(Ray4* trajectory);
    virtual float get_dt_observer(Observer4* observer);
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
    float ray_eps, obs_eps;
    float stop_eps;
    float r_min, r_max;
    Texture *max_step_texture, *horizon_texture, *outer_texture;

    SchwartzchildGeometry(float _radius, float _ray_eps = 1e-3, float _obs_eps = 2e-4, float _stop_eps = 1e-3, float _r_min = 0.075, float _r_max = 1e3, Texture* _max_step_texture = new PureTexture(Vector3f()), Texture* _horizon_texture = new PureTexture(Vector3f()), Texture* _outer_texture = new PureTexture(Vector3f(0.05)));

    float get_dt_ray(Ray4* trajectory);
    float get_dt_observer(Observer4* observer);
    bool is_terminal(Ray4 ray, Hit4& hit);
    bool is_terminal(Observer4* observer);
};