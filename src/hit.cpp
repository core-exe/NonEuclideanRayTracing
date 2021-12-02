# include <vecmath.h>
# include <vector>
# include "hit.hpp"
# include "texture.hpp"
# include "ray.hpp"
using namespace std;

Hit4::Hit4(){
    t=0;
}

Hit4::Hit4(float _t, vector<Ray4> _ray_out, Vector3f _hit_pos_texture, Vector3f _in_direction, vector<Vector3f> _out_direction, Texture* _hit_texture) {
    t = _t;
    ray_out = _ray_out;
    hit_pos_texture = _hit_pos_texture;
    in_direction = _in_direction;
    out_direction = _out_direction;
    hit_texture = _hit_texture;
}