# pragma once
#include <vecmath.h>
#include <string>
using namespace std;

class Group;
class Geometry4;
class Camera4;
class Ray4;
class Hit4;
class Image;
class Trajectory4;

class Scene4 {
    public:
    Geometry4* geometry;
    Group* group;
    Camera4* camera;
    float eps = 0.0001;
    double total_time = 0.0;
    int sample = 1;
    float intersect_dt_ratio = 1.2;
    int max_depth = 4;

    Scene4(){}
    Scene4(Geometry4* _geometry, Group* _group, Camera4* _camera);
    ~Scene4(){}

    float get_dt_geometry(Trajectory4* trajectory);
    Vector3f get_color(Ray4 ray, bool direct, bool debug);
    Vector3f get_color(float x, float y, bool debug);
    double move_camera(float delta_t);
    bool scene_end();
    Image shot(int save_interval = -1, string save_name = string("tmp"));
};