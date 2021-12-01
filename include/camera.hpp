# pragma once
# include <vecmath.h>
# include "observer.hpp"

class Camera4{
    public:
    int height, width;
    float fov;
    Observer4* observer;
    
};