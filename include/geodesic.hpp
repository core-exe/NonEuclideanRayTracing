# pragma once
# include <vecmath.h>
# include "trojectory.hpp"
# include "geometry.hpp"

class Geodesic4: public Trojectory4 {
    public:
    bool is_ddr_update;
    Vector4f ddr;
    int tracking_step;

    Geodesic4(){}
    Geodesic4(Vector4f _r, Vector4f _dr, Geometry4* _geometry);

    Vector4f get_ddr(){
        if(is_ddr_update)
            return ddr;
        ddr = Vector4f();
        for(int i=0; i<4; i++)
            for(int j=0; j<4; j++)
                for(int k=0; k<4; k++)
                    ddr[i] += -gamma[i][j][k]*dr[j]*dr[k];
        return ddr;
    }

    void update_coor(float dt){
        if(!is_ddr_update)
            get_ddr();
        r = r + dr * dt + 0.5 * ddr * dt * dt;
        dr = dr + ddr * dt;
    }

    virtual void step(float dt){
        update_vectors(dt);
        update_coor(dt);
        update_local_geometry();
        tracking_step++;
    }
};

Geodesic4::Geodesic4(Vector4f _r, Vector4f _dr, Geometry4* _geometry){
    r = _r;
    dr = _dr;
    geometry = _geometry;
    attached_vectors = vector<VectorOnTrojectory4>();
    update_local_geometry();
    is_ddr_update = false;
}

Vector4f Geodesic4::get_ddr(){
    if(is_ddr_update)
        return ddr;
    ddr = Vector4f();
    for(int i=0; i<4; i++)
        for(int j=0; j<4; j++)
            for(int k=0; k<4; k++)
                ddr[i] += -gamma[i][j][k]*dr[j]*dr[k];
    return ddr;
}