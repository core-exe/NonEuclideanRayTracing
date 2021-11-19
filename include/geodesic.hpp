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