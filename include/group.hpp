# pragma once
# include <vecmath.h>
# include <vector>
# include "object.hpp"
using namespace std;

class Group: public Object3{
    public:
    vector<Object3*> list;
    Group(){
        list.clear();
    }

    ~Group(){}

    int length(){
        return list.size();
    }

    void add_object(Object3* obj){
        list.push_back(obj);
    }

    bool intersect(Ray4 ray_in, float dt_max, Hit4& hit){
        Hit4 hit_empty = Hit4();
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
};