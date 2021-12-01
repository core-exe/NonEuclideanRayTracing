# pragma once
# include <vecmath.h>
# include "trojectory.hpp"
# include "geodesic.hpp"
# include "geometry.hpp"
# include "utils.hpp"

class Ray4: public Geodesic4{
    public:
    Ray4(){}
    Ray4(Vector4f _r, Vector4f _dr, Geometry4* _geometry);
    Vector4f dr_equivalent(float dt){
        get_ddr();
        return dr + 0.5*dt*ddr;
    }
    float inv_frequency(){
        return -dot(Vector4f(1, Vector3f()), dr, g);
    }
    Vector3f get_spacial_direction(){
        // the direction ray actually proceeds
        // the in ray will actually point away from the surface
        return dr.yzw().normalized();
    }
};

Ray4::Ray4(Vector4f _r, Vector4f _dr, Geometry4* _geometry){
    r = _r;
    dr = _dr;
    geometry = _geometry;
    attached_vectors = vector<VectorOnTrojectory4>();
    update_local_geometry();
    is_ddr_update = false;
}