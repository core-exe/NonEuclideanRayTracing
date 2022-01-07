# pragma once
# include <vecmath.h>
# include <vector>
# include "trajectory.hpp"
using namespace std;

class Geometry4;
class Ray4: public Trajectory4 {
    public:
    bool is_ddr_update;
    Vector4f ddr;
    int tracking_step;
    int max_tracking_step = 16384;
    float importance;
    int depth;

    Ray4(){}
    Ray4(Vector4f _r, Vector4f _dr, Geometry4* _geometry, float _importance = 1.);
    Ray4(Vector4f _r, Vector3f spacial_dir, Geometry4* _geometry, float _importance = 1.);

    Vector4f get_ddr();
    void update_coor(float dt);
    virtual void step(float dt);
    Vector4f dr_equivalent(float dt); // TODO
    float inv_frequency(); // TODO
};



