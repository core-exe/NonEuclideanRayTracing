# include <vecmath.h>
# include <vector>
# include "texture.hpp"
using namespace std;

vector<Vector2f> Texture::get_out_cosine(Vector3f in_pos, float in_cosine){
    // the first direction is importance
    return vector<Vector2f>();
}

Vector3f Texture::color(Vector3f in_pos, Vector3f in_cosine, vector<float> get_out_cosine, vector<Vector3f> out_color){
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

Vector3f PureTexture::color(Vector3f in_pos, Vector3f in_cosine, vector<float> get_out_cosine, vector<Vector3f> out_color){
    // return the color of the in ray
    // given the direction of the out ray, and their colors
    return texture_color;
}

PureGrid::PureGrid(Vector3f _cell_color = Vector3f(0.0), Vector3f _edge_color = Vector3f(1.0), float _grid_length = 1.0, float _ratio = 0.2){
    cell_color = _cell_color;
    edge_color = _edge_color;
    grid_length = _grid_length;
    ratio = _ratio;
}

vector<Vector2f> PureGrid::get_out_cosine(Vector3f in_pos, float in_cosine){
    return vector<Vector2f>();
}

Vector3f PureGrid::color(Vector3f in_pos, Vector3f in_cosine, vector<float> get_out_cosine, vector<Vector3f> out_color){
    in_pos = in_pos / grid_length;
    if(in_pos[0] - floor(in_pos[0]) < ratio / 2 || in_pos[1] - floor(in_pos[1]) < ratio / 2 || ceil(in_pos[0]) - in_pos[0] < ratio / 2 || ceil(in_pos[1]) - in_pos[1] < ratio / 2)
        return edge_color;
    else
        return cell_color;
}