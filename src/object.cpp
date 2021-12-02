# include <vecmath.h>
# include "object.hpp"
# include "hit.hpp"
# include "ray.hpp"
# include "texture.hpp"

Object3::Object3(Texture* _texture){
    texture = _texture;
}

bool intersect(Ray4 ray_in, float dt_max, Hit4& hit){
    // return the delta t given the ray via linear approximation
    // change t
    // push ray into ray_out
    // give a texture to calculate color
    return false;
}