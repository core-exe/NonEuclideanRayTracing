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