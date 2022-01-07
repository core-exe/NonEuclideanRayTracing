# include <vecmath.h>
# include "camera.hpp"
# include "observer.hpp"
# include "geometry.hpp"
# include "plane.hpp"
# include "scene.hpp"
# include "group.hpp"
# include "texture.hpp"
# include "image.hpp"
# include "ball.hpp"
# include <vector>
# include <iostream>

using namespace std;

// this demo tests relativistic observer.

int main(){
    float sc_radius = 1;
    Geometry4* geometry = new FlatGeometry();
    Group* group = new Group(geometry);
    Plane* mirror = new Plane(Vector3f(0, 0, -5.0), Vector3f(1,0,0), Vector3f(0,1,0), new Surface(
        [](Vector3f pos)->float{return 1.0;},
        [](Vector3f pos)->float{return 1.0;},
        [](Vector3f pos)->float{return 0.6;},
        [](Vector3f pos)->float{return 0.4;},
        [](Vector3f pos)->Vector3f{return Vector3f(1.0);},
        [](Vector3f pos)->Vector3f{return Vector3f();},
        [](Vector3f pos)->Vector3f{
            float grid_length = 5.0;
            float ratio = 0.2;
            Vector3f in_pos = pos / grid_length;
            if(in_pos[0] - floor(in_pos[0]) < ratio / 2 || in_pos[1] - floor(in_pos[1]) < ratio / 2 || ceil(in_pos[0]) - in_pos[0] < ratio / 2 || ceil(in_pos[1]) - in_pos[1] < ratio / 2)
                return Vector3f(.25);
            else
                return Vector3f();
        }
    ));
    //1.0, 1.0, 0.6, 0.4, Vector3f(1), Vector3f(0.0), Vector3f(.125)
    mirror->name = "Mirror";
    group->add_object(mirror);

    Ball* ball = new Ball(2.0, Vector3f(), new Surface(
        1.0, 1.5, 0.2, 0.2, Vector3f(1.0, 0.8, 0.8), Vector3f(1.0, 0.4, 0.4), Vector3f(0.7)
    ));
    group->add_object(ball);
    

    float view_pos_theta = 0.4;
    float view_pos_phi = 0.2;
    float view_dir_angle = 0.1;
    float view_rad = 50;
    vector<Vector4f> space_direction = vector<Vector4f>(3);
    Matrix3f perspective = Matrix3f(
        Vector3f(-sin(view_dir_angle), -cos(view_dir_angle),0),
        Vector3f(cos(view_dir_angle), -sin(view_dir_angle),0),
        Vector3f(0,0,1));
    Observer4* observer = new HorizontalObserver4(
        Vector4f(0, 
        view_rad*cos(view_pos_theta)*cos(view_pos_phi), 
        view_rad*cos(view_pos_theta)*sin(view_pos_phi),
        view_rad*sin(view_pos_theta))
        , Vector4f(1,
        -0.0001*sin(view_pos_theta)*cos(view_pos_phi), 
        -0.0001*sin(view_pos_theta)*sin(view_pos_phi), 
        0.0001*cos(view_pos_theta)), geometry, space_direction);
    observer->correction();
    printf("space_direction_front: (%.3f, %.3f, %.3f, %.3f)\n", observer->normals[0].v[0], observer->normals[0].v[1], observer->normals[0].v[2], observer->normals[0].v[3]);
    printf("space_direction_up: (%.3f, %.3f, %.3f, %.3f)\n", observer->normals[1].v[0], observer->normals[1].v[1], observer->normals[1].v[2], observer->normals[1].v[3]);
    printf("space_direction_right: (%.3f, %.3f, %.3f, %.3f)\n", observer->normals[2].v[0], observer->normals[2].v[1], observer->normals[2].v[2], observer->normals[2].v[3]);

    Camera4* camera = new Camera4(720, 1080, 1.0, observer, perspective);
    Scene4 scene(geometry, group, camera);
    scene.sample = 3;

    //Vector3f color = scene.get_color(54,4);
    //printf("%.4f, %.4f, %.4f", color[0], color[1], color[2]);
    
    Image img = scene.shot();
    //img.SetPixel(54, 4, Vector3f(1.0, 0, 0));
    img.SaveBMP("output/demo1.png");
    
    return 0;
}