# pragma once
# include <vecmath.h>
# include "geodesic.hpp"

class Geometry4;
class VectorOnTrajectory4;
class Ray4: public Geodesic4{
    public:
    float importance;

    Ray4(){}
    Ray4(Vector4f _r, Vector4f _dr, Geometry4* _geometry, float _importance = 1.);
    Ray4(Vector4f _r, Vector3f spacial_dir, Geometry4* _geometry, float _importance = 1.);

    Vector4f dr_equivalent(float dt);
    float inv_frequency();
    Vector3f get_spacial_direction();
};