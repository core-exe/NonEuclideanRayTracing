# pragma once
# include <vecmath.h>
# include <vector>
# include "object.hpp"
using namespace std;

class Ray4;
class Hit4;

class Group: public Object3{
    public:
    vector<Object3*> list;
    Group();
    ~Group(){}

    int length();
    void add_object(Object3* obj);
    bool intersect(Ray4 ray_in, float dt_max, Hit4& hit);
};