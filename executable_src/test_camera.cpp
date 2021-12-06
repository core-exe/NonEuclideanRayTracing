# include <vecmath.h>
# include "camera.hpp"
# include "observer.hpp"
# include "geometry.hpp"
# include "plane.hpp"
# include "scene.hpp"
# include "group.hpp"
# include "texture.hpp"
# include "image.hpp"
# include "ray.hpp"
# include <vector>
# include <iostream>

using namespace std;

int main(){
    Geometry4* geometry = new SchwartzchildGeometry(1);
    Group* group = new Group(geometry);
    Plane* plane1 = new Plane(Vector3f(0,-3,0), Vector3f(0,0,1), Vector3f(1,0,0), new PureGrid(
        Vector3f(0.2), Vector3f(0.4), 2.0, 0.4
    ));
    /*
    Plane* plane2 = new Plane(Vector3f(0,0,-3), Vector3f(1,0,0), Vector3f(0,1,0), new PureTexture(Vector3f(0, 0, 0.5)));
    plane2->geometry = geometry;
    */
    group->add_object(plane1);
    //group->add_object(plane2);
    vector<Vector4f> space_direction = vector<Vector4f>(3);
    Matrix3f perspective = Matrix3f(Vector3f(0,-1,0),Vector3f(1,0,0),Vector3f(0,0,1));
    Observer4* observer = new HorizontalObserver4(Vector4f(0, 10*sqrt(3), 0, 10), Vector4f(1, 0, 0.0001, 0), geometry, space_direction);
    observer->correction();
    printf("space_direction_front: (%.3f, %.3f, %.3f, %.3f)\n", observer->normals[0].v[0], observer->normals[0].v[1], observer->normals[0].v[2], observer->normals[0].v[3]);
    printf("space_direction_up: (%.3f, %.3f, %.3f, %.3f)\n", observer->normals[1].v[0], observer->normals[1].v[1], observer->normals[1].v[2], observer->normals[1].v[3]);
    printf("space_direction_right: (%.3f, %.3f, %.3f, %.3f)\n", observer->normals[2].v[0], observer->normals[2].v[1], observer->normals[2].v[2], observer->normals[2].v[3]);

    Camera4* camera = new Camera4(600, 800, 1.6, observer, perspective);
    Scene4 scene(geometry, group, camera);
    scene.sample = 2;

    Image img = scene.shot();
    img.SaveBMP("output/out.png");
    return 0;
}