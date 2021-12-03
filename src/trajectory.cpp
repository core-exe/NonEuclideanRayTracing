# include <vecmath.h>
# include <vector>
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