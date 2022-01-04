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
# include "ball.hpp"
# include <vector>
# include <iostream>

using namespace std;

// this demo tests some objects of NE ray tracing
// involved object: (group), plane, ball
// test reflection.

int main(){
    float sc_radius = 1;
    Geometry4* geometry = new SchwartzchildGeometry(1);
    Group* group = new Group(geometry);
    Plane* mirror = new Plane(Vector3f(0, 0, -6), Vector3f(1,0,0), Vector3f(0,1,0), new Surface(
        [](Vector3f pos)->float{return 1.0;},
        [](Vector3f pos)->float{return 1.0;},
        [](Vector3f pos)->float{return 0.4;},
        [](Vector3f pos)->float{return 0.6;},
        [](Vector3f pos)->Vector3f{return Vector3f(1.0);},
        [](Vector3f pos)->Vector3f{return Vector3f();},
        [](Vector3f pos)->Vector3f{
            float grid_length = 5.0;
            float ratio = 0.2;
            Vector3f in_pos = pos / grid_length;
            if(in_pos[0] - floor(in_pos[0]) < ratio / 2 || in_pos[1] - floor(in_pos[1]) < ratio / 2 || ceil(in_pos[0]) - in_pos[0] < ratio / 2 || ceil(in_pos[1]) - in_pos[1] < ratio / 2)
                return Vector3f(.2);
            else
                return Vector3f(.05);
        }
    ));
    //1.0, 1.0, 0.6, 0.4, Vector3f(1), Vector3f(0.0), Vector3f(.125)
    
    mirror->name = "Mirror";
    group->add_object(mirror);
    
    Ball* ball1 = new Ball(
        3, Vector3f(8, 0, 0), new Surface(1.0, 1.5, 0.05, 0.05, Vector3f(0.8), Vector3f(1.0, 0.6, 0.6), Vector3f(.7, 0, 0))
    );
    ball1->name = "Ball1";
    group->add_object(ball1);

    

    Ball* ball2 = new Ball(
        3, Vector3f(0, 8, 0), new PureSurface(1.0, 1.0, 0.9, 0.1, Vector3f(0.6, 1.0, 0.6), Vector3f(), Vector3f(0, 0.5, 0))
    );
    ball1->name = "Ball2";
    group->add_object(ball2);
    
    Ball* ball3 = new Ball(
        3, Vector3f(0, 0, 8), new PureSurface(1.0, 1.0, 0.5, 0.5, Vector3f(1.0), Vector3f(0), Vector3f(0, 0, 0.8))
    );
    ball1->name = "Ball3";
    group->add_object(ball3);

    

    

    float view_pos_theta = 0.4;
    float view_pos_phi = 3.141/5;
    float view_dir_angle = -0.05;
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

    Camera4* camera = new Camera4(720, 1080, 0.7, observer, perspective);
    Scene4 scene(geometry, group, camera);
    scene.sample = 3;
    scene.max_depth = 4;

    //Vector3f color = scene.get_color(21, 28, true);
    //printf("%.4f, %.4f, %.4f\n\n\n\n", color[0], color[1], color[2]);

    Image img = scene.shot(10);
    //img.SetPixel(21, 28, Vector3f(0, 1.0, 0));
    img.SaveBMP("output/demo2.png");
    
    return 0;
}