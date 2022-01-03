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
    float importance;
    vector<float> out_cosine, out_importance;
    Texture* hit_texture;
    Hit4();
    ~Hit4(){}
};