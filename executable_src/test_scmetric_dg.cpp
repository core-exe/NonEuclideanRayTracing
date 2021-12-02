# include <vecmath.h>
# include "metric.hpp"
# include <iostream>
using namespace std;

int main(){
    SchwartzchildMetric m(1.0);
    float dg[4][4][4];
    float eps = 5e-4;
    Vector4f r=Vector4f(.2, 1.1, 0.7, 0.1);
    m.d(r, dg);
    for(int i=0; i<4; i++){
        cout << endl;
        for(int j=0; j<4; j++){
            cout << endl;
            for(int k=0; k<4; k++){
                Vector4f rs = r;
                rs[k] += eps;
                cout << (m.val(rs)(i,j)-m.val(r)(i,j))/eps - dg[i][j][k] << endl;
            }
        }
    }
    return 0;
}