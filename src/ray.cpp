# include <vecmath.h>
# include "ray.hpp"
# include "geometry.hpp"
# include "trajectory.hpp"
# include "utils.hpp"

Ray4::Ray4(Vector4f _r, Vector4f _dr, Geometry4* _geometry, float _importance){
    r = _r;
    dr = -_dr/_dr[0];
    geometry = _geometry;
    attached_vectors = vector<VectorOnTrajectory4>();
    update_local_geometry();
    is_ddr_update = false;
    importance = _importance;
    tracking_step = 0;
}

Ray4::Ray4(Vector4f _r, Vector3f spacial_dir, Geometry4* _geometry, float _importance){
    r = _r;
    geometry = _geometry;
    update_local_geometry();
    dr = get_negative_null_vector(-spacial_dir, g);
    attached_vectors = vector<VectorOnTrajectory4>();
    is_ddr_update = false;
    importance = _importance;
    tracking_step = 0;
}

Vector4f Ray4::get_ddr(){
    if(is_ddr_update)
        return ddr;
    ddr = Vector4f();
    for(int i=0; i<4; i++)
        for(int j=0; j<4; j++)
            for(int k=0; k<4; k++)
                ddr[i] += -gamma[i][j][k]*dr[j]*dr[k];
    return ddr;
}

void Ray4::update_coor(float dt){
    if(!is_ddr_update)
        get_ddr();
    r = r + dr * dt + 0.5 * ddr * dt * dt;
    dr = dr + ddr * dt;
}

void Ray4::step(float dt){
    update_vectors(dt);
    update_coor(dt);
    update_local_geometry();
    tracking_step++;
}

Vector4f Ray4::dr_equivalent(float dt){
    get_ddr();
    return dr + 0.5*dt*ddr;
}

float Ray4::inv_frequency(){
    return -dot(Vector4f(1, Vector3f()), dr, g);
}