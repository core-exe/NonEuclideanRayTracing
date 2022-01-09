# pragma once
# include <vecmath.h>
# include <vector>
# include <functional>
using namespace std;

class Geometry4;
class Trajectory4;

class VectorOnTrajectory4{
    public:
    Trajectory4* trajectory;
    Vector4f v;

    VectorOnTrajectory4();
    VectorOnTrajectory4(Trajectory4* _trajectory, Vector4f _v);
    ~VectorOnTrajectory4(){}

    virtual void step(float dt){}
    virtual Vector4f get_dv();
    Vector4f covariant_derivative_freeze();
};

class Trajectory4{
    public:
    Vector4f r, dr;
    Geometry4* geometry;
    vector<VectorOnTrajectory4> attached_vectors;
    Matrix4f g;
    float t, dg[4][4][4], gamma[4][4][4];

    Trajectory4(){}
    Trajectory4(Vector4f _r, Vector4f _dr, Geometry4* _geometry);
    ~Trajectory4(){}

    virtual Vector4f get_ddr();
    void attach_vector(VectorOnTrajectory4 v);
    void update_vectors(float dt);
    void update_local_geometry();
    virtual void update_coor(float dt);
    virtual void step(float dt);
};

class DifferentialTrajectory: public virtual Trajectory4{
    public:
    function<Vector4f(Vector4f, Vector4f, Matrix4f, float[4][4][4])> motion_equation; // (r,v,g,Gamma) -> a
    Vector4f ddr;
    bool is_ddr_update;

    DifferentialTrajectory(){}
    DifferentialTrajectory(Vector4f _r, Vector4f _dr, Geometry4* _geometry, function<Vector4f(Vector4f, Vector4f, Matrix4f, float[4][4][4])> _motion_equation);
    Vector4f get_ddr();
    void update_coor(float dt);
};

class ParametricTrajectory: public virtual Trajectory4{
    public:
    function<Vector4f(float)> r_func, dr_func, ddr_func; // keeping it consistent is the user's responsibility.

    ParametricTrajectory(){}
    ParametricTrajectory(Geometry4* _geometry, function<Vector4f(float)> _r_func, function<Vector4f(float)> _dr_func, function<Vector4f(float)> _ddr_func);
    Vector4f get_ddr();
    void update_coor(float dt);
};
