# include <vecmath.h>
# include "observer.hpp"
# include "trajectory.hpp"
# include "utils.hpp"
# include <vector>
using namespace std;

Prograde::Prograde(Observer4* _observer){
    trajectory = _observer;
    observer = _observer;
    align();
}

void Prograde::align(){
    Vector4f et = observer->dr;
    v = et / sqrt(-dot(et, et, observer->g));
}

Vector4f Prograde::get_dv(){
    Vector4f dr = observer->dr;
    Vector4f ddr = observer->get_ddr();
    float length_square = -dot(dr, dr, observer->g);
    float s = 0;
    for(int i=0; i<4; i++)
        for(int j=0; j<4; j++)
            for(int k=0; k<4; k++)
                s+=dr[i]*dr[j]*dr[k]*observer->dg[i][j][k];
    s+=2*dot(dr, ddr, observer->g);
    return (ddr*sqrt(length_square)+dr*s/(2*sqrt(length_square)))/length_square;
}


Normal::Normal(Observer4* _observer, Vector4f _v){
    trajectory = _observer;
    observer = _observer;
    v = _v;
    v = v + observer->prograde.v * dot(v, observer->prograde.v, trajectory->g);
}



Observer4::Observer4(Vector4f _r, Vector4f _dr, Geometry4* _geometry, vector<Vector4f> space_direction) : Trajectory4(_r, _dr, _geometry){
    normals = vector<Normal>();
    update_local_geometry();
    prograde = Prograde(this);
    for(int i=0; i<2; i++){
        normals[i] = Normal(this, space_direction[i]);
    }
}



void Observer4::correction(){
    prograde.align();
    Vector4f e0=prograde.v, e1=normals[0].v, e2=normals[1].v, e3=normals[2].v;
    e1 = e1 + e0*dot(e0, e1, g);
    e1 = e1 / sqrt(dot(e1, e1, g));
    e2 = e2 + e0*dot(e0, e2, g) - e1*dot(e1, e2, g);
    e2 = e2 / sqrt(dot(e2, e2, g));
    e3 = e3 + e0*dot(e0, e3, g) - e1*dot(e1, e3, g) - e2*dot(e2, e3, g);
    e3 = e3 / sqrt(dot(e3, e3, g));
    prograde.v = e0;
    normals[0].v = e1;
    normals[1].v = e2;
    normals[2].v = e3;
}

void Observer4::update_frame(float dt){
    // update the frame
}

void Observer4::step(float dt){
    // update the frame
    update_frame(dt);
    correction();
    // normal update sequence
    update_vectors(dt);
    update_coor(dt);
    update_local_geometry();
}

GyroscopeObserver4::GyroscopeObserver4(Vector4f _r, Vector4f _dr, Geometry4* _geometry, vector<Vector4f> space_direction):Observer4(_r, _dr, _geometry, space_direction){
    normals = vector<Normal>();
    update_local_geometry();
    prograde = Prograde(this);
    for(int i=0; i<2; i++){
        normals[i] = Normal(this, space_direction[i]);
    }
}

void GyroscopeObserver4::update_frame(float dt){
    // update the frame according to a gyroscope
    Vector4f De0 = prograde.covariant_derivative_freeze()+prograde.get_dv();
    for(int i=0; i<3; i++){
        Vector4f Dei = De0 * dot(De0, normals[i].v, g);
        Vector4f dei = Dei - normals[i].covariant_derivative_freeze();
        normals[i].v = normals[i].v + dt * dei;
    }
}

HorizontalObserver4::HorizontalObserver4(Vector4f _r, Vector4f _dr, Geometry4* _geometry, vector<Vector4f> space_direction):Observer4(_r, _dr, _geometry, space_direction){
    normals = vector<Normal>();
    update_local_geometry();
    prograde = Prograde(this);
    for(int i=0; i<2; i++){
        normals[i] = Normal(this, space_direction[i]);
    }
}

void HorizontalObserver4::correction(){
    prograde.align();
    Vector3f up = r.yzw().normalized();
    Vector3f front = dr.yzw();
    front = (front - Vector3f::dot(up, front) * up).normalized();
    Vector3f right = Vector3f::cross(front, up).normalized();
    Vector4f e0 = prograde.v, e1 = Vector4f(0, front), e2 = Vector4f(0, up), e3 = Vector4f(0, right);
    e2 = e2 + e0*dot(e0, e2, g);
    e2 = e2 / sqrt(dot(e2, e2, g));
    e1 = e1 + e0*dot(e0, e1, g) - e1*dot(e1, e1, g);
    e1 = e1 / sqrt(dot(e1, e1, g));
    e3 = e3 + e0*dot(e0, e3, g) - e1*dot(e1, e3, g) - e2*dot(e2, e3, g);
    e3 = e3 / sqrt(dot(e3, e3, g));
    prograde.v = e0;
    normals[0].v = e1;
    normals[1].v = e2;
    normals[2].v = e3;
}