# pragma once
#include <vecmath.h>

class Group;
class Geometry4;
class Camera4;
class Ray4;
class Hit4;
class Image;

class Scene4 {
    public:
    Geometry4* geometry;
    Group* group;
    Camera4* camera;
    float eps = 0.0001;
    double total_time = 0.0;
    int sample = 1;

    Scene4(){}
    Scene4(Geometry4* _geometry, Group* _group, Camera4* _camera);
    ~Scene4(){}

    float get_dt_geometry(Vector4f r, Vector4f dr);
    Vector3f get_color(Ray4 ray);
    double move_camera(float delta_t);
    Image shot();
};