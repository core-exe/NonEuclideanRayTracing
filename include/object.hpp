# pragma once
# include <vecmath.h>
# include <vector>
# include <string>
using namespace std;

class Hit4;
class Ray4;
class Texture;
class Geometry4;

class Object3{// a static object in 4D
    public:
    Texture* texture;
    Geometry4* geometry;
    string name;
    float minimal_dt = 1e-5;

    Object3(){
        name = string("None");
    }
    Object3(Texture* _texture, Geometry4* _geometry);
    ~Object3(){}
    
    virtual bool intersect(Ray4 ray_in, float dt_max, Hit4& hit);
    void get_out_rays(Vector3f in_direction, Vector3f hit_pos, Vector4f hit_r, Hit4& hit);
};