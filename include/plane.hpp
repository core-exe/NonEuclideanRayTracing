# pragma once
# include <vecmath.h>
# include "object.hpp"

class Plane: public Object3{
    public:
    Vector3f o, v1, v2;
    Vector3f n;

    Plane();
    Plane(Vector3f _o, Vector3f _v1, Vector3f _v2, Texture* _texture);
    ~Plane();

    bool intersect(Ray4 ray_in, float dt_max, Hit4& hit);
    Vector3f normal(Vector3f hit_pos);
};