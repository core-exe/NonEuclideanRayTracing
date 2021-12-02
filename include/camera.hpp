# pragma once
# include <vecmath.h>

class Observer4;
class Ray4;

class Camera4{
    public:
    int height, width;
    float f;
    Observer4* observer;
    Camera4(int _height, int _width, float _fov, Observer4* _observer);
    Ray4 get_ray(float w, float h);
};