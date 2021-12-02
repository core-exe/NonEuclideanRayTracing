# pragma once
# include <vecmath.h>
# include <vector>
using namespace std;

class Texture {
    public:
    Texture(){}
    ~Texture(){}

    virtual Vector3f color(Vector3f in_pos, Vector3f in_direction, vector<Vector3f> out_direction, vector<Vector3f> out_color);
};