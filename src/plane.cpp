# include <vecmath.h>
# include <iostream>
# include "plane.hpp"
# include "ray.hpp"
# include "utils.hpp"
# include "hit.hpp"
# include "texture.hpp"
using namespace std;

Plane::Plane(Vector3f _o, Vector3f _v1, Vector3f _v2, Texture* _texture){
    o = _o;
    v1 = _v1;
    v2 = _v2;
    pass = [](Vector3f pos)->bool{return false;};
    n = Vector3f::cross(v1, v2).normalized();
    texture = _texture;
}

Plane::Plane(Vector3f _o, Vector3f _v1, Vector3f _v2, Texture* _texture, function<bool(Vector3f)> _pass){
    o = _o;
    v1 = _v1;
    v2 = _v2;
    pass = _pass;
    n = Vector3f::cross(v1, v2).normalized();
    texture = _texture;
}

bool Plane::intersect(Ray4 ray_in, float dt_max, Hit4& hit){
    Vector3f dr_equiv = ray_in.dr_equivalent(dt_max).yzw();
    Vector3f r_spacial = ray_in.r.yzw();
    float t = Vector3f::dot(o-r_spacial, n) / Vector3f::dot(dr_equiv, n);
    if(t<=minimal_dt || t<=hit.t || t>dt_max)
        return false;
    Vector4f hit_r = ray_in.r + ray_in.dr*t;
    Vector3f hit_pos = Vector3f();
    hit_pos[0] = Vector3f::dot(hit_r.yzw(), v1);
    hit_pos[1] = Vector3f::dot(hit_r.yzw(), v2);
    if(pass(hit_pos))
        return false;
    hit.normal = n;
    hit.t = t;
    get_out_rays(dr_equiv, hit_pos, hit_r, hit);
    //cout << "intersecting with " << name << endl;
    return true;
}