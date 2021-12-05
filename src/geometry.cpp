# include <vecmath.h>
# include <iostream>
# include "geometry.hpp"
# include "metric.hpp"
# include "christoffel.hpp"
# include "ray.hpp"
# include "hit.hpp"
# include "observer.hpp"
# include "trajectory.hpp"
# include "texture.hpp"
using namespace std;

Geometry4::Geometry4(Metric4* _g) {
    g = _g;
    gamma = new Christoffel4(_g);
}

float Geometry4::get_dt(Trajectory4* trajectory) {
    return 1.0;
}

bool Geometry4::is_terminal(Ray4 ray, Hit4& hit){
    return false;
}

bool Geometry4::is_terminal(Observer4* ray){
    return false;
}

SchwartzchildGeometry::SchwartzchildGeometry(float _radius, float _dt_eps, float _stop_eps, float _r_min, float _r_max){
    g = new SchwartzchildMetric(_radius);
    gamma = new Christoffel4(g);
    radius = _radius;
    dt_eps = _dt_eps;
    stop_eps = _stop_eps;
    r_min = _r_min;
    r_max = _r_max;
}

float SchwartzchildGeometry::get_dt(Trajectory4* trajectory) {
    float r = trajectory->r.yzw().length();
    float v = trajectory->dr.yzw().length();
    float a = trajectory->get_ddr().yzw().length();
    return min(min(dt_eps*r/v, sqrt(2*dt_eps*r/a)), dt_eps*r/(-trajectory->dr[0]));
}

bool SchwartzchildGeometry::is_terminal(Ray4 ray, Hit4& hit){
    float r = ray.r.yzw().length();
    float v = ray.dr.yzw().length();
    if(abs(v/ray.dr[0])<stop_eps)
        hit.hit_texture = new PureTexture(Vector3f(1.,0.,0.));
    else
        hit.hit_texture = new PureTexture();
    return v<stop_eps || r>r_max || ray.tracking_step>=ray.max_tracking_step;
}

bool SchwartzchildGeometry::is_terminal(Observer4* observer4){
    float r = observer4->r.yzw().length();
    return r<r_min || r>r_max;
}
