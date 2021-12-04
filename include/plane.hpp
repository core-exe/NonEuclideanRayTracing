# pragma once
# include "object.hpp"

class Plane: public Object3{
    public:
    Vector3f o, v1, v2;
    Vector3f n;
    bool intersect(Ray4 ray_in, float dt_max, Hit4& hit);
};