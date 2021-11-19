# include <vecmath.h>
# include <vector>

class Object3{
    public:
    Object3(){}
    ~Object3(){}
    virtual float distance(Vector3f r){
        return 1.0;
    }
};