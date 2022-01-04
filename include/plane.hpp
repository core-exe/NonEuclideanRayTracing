# pragma once
# include <vecmath.h>
# include <functional>
# include "object.hpp"
using namespace std;

class Plane: public Object3{
    public:
    Vector3f o, v1, v2;
    Vector3f n;
    function<bool(Vector3f)> pass;

    Plane();
    Plane(Vector3f _o, Vector3f _v1, Vector3f _v2, Texture* _texture);
    Plane(Vector3f _o, Vector3f _v1, Vector3f _v2, Texture* _texture, function<bool(Vector3f)> pass);
    ~Plane();

    bool intersect(Ray4 ray_in, float dt_max, Hit4& hit);
};