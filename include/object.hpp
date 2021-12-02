# pragma once
# include <vecmath.h>

class Hit4;
class Ray4;
class Texture;

class Object3{// a static object in 4D
    public:
    Texture* texture;

    Object3(){}
    Object3(Texture* _texture);
    ~Object3(){}
    
    virtual bool intersect(Ray4 ray_in, float dt_max, Hit4& hit);
};