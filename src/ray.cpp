# include <vecmath.h>
# include "ray.hpp"
# include "utils.hpp"
# include "geometry.hpp"
# include "trajectory.hpp"


Ray4::Ray4(Vector4f _r, Vector4f _dr, Geometry4* _geometry){
    r = _r;
    dr = _dr;
    geometry = _geometry;
    attached_vectors = vector<VectorOnTrajectory4>();
    update_local_geometry();
    is_ddr_update = false;
}

Vector4f Ray4::dr_equivalent(float dt){
    get_ddr();
    return dr + 0.5*dt*ddr;
}

float Ray4::inv_frequency(){
    return -dot(Vector4f(1, Vector3f()), dr, g);
}

Vector3f Ray4::get_spacial_direction(){
    // the direction ray actually proceeds
    // the in ray will actually point away from the surface
    return dr.yzw().normalized();
}