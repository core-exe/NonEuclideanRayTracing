#include <vecmath.h>
#include "geometry.hpp"

class Geodesic3 {
    public:
    Vector3f r;
    Vector3f dr;
    Geometry3* geometry;
    Geodesic3(Vector3f _r, Vector3f _dr, Geometry3* _geometry) {
        r = _r;
        dr = _r;
        geometry = _geometry;
    }
};

class Geodesic4 {
    public:
    Vector4f r;
    Vector4f dr;
    Geometry4* geometry;
    Geodesic4(Vector4f _r, Vector4f _dr, Geometry4* _geometry) {
        r = _r;
        dr = _r;
        geometry = _geometry;
    }
};

class Ray4: public Geodesic4{

};