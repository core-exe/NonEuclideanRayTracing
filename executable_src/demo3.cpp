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

# define PI 3.1415926

using namespace std;

// this demo tests relativistic observer.

int main(){
    function<Vector3f(Vector3f, Image*)> blackhole_grid = [](Vector3f pos, Image* img)->Vector3f{
        pos.normalize();
        float phi = atan2(pos.y(), pos.x());
        float theta = asin(pos.z());
        int phi_div = 9;
        int theta_div = 10;
        float ratio = 0.1;
        Vector3f grid_color = Vector3f(0.3, 0, 0);
        theta = theta * theta_div / PI;
        phi = phi * phi_div / (2 * PI);
        bool is_grid = false;
        is_grid = is_grid || ((theta - floor(theta)) < (ratio / 2)) || ((ceil(theta) - theta) < (ratio / 2));
        is_grid = is_grid || ((phi - floor(phi)) < (ratio / 2)) || ((ceil(phi) - phi) < (ratio / 2));
        return is_grid ? grid_color : Vector3f();
    };
    
    
    Image* cosmos = Image::LoadTGA("assets/cosmos.tga");

    function<Vector3f(Vector3f, Image*)> spherical_interpole = [](Vector3f pos, Image* img)->Vector3f{
        int h = img->Height(), w = img->Width();
        pos.normalize();
        float phi = atan2(pos.y(), pos.x()) + PI;
        float theta = asin(pos.z()) + PI / 2;
        float pix_w = phi / (2 * PI) * w;
        float pix_h = theta / (2 * PI) * h;
        int pix_w0 = (int) pix_w;
        int pix_w1 = (pix_w0 + 1 == w ? 0 : pix_w0 + 1);
        float pix_dw = pix_w - pix_w0;
        int pix_h0 = (int) pix_h;
        int pix_h1 = (pix_h0 + 1 == h ? 0 : pix_h0 + 1);
        float pix_dh = pix_h - pix_h0;
        return (img->GetPixel(pix_w0, pix_h0) * (1 - pix_dw) + img->GetPixel(pix_w1, pix_h0) * pix_dw) * (1 - pix_dh) + (img->GetPixel(pix_w0, pix_h1) * (1 - pix_dw) + img->GetPixel(pix_w1, pix_h1) * pix_dw) * pix_dh;
    };
    

    float sc_radius = 1.0;
    Geometry4* geometry = new SchwartzchildGeometry(
        sc_radius,
        0.005,
        0.0001,
        0.001,
        0.075,
        1000,
        new TerminalTexture(
            blackhole_grid, new Image(1, 1)
        ),
        new TerminalTexture(
            blackhole_grid, new Image(1, 1)
        ),
        new TerminalTexture(
            spherical_interpole, cosmos
        )
    );
    Group* group = new Group(geometry);

    float view_pos_theta = 0;
    float view_pos_phi = 0;
    float view_rad = 5;
    float view_dir_angle = -0.5;

    function<Matrix3f(float)> get_perspective = [](float r)->Matrix3f{
        float view_dir_angle;
        if(r<1.5)
            view_dir_angle = -1 + r/1.5;
        else
            view_dir_angle = 1 - 1.5 / r;
        return Matrix3f(
        Vector3f(cos(view_dir_angle), -sin(view_dir_angle),0),
        Vector3f(sin(view_dir_angle), cos(view_dir_angle),0),
        Vector3f(0,0,1));
    };
    
    vector<Vector4f> space_direction = vector<Vector4f>(3);
    Matrix3f perspective = Matrix3f(
        Vector3f(cos(view_dir_angle), -sin(view_dir_angle),0),
        Vector3f(sin(view_dir_angle), cos(view_dir_angle),0),
        Vector3f(0,0,1));
    Observer4* observer = new HorizontalDifferential(
        Vector4f(0, 5, 0, 0),
        Vector4f(1, 0, 0.25 * cos(-0.4), 0.25 * sin(-0.4)),
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

    Camera4* camera = new Camera4(300, 400, 2, observer, perspective);
    Scene4 scene(geometry, group, camera);
    FILE* log = fopen("output/demo3/log.txt", "w+");
    fclose(log);
    float simulate_dt_coef = 0.005;
    int counter = 0;
    while(!scene.scene_end()) {
        log = fopen("output/demo3/log.txt", "a");

        Observer4* o = scene.camera->observer;

        float r = o->r.yzw().length();
        float v = o->dr.yzw().length();
        float simulate_dt = simulate_dt_coef * r / v;
        double proper_time;

        camera->perspective = get_perspective(r);
        proper_time = scene.move_camera(simulate_dt);
        char str[100];
        sprintf(str, "output/demo3/%04d.png", counter);
        
        fprintf(log, "step %04d\n", counter);
        fprintf(log, "simulate_dt: %.4f\n", simulate_dt);
        fprintf(log, "r: (%.3f, %.3f, %.3f, %.3f)\n", o->r[0], o->r[1], o->r[2], o->r[3]);
        fprintf(log, "dr: (%.3f, %.3f, %.3f, %.3f)\n", o->dr[0], o->dr[1], o->dr[2], o->dr[3]);
        fprintf(log, "proper time: %e\n\n", proper_time);
        
        fprintf(log, "direction_0: (%.3f, %.3f, %.3f, %.3f)\n", o->prograde.v[0], o->prograde.v[1], o->prograde.v[2], o->prograde.v[3]);
        fprintf(log, "direction_1: (%.3f, %.3f, %.3f, %.3f)\n", o->normals[0].v[0], o->normals[0].v[1], o->normals[0].v[2], o->normals[0].v[3]);
        fprintf(log, "direction_2: (%.3f, %.3f, %.3f, %.3f)\n", o->normals[1].v[0], o->normals[1].v[1], o->normals[1].v[2], o->normals[1].v[3]);
        fprintf(log, "direction_3: (%.3f, %.3f, %.3f, %.3f)\n\n\n", o->normals[2].v[0], o->normals[2].v[1], o->normals[2].v[2], o->normals[2].v[3]);
        fclose(log);

        printf("rendering img %04d\n", counter);

        Image img = scene.shot();
        img.SaveBMP(str);
        
        counter++;
        if(counter == 10000)
            break;
    }
    return 0;
}