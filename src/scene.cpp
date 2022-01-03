# include <vecmath.h>
# include <vector>
# include <iostream>
# include <omp.h>
# include "scene.hpp"
# include "group.hpp"
# include "geometry.hpp"
# include "camera.hpp"
# include "ray.hpp"
# include "hit.hpp"
# include "texture.hpp"
# include "image.hpp"
# include "observer.hpp"
using namespace std;

Scene4::Scene4(Geometry4* _geometry, Group* _group, Camera4* _camera){
    geometry = _geometry;
    group = _group;
    camera = _camera;
}

float Scene4::get_dt_geometry(Trajectory4* trajectory) {
    float t_geometry = geometry->get_dt(trajectory);
    return t_geometry;
}

Vector3f Scene4::get_color(Ray4 ray, bool direct = false){
    //cout << "get_color" << endl;
    Hit4 hit;
    hit.importance = ray.importance;
    while(!geometry->is_terminal(ray, hit))
    {
        Vector4f r = ray.r;
        float dt_max = get_dt_geometry(&ray);
        //printf("position: %.4f, %.4f, %.4f, %.4f, dt: %.4f\n", r[0], r[1], r[2], r[3], dt_max);

        if(group->intersect(ray, dt_max*intersect_dt_ratio, hit)){
            //cout << "intersected" << endl;
            break;
        }
        ray.step(dt_max);
    }
    vector<Vector3f> colors = vector<Vector3f>();
    //cout << "num_rays: " << hit.ray_out.size() << endl;
    for(int i=0; i<hit.ray_out.size(); i++){
        //cout << "importance " << hit.ray_out[i].importance << endl;
        Vector4f r = hit.ray_out[i].r;
        Vector4f dr = hit.ray_out[i].dr;
        //printf("position: %.4f, %.4f, %.4f, %.4f\n", r[0], r[1], r[2], r[3]);
        //printf("direction: %.4f, %.4f, %.4f, %.4f\n", dr[0], dr[1], dr[2], dr[3]);
    }
    for(int i=0; i<hit.ray_out.size(); i++){
        if(hit.ray_out[i].importance > eps){
            colors.push_back(get_color(hit.ray_out[i]));
        }
        else
            colors.push_back(Vector3f());
    }
    Vector3f color = hit.hit_texture->color(hit.hit_pos_texture, hit.in_cosine, hit.out_importance, colors);
    return color;
}

Vector3f Scene4::get_color(float x, float y){
    Vector3f color_avg = Vector3f();
    for(int dx = 0; dx<sample; dx++){
        for(int dy = 0; dy<sample; dy++){
            float w = x-(1-.5/sample)+(float) dx/sample;
            float h = y-(1-.5/sample)+(float) dy/sample;
            Ray4 ray = camera->get_ray(w, h);
            Vector3f color = get_color(ray, true);
            color_avg = color_avg + color / (sample * sample);
        }
    }
    return color_avg;
}

double Scene4::move_camera(float delta_t){
    // return the proper time
    bool stop = false;
    double proper_time_total=0.;
    while (!geometry->is_terminal(camera->observer))
    {
        float dt = get_dt_geometry(camera->observer);
        if(dt < delta_t)
            delta_t -= dt;
        else
            dt = delta_t;
            stop = true;
        proper_time_total += camera->observer->get_proper_time(dt);
        camera->observer->step(dt);
        if(stop)
            break;
    }
    return proper_time_total;
}

Image Scene4::shot(){
    Image img = Image(camera->width, camera->height);
    for(int x=0; x<camera->width; x++){
        printf("rendering x = %4d / %4d\n", x, camera->width);
        # pragma omp parallel for shared(img, x) num_threads(32)
        for(int y=0; y<camera->height; y++){
            img.SetPixel(x, y, get_color(x, y));
        }
    }
    return img;
}