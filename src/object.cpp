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
    name = string("None");
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
    //cout << "get_out_rays" << endl;
    Vector4f et = Vector4f(1, Vector3f());
    Vector4f n = Vector4f(0, normal(hit_pos)), in_direction_4d = Vector4f(0, in_direction);
    Matrix4f g = geometry->g->val(hit_r);


    et = et / sqrt(-g(0,0));
    n = n + dot(n, et, g) * et;
    n = n / sqrt(dot(n, n, g));
    in_direction_4d = in_direction_4d + dot(in_direction_4d, et, g) * et;
    in_direction_4d = in_direction_4d / sqrt(dot(in_direction_4d, in_direction_4d, g));

    //printf("in direction: %.4f, %.4f, %.4f. %.4f\n", in_direction_4d[0], in_direction_4d[1], in_direction_4d[2], in_direction_4d[3]);
    //printf("normal: %.4f, %.4f, %.4f. %.4f\n", n[0], n[1], n[2], n[3]);


    float in_cos = dot(n, in_direction_4d, g); // negative, toward the PureSurface
    Vector4f tangent = (in_direction_4d - in_cos * n);
    tangent = tangent / sqrt(dot(tangent, tangent, g));
    vector<Vector2f> out_cos = texture->get_out_cosine(hit_pos, in_cos);
    vector<Ray4> out_ray = vector<Ray4>();
    for(int i=0; i<out_cos.size(); i++){
        Vector3f space_direction = (n*out_cos[i][1] + tangent*sqrt(1-pow(out_cos[i][1], 2))).yzw();
        //printf("out direction: %.4f, %.4f, %.4f, importance: %.4f\n", space_direction[0], space_direction[1], space_direction[2], out_cos[i][0]);
        hit.out_importance.push_back(out_cos[i][0]);
        out_ray.push_back(Ray4(hit_r, space_direction, geometry, out_cos[i][0]*hit.importance));
        hit.out_cosine.push_back(out_cos[i][1]);
    }
    hit.ray_out = out_ray;
    hit.in_cosine = in_cos;
    hit.hit_texture = texture;
    hit.hit_pos_texture = hit_pos;
}