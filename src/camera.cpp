# include <vecmath.h>
# include <iostream>
# include <cstdio>
# include "camera.hpp"
# include "ray.hpp"
# include "observer.hpp"

using namespace std;

Camera4::Camera4(int _height, int _width, float _fov, Observer4* _observer, Matrix3f _perspective){
    height = _height;
    width = _width;
    f = atan(_fov/2);
    observer = _observer;
    observer->correction();
    perspective = _perspective;
}

Ray4 Camera4::get_ray(float w, float h){
    Vector2f image_pos = Vector2f(h-height/2., w-width/2.)/(height/2.);
    Vector3f ray_direction_spacial = Vector3f(1, image_pos*f).normalized();
    ray_direction_spacial = perspective * ray_direction_spacial;
    Vector4f ray_direction_rel = Vector4f(-1, ray_direction_spacial).normalized();
    Vector4f ray_direction = ray_direction_rel[0]*observer->prograde.v;
    for(int i=1; i<4; i++){
        ray_direction = ray_direction + ray_direction_rel[i]*(observer->normals[i-1].v);
    }
    Ray4 ray = Ray4(observer->r, ray_direction, observer->geometry);
    return ray;
}