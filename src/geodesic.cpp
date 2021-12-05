# include <vecmath.h>
# include "geodesic.hpp"
# include "geometry.hpp"
# include "trajectory.hpp"

Geodesic4::Geodesic4(Vector4f _r, Vector4f _dr, Geometry4* _geometry) : Trajectory4(_r, _dr, _geometry){
    r = _r;
    dr = _dr;
    geometry = _geometry;
    attached_vectors = vector<VectorOnTrajectory4>();
    update_local_geometry();
    is_ddr_update = false;
    tracking_step = 0;
}

Vector4f Geodesic4::get_ddr(){
    if(is_ddr_update)
        return ddr;
    ddr = Vector4f();
    for(int i=0; i<4; i++)
        for(int j=0; j<4; j++)
            for(int k=0; k<4; k++)
                ddr[i] += -gamma[i][j][k]*dr[j]*dr[k];
    return ddr;
}

void Geodesic4::update_coor(float dt){
    if(!is_ddr_update)
        get_ddr();
    r = r + dr * dt + 0.5 * ddr * dt * dt;
    dr = dr + ddr * dt;
}

void Geodesic4::step(float dt){
    update_vectors(dt);
    update_coor(dt);
    update_local_geometry();
    tracking_step++;
}