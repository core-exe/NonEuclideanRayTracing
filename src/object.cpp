# include <vecmath.h>
# include "object.hpp"
# include "hit.hpp"
# include "ray.hpp"
# include "texture.hpp"
# include "utils.hpp"
# include "geometry.hpp"

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

Vector3f Object3::rel_direction(Vector3f v){
    return v;
}

Vector3f Object3::from_rel_direction(Vector3f v){
    return v;
}

vector<Ray4> Object3::get_out_rays(Vector3f abs_direction, Vector3f hit_pos, Vector4f hit_r){
    Vector3f rel_in = rel_direction(abs_direction);
    vector<Vector4f> out_directions = texture->get_out_directions(abs_direction, hit_pos);
    vector<Ray4> out_rays = vector<Ray4>();
    for(int i=0; i<out_directions.size(); i++){
        Vector3f spacial_direction = from_rel_direction(out_directions[i].yzw());
        float importance = out_directions[i][0];
        out_rays.push_back(Ray4(hit_r, spacial_direction, geometry, importance));
    }
    return out_rays;
}