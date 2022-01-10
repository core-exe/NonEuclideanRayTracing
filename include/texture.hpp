# pragma once
# include <vecmath.h>
# include <vector>
# include <functional>
using namespace std;

class Image;

class Texture {
    public:
    Texture(){}
    ~Texture(){}

    virtual vector<Vector2f> get_out_cosine(Vector3f in_pos, float in_cosine);
    virtual Vector3f color(Vector3f in_pos, Vector3f in_cosine, vector<float> out_importance, vector<Vector3f> out_color);
};

class PureTexture: public Texture{
    public:
    Vector3f texture_color;
    PureTexture(){}
    PureTexture(Vector3f _color);
    ~PureTexture(){}

    vector<Vector2f> get_out_cosine(Vector3f in_pos, float in_cosine);
    Vector3f color(Vector3f in_pos, Vector3f in_cosine, vector<float> out_importance, vector<Vector3f> out_color);
};

class PureGrid: public Texture{
    public:
    Vector3f cell_color, edge_color;
    float grid_length, ratio;
    PureGrid(Vector3f _cell_color, Vector3f _edge_color, float _grid_length, float _ratio);
    ~PureGrid();

    vector<Vector2f> get_out_cosine(Vector3f in_pos, float in_cosine);
    Vector3f color(Vector3f in_pos, Vector3f in_cosine, vector<float> out_importance, vector<Vector3f> out_color);
};

class Surface: public Texture{
    public:
    function<float(Vector3f)> n1_map, n2_map, r_map, l_map;
    function<Vector3f(Vector3f)> r_color_map, t_color_map, l_color_map;
    Surface(){}
    Surface(float _n1, float _n2, float _r, float _l, Vector3f _r_color, Vector3f _t_color, Vector3f _l_color);
    Surface(
        function<float(Vector3f)> _n1_map,
        function<float(Vector3f)> _n2_map,
        function<float(Vector3f)> _r_map,
        function<float(Vector3f)> _l_map,
        function<Vector3f(Vector3f)> _r_color_map,
        function<Vector3f(Vector3f)> _t_color_map,
        function<Vector3f(Vector3f)> _l_color_map);
    ~Surface();

    vector<Vector2f> get_out_cosine(Vector3f in_pos, float in_cosine);
    Vector3f color(Vector3f in_pos, Vector3f in_cosine, vector<float> out_importance, vector<Vector3f> out_color);
};

class TerminalTexture: public Texture { // no reflection and transmission.
    public:
    function<Vector3f(Vector3f, Image*)> color_map;
    Image* img;
    TerminalTexture(){}
    TerminalTexture(function<Vector3f(Vector3f, Image*)> _color_map, Image* _img);
    ~TerminalTexture(){}

    vector<Vector2f> get_out_cosine(Vector3f in_pos, float in_cosine);
    Vector3f color(Vector3f in_pos, Vector3f in_cosine, vector<float> out_importance, vector<Vector3f> out_color);
};