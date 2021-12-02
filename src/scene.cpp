# include <vecmath.h>
# include "scene.hpp"
# include "group.hpp"
# include "geometry.hpp"
# include "camera.hpp"
# include "ray.hpp"
# include "hit.hpp"

Scene4::Scene4(Geometry4* _geometry, Group* _group, Camera4* _camera){
    geometry = _geometry;
    group = _group;
    camera = _camera;
}

float Scene4::get_dt_geometry(Vector4f r, Vector4f dr) {
    float t_geometry = geometry->get_dt(r, dr);
    return t_geometry;
}

Vector3f Scene4::get_color(Ray4 ray){
    Hit4 hit;
    while(geometry->is_terminal(ray, hit))
    {
        /* code */
    }
    return Vector3f();
}