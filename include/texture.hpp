# pragma once
# include <vecmath.h>
# include <vector>
using namespace std;

class Texture {
    public:
    Texture(){}
    ~Texture(){}

    virtual vector<Vector2f> get_out_cosine(Vector3f in_pos, float in_cosine);
    virtual Vector3f color(Vector3f in_pos, Vector3f in_cosine, vector<float> get_out_cosine, vector<Vector3f> out_color);
};

class PureTexture: public Texture{
    public:
    Vector3f texture_color;
    PureTexture(){}
    PureTexture(Vector3f _color);
    ~PureTexture(){}

    vector<Vector2f> get_out_cosine(Vector3f in_pos, float in_cosine);
    Vector3f color(Vector3f in_pos, Vector3f in_cosine, vector<float> get_out_cosine, vector<Vector3f> out_color);
};