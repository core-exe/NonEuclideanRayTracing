# include <vecmath.h>
# include <vector>
# include <iostream>
# include "group.hpp"
# include "hit.hpp"
# include "ray.hpp"
# include "object.hpp"
# include "geometry.hpp"
using namespace std;

Group::Group(){
    list.clear();
}

Group::Group(Geometry4* _geometry){
    list.clear();
    geometry = _geometry;
}

int Group::length(){
    return list.size();
}

void Group::add_object(Object3* obj){
    list.push_back(obj);
    obj->geometry = geometry;
}

bool Group::intersect(Ray4 ray_in, float dt_max, Hit4& hit){
    float dt_min = 1e38;
    bool ret = false;
    for(int i=0; i<length(); i++){
        Hit4 hit_empty = Hit4();
        if(list[i]->intersect(ray_in, dt_max, hit_empty) && hit_empty.t<dt_min){
            dt_min = hit_empty.t;
            hit = hit_empty;
            ret = true;
        }
    }
    return ret;
}