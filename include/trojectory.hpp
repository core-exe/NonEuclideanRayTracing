# pragma once
# include <vecmath.h>
# include <vector>
# include "geometry.hpp"
using namespace std;

class Trojectory4;
class VectorOnTrojectory4{
    public:
    Trojectory4* trojectory;
    Vector4f v;

    VectorOnTrojectory4(){
        v = Vector4f();
    }

    VectorOnTrojectory4(Trojectory4* _trojectory, Vector4f _v){
        trojectory = _trojectory;
        v = _v;
    }

    ~VectorOnTrojectory4(){}

    virtual void step(float dt){
        // change v according to time interval dt
    }

    virtual Vector4f get_dv(){
        return Vector4f();
    }

    Vector4f covariant_derivative_freeze();
};

class Trojectory4{
    public:
    Vector4f r, dr;
    Geometry4* geometry;
    vector<VectorOnTrojectory4> attached_vectors;
    
    Matrix4f g;
    float dg[4][4][4], gamma[4][4][4];

    Trojectory4(){}

    Trojectory4(Vector4f _r, Vector4f _dr, Geometry4* _geometry){
        r = _r;
        dr = _dr;
        geometry = _geometry;
        attached_vectors = vector<VectorOnTrojectory4>();
        update_local_geometry();
    }

    ~Trojectory4(){}

    virtual Vector4f get_ddr(){
        // calculate ddr
        return Vector4f();
    }

    void attach_vector(VectorOnTrojectory4 v){
        attached_vectors.push_back(v);
    }

    void update_vectors(float dt){
        for(int i=0; i<attached_vectors.size(); i++){
            attached_vectors[i].step(dt);
        }
    }

    void update_local_geometry(){
        g = geometry->g->val(r);
        geometry->g->d(r, dg);
        geometry->gamma->val(r, dg);
    }

    virtual void update_coor(float dt){
        // change r, dr according to the time interval dt
    }

    virtual void step(float dt){
        update_vectors(dt);
        update_coor(dt);
        update_local_geometry();
    }
};

Vector4f VectorOnTrojectory4::covariant_derivative_freeze(){
    Vector4f dr = trojectory->dr;
    Vector4f Dv = Vector4f();
    float gamma[4][4][4];
    for(int i=0; i<4; i++)
        for(int j=0; j<4; j++)
            for(int k=0; k<4; k++)
                Dv[i] += v[j]*dr[k];
    return Dv;
}