# include <vecmath.h>
# include <vector>
# include "hit.hpp"
# include "texture.hpp"
# include "ray.hpp"
using namespace std;

Hit4::Hit4(){
    t=0;
    out_importance = vector<float>();
    out_cosine = vector<float>();
}