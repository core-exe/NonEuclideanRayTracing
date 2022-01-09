# pragma once
# include <vecmath.h>
# include "trajectory.hpp"
# include <vector>
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

class Observer4: public virtual Trajectory4{
    public:
    Prograde prograde;
    vector<Normal> normals;

    Observer4(){}
    Observer4(Vector4f _r, Vector4f _dr, Geometry4* _geometry, vector<Vector4f> space_direction);
    ~Observer4(){}

    virtual void correction();
    virtual void update_frame(float dt);
    virtual void step(float dt);
    float get_proper_time(float dt);
};

class GyroscopeObserver4: public Observer4{
    public:
    GyroscopeObserver4(){}
    GyroscopeObserver4(Vector4f _r, Vector4f _dr, Geometry4* _geometry, vector<Vector4f> space_direction);
    void update_frame(float dt);
};

class HorizontalObserver4: public Observer4{
    public:
    HorizontalObserver4(){}
    HorizontalObserver4(Vector4f _r, Vector4f _dr, Geometry4* _geometry, vector<Vector4f> space_direction);
    void correction();
};

class GyroDifferential: public GyroscopeObserver4, public DifferentialTrajectory{
    GyroDifferential(Vector4f _r, Vector4f _dr, Geometry4* _geometry, function<Vector4f(Vector4f, Vector4f, Matrix4f, float[4][4][4])> _motion_equation, vector<Vector4f> space_direction);
    void step(float dt);
};

class HorizontalDifferential: public HorizontalObserver4, public DifferentialTrajectory{
    HorizontalDifferential(Vector4f _r, Vector4f _dr, Geometry4* _geometry, function<Vector4f(Vector4f, Vector4f, Matrix4f, float[4][4][4])> _motion_equation, vector<Vector4f> space_direction);
    void step(float dt);
};

class GyroParametric: public GyroscopeObserver4, public ParametricTrajectory{
    GyroParametric(Geometry4* _geometry, function<Vector4f(float)> _r_func, function<Vector4f(float)> _dr_func, function<Vector4f(float)> _ddr_func, vector<Vector4f> space_direction);
    void step(float dt);
};

class HorizontalParametric: public HorizontalObserver4, public ParametricTrajectory{
    HorizontalParametric(Geometry4* _geometry, function<Vector4f(float)> _r_func, function<Vector4f(float)> _dr_func, function<Vector4f(float)> _ddr_func, vector<Vector4f> space_direction);
    void step(float dt);
};
