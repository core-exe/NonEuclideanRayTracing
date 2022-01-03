# include <vecmath.h>
# include <vector>
# include "hit.hpp"
# include "texture.hpp"
# include "ray.hpp"
using namespace std;

Hit4::Hit4(){
    t=0;
    out_importance = vector<float>();
    out_cosine = vector<float>();
}

Hit4::Hit4(float _t, vector<Ray4> _ray_out, Vector3f _hit_pos_texture, float _in_cosine, vector<float> _out_cosine, vector<float> _out_importance, Texture* _hit_texture){
    t = _t;
    ray_out = _ray_out;
    hit_pos_texture = _hit_pos_texture;
    in_cosine = _in_cosine;
    out_cosine = _out_cosine;
    hit_texture = _hit_texture;
    out_importance = _out_importance;
}