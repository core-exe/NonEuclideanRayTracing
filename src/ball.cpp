# include <vecmath.h>
# include <functional>
# include <iostream>
# include "object.hpp"
# include "ball.hpp"
# include "ray.hpp"
# include "hit.hpp"
using namespace std;

Ball::Ball(float _rad, Vector3f _o, Texture* _texture, Vector3f _v1, Vector3f _v2, function<bool(Vector3f)> _pass) {
    rad = _rad;
    o = _o;
    v1 = _v1;
    v2 = _v2;
    v3 = Vector3f::cross(v1, v2);
    texture = _texture;
    pass = _pass;

} 

bool Ball::intersect(Ray4 ray_in, float dt_max, Hit4& hit) {
    Vector4f dr_equiv = ray_in.dr_equivalent(dt_max);
    Vector3f v = dr_equiv.yzw();
    Vector3f r = ray_in.r.yzw();
    float v_length = v.length();
    v.normalize();


    bool inside = (o-r).length() < rad;
    Vector3f d = (o-r)-Vector3f::dot(o-r, v) * v;
    if (d.length() >= rad)
        return false;
    float distance = Vector3f::dot(o-r, v) + sqrt(pow(rad, 2)-pow(d.length(), 2)) * (inside ? 1 : -1);
    float dt = distance / v_length;


    if (dt < hit.t || dt < minimal_dt || dt > dt_max)
        return false;
    Vector4f hit_r = ray_in.r + dr_equiv * dt;
    Vector3f hit_relative = (hit_r.yzw() - o).normalized();


    hit.t = dt;
    hit.normal = hit_relative;
    Vector3f hit_pos = Vector3f();
    hit_pos[0] = Vector3f::dot(v1, hit_relative);
    hit_pos[1] = Vector3f::dot(v2, hit_relative);
    hit_pos[2] = Vector3f::dot(v3, hit_relative);
    get_out_rays(dr_equiv.yzw(), hit_pos, hit_r, hit);
    return true;
}