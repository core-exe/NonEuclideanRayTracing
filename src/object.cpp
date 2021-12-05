# include <vecmath.h>
# include <iostream>
# include "object.hpp"
# include "hit.hpp"
# include "ray.hpp"
# include "texture.hpp"
# include "utils.hpp"
# include "geometry.hpp"
# include "metric.hpp"
using namespace std;

Object3::Object3(Texture* _texture, Geometry4* _geometry){
    texture = _texture;
    geometry = _geometry;
}

bool Object3::intersect(Ray4 ray_in, float dt_max, Hit4& hit){
    // return the delta t given the ray via linear approximation
    // change t
    // push ray into ray_out
    // give a texture to calculate color
    return false;
}

Vector3f Object3::normal(Vector3f hit_pos){
    return Vector3f();
}

void Object3::get_out_rays(Vector3f in_direction, Vector3f hit_pos, Vector4f hit_r, Hit4 &hit){
    Vector3f n = normal(hit_pos);
    Matrix4f g = geometry->g->val(hit_r);
    n = n / sqrt(dot(n, n, g));
    in_direction = in_direction / sqrt(dot(in_direction, in_direction, g));
    float in_cos = dot(n, in_direction, g); // negative.
    Vector3f tangent = (in_direction - in_cos * n);
    tangent = tangent / sqrt(dot(tangent, tangent, g));
    vector<Vector2f> out_cos = texture->get_out_cosine(hit_pos, in_cos);
    vector<Ray4> out_ray = vector<Ray4>();
    for(int i=0; i<out_cos.size(); i++){
        Vector3f space_direction = n*out_cos[i][1] + tangent*sqrt(1-pow(out_cos[i][1], 2));
        out_ray.push_back(Ray4(hit_r, space_direction, geometry, out_cos[i][0]));
        hit.out_cosine.push_back(out_cos[i][1]);
    }
    hit.ray_out = out_ray;
    hit.in_cosine = in_cos;
    hit.hit_texture = texture;
    hit.hit_pos_texture = hit_pos;
}