# pragma once
# include <vecmath.h>

class Metric4;
class Christoffel4 {
    private:
    Metric4* g;
    public:
    Christoffel4(Metric4* _g);
    void val(Vector4f r, float gamma[4][4][4]);
};