# include <vecmath.h>
# include <vector>
# include "hit.hpp"
# include "geodesic.hpp"
using namespace std;

class Object3{// a static object in 4D
    public:
    Object3(){}
    ~Object3(){}
    Texture* texture;
    virtual bool intersect(Ray4 ray_in, float dt_max, Hit4& hit){
        // return the delta t given the ray via linear approximation
        // change t
        // push ray into ray_out
        // give a texture to calculate color
        return false;
    }
};