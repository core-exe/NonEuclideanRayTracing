# include "geometry.hpp"
# include "ray.hpp"
# include "utils.hpp"
# include "metric.hpp"
# include <cstdio>
# include <iostream>

// not available right now

int main(){
    SchwartzchildGeometry* geometry = new SchwartzchildGeometry(1.0);
    float x;
    cin >> x;
    float r_min = 1e-6, r_max = 100;
    Vector4f dr = Vector4f(1, 0, sqrt(1-1/x), 0);
    Vector4f init_pos = Vector4f(0,x,0,0);
    Ray4 geodesic(init_pos, dr, geometry);

    for(int i=0; i<8192; i++){
        float r = geodesic.r.yzw().length();
        Vector4f pos = geodesic.r;
        if(r<r_min || r>r_max)
            break;
        float dt = geometry->get_dt_ray(&geodesic);
        geodesic.step(dt);
        printf("n = %05d, t = %.5f, x = %+.5f, y = %+.5f, r = %.5f\n", i, pos[0], pos[1], pos[2], r);
    }
    return 0;
}