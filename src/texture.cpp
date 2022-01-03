# include <vecmath.h>
# include <vector>
# include "texture.hpp"
# include <iostream>
using namespace std;

vector<Vector2f> Texture::get_out_cosine(Vector3f in_pos, float in_cosine){
    // the first direction is importance
    return vector<Vector2f>();
}

Vector3f Texture::color(Vector3f in_pos, Vector3f in_cosine, vector<float> out_cosine, vector<Vector3f> out_importance){
    // return the color of the in ray
    // given the direction of the out ray, and their colors
    return Vector3f();
}

PureTexture::PureTexture(Vector3f _color){
    texture_color = _color;
}

vector<Vector2f> PureTexture::get_out_cosine(Vector3f in_pos, float in_cosine){
    // the first direction is importance
    return vector<Vector2f>();
}

Vector3f PureTexture::color(Vector3f in_pos, Vector3f in_cosine, vector<float> out_importance, vector<Vector3f> out_color){
    // return the color of the in ray
    // given the direction of the out ray, and their colors
    return texture_color;
}

PureGrid::PureGrid(Vector3f _cell_color, Vector3f _edge_color = Vector3f(1.0), float _grid_length = 1.0, float _ratio = 0.2){
    cell_color = _cell_color;
    edge_color = _edge_color;
    grid_length = _grid_length;
    ratio = _ratio;
}

vector<Vector2f> PureGrid::get_out_cosine(Vector3f in_pos, float in_cosine){
    return vector<Vector2f>();
}

Vector3f PureGrid::color(Vector3f in_pos, Vector3f in_cosine, vector<float> out_importance, vector<Vector3f> out_color){
    in_pos = in_pos / grid_length;
    if(in_pos[0] - floor(in_pos[0]) < ratio / 2 || in_pos[1] - floor(in_pos[1]) < ratio / 2 || ceil(in_pos[0]) - in_pos[0] < ratio / 2 || ceil(in_pos[1]) - in_pos[1] < ratio / 2)
        return edge_color;
    else
        return cell_color;
}

PureSurface::PureSurface(float _n1, float _n2, float _r, float _l, Vector3f _r_color, Vector3f _t_color, Vector3f _l_color){
    // r are intensity reserved for refraction
    // l are intensity reserved for self-illumination
    // the remaining part are decided by Fresnel equations
    n1 = _n1;
    n2 = _n2;
    r = _r;
    l = _l;
    r_color = _r_color;
    t_color = _t_color;
    l_color = _l_color;
}

vector<Vector2f> PureSurface::get_out_cosine(Vector3f in_pos, float in_cosine){
    bool inside = (in_cosine > 0);
    float in_sine = sqrt(1 - pow(in_cosine, 2));
    float out_sine = (inside ? (in_sine / n2 * n1) : (in_sine / n1 * n2));
    bool full_refl = (out_sine >= 1);
    float r_eff, t_eff;
    vector<Vector2f> out_cosine = vector<Vector2f>();
    if (full_refl) {
        out_cosine.push_back(Vector2f(1-l, -in_cosine));
    } else {
        float in_angle = asin(in_sine), out_angle = asin(out_sine);
        float rs = - sin(in_angle - out_angle) / sin(in_angle + out_angle);
        float ts = rs + 1;
        float rp = tan(in_angle - out_angle) / tan(in_angle + out_angle);
        float tp = rp + 1;
        float out_cosine_t = sqrt(1-pow(out_sine, 2)) * (inside ? 1 : -1);
        tp *= (inside ? (n2/n1) : (n1/n2));
        r_eff = r + (1-r-l) * sqrt((pow(rs,2)+pow(rp,2))/2);
        t_eff = (1-r-l) * sqrt((pow(ts,2)+pow(tp,2))/2) * abs(out_cosine_t / in_cosine);
        t_eff *= (inside ? (n1/n2) : (n2/n1));
        out_cosine.push_back(Vector2f(r_eff, -in_cosine));
        out_cosine.push_back(Vector2f(t_eff, out_cosine_t));
    }
    return out_cosine;
}

Vector3f PureSurface::color(Vector3f in_pos, Vector3f in_cosine, vector<float> out_importance, vector<Vector3f> out_color) {
    float r_eff = out_importance[0], t_eff = out_importance[1];
    return (1-r_eff-t_eff)*l_color + r_eff*out_color[0]*r_color + t_eff*out_color[1]*t_color;
}

Surface::Surface(float _n1, float _n2, float _r, float _l, Vector3f _r_color, Vector3f _t_color, Vector3f _l_color) {
    n1_map = [_n1](Vector3f pos)->float{return _n1;};
    n2_map = [_n2](Vector3f pos)->float{return _n2;};
    r_map = [_r](Vector3f pos)->float{return _r;};
    l_map = [_l](Vector3f pos)->float{return _l;};
    r_color_map = [_r_color](Vector3f pos)->Vector3f{return _r_color;};
    t_color_map = [_t_color](Vector3f pos)->Vector3f{return _t_color;};
    l_color_map = [_l_color](Vector3f pos)->Vector3f{return _l_color;};
}

Surface::Surface(
    function<float(Vector3f)> _n1_map,
    function<float(Vector3f)> _n2_map,
    function<float(Vector3f)> _r_map,
    function<float(Vector3f)> _l_map,
    function<Vector3f(Vector3f)> _r_color_map,
    function<Vector3f(Vector3f)> _t_color_map,
    function<Vector3f(Vector3f)> _l_color_map
) {
    n1_map = _n1_map;
    n2_map = _n2_map;
    r_map = _r_map;
    l_map = _l_map;
    r_color_map = _r_color_map;
    t_color_map = _t_color_map;
    l_color_map = _l_color_map;
}

vector<Vector2f> Surface::get_out_cosine(Vector3f in_pos, float in_cosine){
    float n1 = n1_map(in_pos), n2 = n2_map(in_pos), r = r_map(in_pos), l = l_map(in_pos);
    bool inside = (in_cosine > 0);
    float in_sine = sqrt(1 - pow(in_cosine, 2));
    float out_sine = (inside ? (in_sine / n2 * n1) : (in_sine / n1 * n2));
    bool full_refl = (out_sine >= 1);
    float r_eff, t_eff;
    vector<Vector2f> out_cosine = vector<Vector2f>();
    if (full_refl) {
        out_cosine.push_back(Vector2f(1-l, -in_cosine));
        out_cosine.push_back(Vector2f(0, -in_cosine));
    } else {
        float in_angle = asin(in_sine), out_angle = asin(out_sine);
        float rs = - sin(in_angle - out_angle) / sin(in_angle + out_angle);
        float ts = rs + 1;
        float rp = tan(in_angle - out_angle) / tan(in_angle + out_angle);
        float tp = rp + 1;
        float out_cosine_t = sqrt(1-pow(out_sine, 2)) * (inside ? 1 : -1);
        tp *= (inside ? (n2/n1) : (n1/n2));
        r_eff = r + (1-r-l) * sqrt((pow(rs,2)+pow(rp,2))/2);
        t_eff = (1-r-l) * sqrt((pow(ts,2)+pow(tp,2))/2) * abs(out_cosine_t / in_cosine);
        t_eff *= (inside ? (n1/n2) : (n2/n1));
        out_cosine.push_back(Vector2f(r_eff, -in_cosine));
        out_cosine.push_back(Vector2f(t_eff, out_cosine_t));
    }
    return out_cosine;
}

Vector3f Surface::color(Vector3f in_pos, Vector3f in_cosine, vector<float> out_importance, vector<Vector3f> out_color) {
    Vector3f l_color = l_color_map(in_pos), r_color = r_color_map(in_pos), t_color = t_color_map(in_pos);
    float r_eff = out_importance[0], t_eff = out_importance[1];
    return (1-r_eff-t_eff)*l_color + r_eff*out_color[0]*r_color + t_eff*out_color[1]*t_color;
}