# pragma once
# include <vecmath.h>
# include <functional>
# include "object.hpp"
using namespace std;

class Ball: public Object3{
    public:
    float rad, phi;
    Vector3f o, v1, v2, v3;
    function<bool(Vector3f)> pass;
    float minimal_dt = 3e-5;

    Ball(){}
    Ball(
        float _rad,
        Vector3f _o,
        Texture* _texture,
        Vector3f _v1 = Vector3f(1, 0, 0),
        Vector3f _v2 = Vector3f(0, 1, 0),
        function<bool(Vector3f)> _pass = [](Vector3f pos)->bool{return false;}
    );
    ~Ball(){}

    bool intersect(Ray4 ray_in, float dt_max, Hit4& hit);
};