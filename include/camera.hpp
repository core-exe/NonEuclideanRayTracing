# pragma once
# include <vecmath.h>
# include "observer.hpp"
# include "ray.hpp"

class Camera4{
    public:
    int height, width;
    float f;
    Observer4* observer;
    
    Camera4(int _height, int _width, float _fov, Observer4* _observer){
        height = _height;
        width = _width;
        f = atan(_fov/2);
        observer = _observer;
    }

    Ray4 get_ray(float w, float h){
        Vector2f image_pos = Vector2f(height/2.-h, w-width/2.)/(height/2.);
        Vector3f ray_direction_spacial = Vector3f(1, image_pos*f).normalized();
        Vector4f ray_direction_rel = Vector4f(-1, ray_direction_spacial).normalized();
        Vector4f ray_direction = ray_direction_rel[0]*observer->prograde.v;
        for(int i=0; i<3; i++)
            ray_direction = ray_direction + ray_direction_rel[i]*observer->normals[i].v;
        return Ray4(observer->r, ray_direction, observer->geometry);
    }
};