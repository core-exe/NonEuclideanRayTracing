# pragma once
# include <vecmath.h>
# include "geodesic.hpp"

class Geometry4;
class VectorOnTrajectory4;
class Ray4: public Geodesic4{
    public:
    Ray4(){}
    Ray4(Vector4f _r, Vector4f _dr, Geometry4* _geometry);
    Vector4f dr_equivalent(float dt);
    float inv_frequency();
    Vector3f get_spacial_direction();
};