# pragma once
# include <vecmath.h>
# include "trajectory.hpp"
# include <vector>
# include "utils.hpp"
using namespace std;

class Observer4;

class Prograde: public VectorOnTrajectory4{
    public:
    Observer4* observer;
    Prograde(){}
    ~Prograde(){}
    Prograde(Observer4* _observer);
    void align();
    Vector4f get_dv();
};


class Normal: public VectorOnTrajectory4{
    public:
    Observer4* observer;
    Normal(){}
    ~Normal(){}
    Normal(Observer4* _observer, Vector4f _v);
};

class Observer4: public Trajectory4{
    public:
    Prograde prograde;
    vector<Normal> normals;

    Observer4(){}
    Observer4(Vector4f _r, Vector4f _dr, Geometry4* _geometry, vector<Vector4f> space_direction);
    ~Observer4(){}

    virtual void correction();
    virtual void update_frame(float dt);
    void step(float dt);
};

class GyroscopeObserver4: public Observer4{
    public:
    GyroscopeObserver4(Vector4f _r, Vector4f _dr, Geometry4* _geometry, vector<Vector4f> space_direction);
    void update_frame(float dt);
};

class HorizontalObserver4: public Observer4{
    public:
    HorizontalObserver4(Vector4f _r, Vector4f _dr, Geometry4* _geometry, vector<Vector4f> space_direction);
    void correction();
};