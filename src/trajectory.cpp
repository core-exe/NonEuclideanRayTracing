# include <vecmath.h>
# include <vector>
# include <functional>
# include "trajectory.hpp"
# include "geometry.hpp"
# include "metric.hpp"
# include "christoffel.hpp"
using namespace std;

VectorOnTrajectory4::VectorOnTrajectory4(){
    v = Vector4f();
}

VectorOnTrajectory4::VectorOnTrajectory4(Trajectory4* _trajectory, Vector4f _v){
    trajectory = _trajectory;
    v = _v;
}

Vector4f VectorOnTrajectory4::get_dv(){
    return Vector4f();
}

Vector4f VectorOnTrajectory4::covariant_derivative_freeze(){
    Vector4f dr = trajectory->dr;
    Vector4f Dv = Vector4f();
    float gamma[4][4][4];
    for(int i=0; i<4; i++)
        for(int j=0; j<4; j++)
            for(int k=0; k<4; k++)
                Dv[i] += v[j]*dr[k];
    return Dv;
}

Trajectory4::Trajectory4(Vector4f _r, Vector4f _dr, Geometry4* _geometry){
    r = _r;
    dr = _dr;
    geometry = _geometry;
    attached_vectors = vector<VectorOnTrajectory4>();
    update_local_geometry();
}

Vector4f Trajectory4::get_ddr(){
    // calculate ddr
    return Vector4f();
}

void Trajectory4::attach_vector(VectorOnTrajectory4 v){
    attached_vectors.push_back(v);
}

void Trajectory4::update_vectors(float dt){
    for(int i=0; i<attached_vectors.size(); i++){
        attached_vectors[i].step(dt);
    }
}

void Trajectory4::update_local_geometry(){
    g = geometry->g->val(r);
    geometry->g->d(r, dg);
    geometry->gamma->val(r, gamma);
}

void Trajectory4::update_coor(float dt){
    // change r, dr according to the time interval dt
}

void Trajectory4::step(float dt){
    update_vectors(dt);
    update_coor(dt);
    update_local_geometry();
}

DifferentialTrajectory::DifferentialTrajectory(Vector4f _r, Vector4f _dr, Geometry4* _geometry, function<Vector4f(Vector4f, Vector4f, Matrix4f, float[4][4][4])> _motion_equation) {
    t = 0;
    r = _r;
    dr = _dr;
    geometry = _geometry;
    motion_equation = _motion_equation;
    is_ddr_update = false;
    attached_vectors = vector<VectorOnTrajectory4>();
    update_local_geometry();
}

Vector4f DifferentialTrajectory::get_ddr() {
    if(is_ddr_update){
        return ddr;
    }
    is_ddr_update = true;
    ddr = motion_equation(r, dr, g, gamma);
    return ddr;
}

void DifferentialTrajectory::update_coor(float dt){
    if(!is_ddr_update)
        get_ddr();
    r = r + dr * dt + 0.5 * ddr * dt * dt;
    dr = dr + ddr * dt;
    t = t + dt;
}

ParametricTrajectory::ParametricTrajectory(Geometry4* _geometry, function<Vector4f(float)> _r_func, function<Vector4f(float)> _dr_func, function<Vector4f(float)> _ddr_func) {
    geometry = _geometry;
    r_func = _r_func;
    dr_func = _dr_func;
    ddr_func = _ddr_func;
    t = 0;
    r = r_func(0);
    dr = dr_func(0);
    attached_vectors = vector<VectorOnTrajectory4>();
    update_local_geometry();
}

Vector4f ParametricTrajectory::get_ddr() {
    return ddr_func(t);
}

void ParametricTrajectory::update_coor(float dt){
    t = t + dt;
    r = r_func(t);
    dr = dr_func(t);
}