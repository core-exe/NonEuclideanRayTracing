# include <vecmath.h>
# include "geometry.hpp"
# include "metric.hpp"
# include "christoffel.hpp"
# include "ray.hpp"
# include "hit.hpp"
# include "observer.hpp"

Geometry4::Geometry4(Metric4* _g) {
    g = _g;
    gamma = new Christoffel4(_g);
}

float Geometry4::get_dt(Vector4f r, Vector4f dr) {
    return 1.0;
}

bool Geometry4::is_terminal(Ray4 ray, Hit4& hit){
    return false;
}

bool Geometry4::is_terminal(Observer4* ray){
    return false;
}