# pragma once
# include <vecmath.h>
# include <vector>
# include "trajectory.hpp"
using namespace std;

class Geometry4;
class Geodesic4: public Trajectory4 {
    public:
    bool is_ddr_update;
    Vector4f ddr;
    int tracking_step;
    int max_tracking_step = 16384;

    Geodesic4(){}
    Geodesic4(Vector4f _r, Vector4f _dr, Geometry4* _geometry);

    Vector4f get_ddr();
    void update_coor(float dt);
    virtual void step(float dt);
};



