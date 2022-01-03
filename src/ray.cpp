# include <vecmath.h>
# include "ray.hpp"
# include "utils.hpp"
# include "geometry.hpp"
# include "trajectory.hpp"


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

Vector4f Ray4::dr_equivalent(float dt){
    get_ddr();
    return dr + 0.5*dt*ddr;
}

float Ray4::inv_frequency(){
    return -dot(Vector4f(1, Vector3f()), dr, g);
}