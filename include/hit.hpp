# pragma once
# include <vecmath.h>
# include <vector>
using namespace std;

class Texture;
class Ray4;

class Hit4 {
    public:
    float t;
    vector<Ray4> ray_out; 
    Vector3f hit_pos_texture;
    float in_cosine;
    vector<float> out_cosine;
    Texture* hit_texture;
    Hit4();
    ~Hit4(){}
    Hit4(float _t, vector<Ray4> _ray_out, Vector3f _hit_pos_texture, float _in_cosine, vector<float> _out_cosine, Texture* _hit_texture);
};