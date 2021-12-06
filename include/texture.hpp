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

class PureGrid: public Texture{
    public:
    Vector3f cell_color, edge_color;
    float grid_length, ratio;
    PureGrid(Vector3f _cell_color, Vector3f _edge_color, float _grid_length, float _ratio);
    ~PureGrid();

    vector<Vector2f> get_out_cosine(Vector3f in_pos, float in_cosine);
    Vector3f color(Vector3f in_pos, Vector3f in_cosine, vector<float> get_out_cosine, vector<Vector3f> out_color);
};