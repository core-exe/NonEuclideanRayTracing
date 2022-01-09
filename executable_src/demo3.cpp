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
    float sc_radius = 1.0;
    Geometry4* geometry = new SchwartzchildGeometry(1.0);
    Group* group = new Group(geometry);

    float view_pos_theta = 0;
    float view_pos_phi = 0;
    float view_rad = 5;
    float view_dir_angle = - 3.1415 / 6;
    vector<Vector4f> space_direction = vector<Vector4f>(3);
    Matrix3f perspective = Matrix3f(
        Vector3f(-sin(view_dir_angle), -cos(view_dir_angle),0),
        Vector3f(cos(view_dir_angle), -sin(view_dir_angle),0),
        Vector3f(0,0,1));
    Observer4* observer = new HorizontalDifferential(
        Vector4f(0, 5, 0, 0),
        Vector4f(1, 0, 0.01, 0),
        geometry,
        [](Vector4f r, Vector4f dr, Matrix4f g, float gamma[4][4][4])->Vector4f{
            Vector4f ddr = Vector4f();
            for(int i=0; i<4; i++)
                for(int j=0; j<4; j++)
                    for(int k=0; k<4; k++)
                        ddr[i] += -gamma[i][j][k]*dr[j]*dr[k];
            return ddr;
        }
    );
    observer->correction();

    /*
    
    */

    Camera4* camera = new Camera4(64, 64, 2, observer, perspective);
    Scene4 scene(geometry, group, camera);
    float simulate_dt = 0.5;
    int counter = 0;
    while(!scene.scene_end()) {
        Observer4* o = scene.camera->observer;
        printf("step %04d\n", counter);
        printf("r: (%.3f, %.3f, %.3f, %.3f)\n", o->r[0], o->r[1], o->r[2], o->r[3]);
        printf("dr: (%.3f, %.3f, %.3f, %.3f)\n", o->dr[0], o->dr[1], o->dr[2], o->dr[3]);
        cout << endl;
        
        printf("direction_0: (%.3f, %.3f, %.3f, %.3f)\n", o->prograde.v[0], o->prograde.v[1], o->prograde.v[2], o->prograde.v[3]);
        printf("direction_1: (%.3f, %.3f, %.3f, %.3f)\n", o->normals[0].v[0], o->normals[0].v[1], o->normals[0].v[2], o->normals[0].v[3]);
        printf("direction_2: (%.3f, %.3f, %.3f, %.3f)\n", o->normals[1].v[0], o->normals[1].v[1], o->normals[1].v[2], o->normals[1].v[3]);
        printf("direction_3: (%.3f, %.3f, %.3f, %.3f)\n", o->normals[2].v[0], o->normals[2].v[1], o->normals[2].v[2], o->normals[2].v[3]);
        cout << endl;
        cout << endl;

        scene.move_camera(simulate_dt);
        char str[100];
        sprintf(str, "output/demo3/%04d.png", counter);
        
        Image img = scene.shot();
        img.SaveBMP(str);
        
        counter++;
        if(counter == 10000)
            break;
    }
    
    return 0;
}