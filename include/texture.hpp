# include <vecmath.h>
# include <vector>
# include "geodesic.hpp"
using namespace std;
class Texture {
    public:
    Texture(){}
    ~Texture(){}

    virtual Vector3f color(Vector3f in_pos, Vector3f in_direction, vector<Vector3f> out_direction, vector<Vector3f> out_color){
        // return the color of the in ray
        // given the direction of the out ray, and their colors
        return Vector3f();
    }
};