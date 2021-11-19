#include <vecmath.h>
#include "object.hpp"
#include "geometry.hpp"

class Scene3 {
    public:
    Geometry3* geometry;
    Object3* group;
    Scene3(Geometry3* _geometry, Object3* _group) {
        geometry = _geometry;
        group = _group;
    }
    float get_dt_geometry(Vector3f r, Vector3f dr) {
        float t_geometry = geometry->get_dt(r, dr);
        return t_geometry;
    }
    float get_dt_object(Vector3f r, Vector3f dr) {
        float t_object = group->distance(r) / dr.length();
        return t_object;
    }
};