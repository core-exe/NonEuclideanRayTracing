# pragma once
# include <vecmath.h>
# include <vector>
using namespace std;

class Hit4;
class Ray4;
class Texture;
class Geometry4;

class Object3{// a static object in 4D
    public:
    Texture* texture;
    Geometry4* geometry;

    Object3(){}
    Object3(Texture* _texture, Geometry4* _geometry);
    ~Object3(){}
    
    virtual bool intersect(Ray4 ray_in, float dt_max, Hit4& hit);
    virtual Vector3f rel_direction(Vector3f v);
    virtual Vector3f from_rel_direction(Vector3f v);
    vector<Ray4> get_out_rays(Vector3f abs_direction, Vector3f hit_pos, Vector4f hit_r);
};