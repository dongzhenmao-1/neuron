#include <stdio.h>
#include <vector> 
#include <math.h>

#include "neuron.hpp"

void view_DA_v() {
    printf("Time,DA_v\n");
    DA.float_v(1);
    for (int i = 0; i < 2000; ++i) { // 200 ms
        if (i % 10 == 0) {
            printf("%f,%.6f\n", i / 10.0, DA.v());
        }
        DA.t_run();
    }    
}

PN_Neuron a, b, c;

void view_enhance() {
    printf("Time,W\n");
    link_random(&a, &b);
    link_random(&c, &b);

    printf("%lf,%lf,%lf,%lf\n", 0, b.v, b.den.front().Ca_v, b.den.front().w);

    for (int i = 0; i < 6; ++i) {
        c.release();
        b.t_run();
        printf("%lf,%lf,%lf,%lf\n", 0, b.v, b.den.front().Ca_v, b.den.front().w);
    }

    DA.float_v(0.5);
    for (int i = 1; i < 10000; ++i) {
        DA.t_run();
        b.t_run();
        if(i % 10 == 0) printf("%lf,%lf,%lf,%lf\n", i / 10.0, b.v, b.den.front().Ca_v, b.den.front().w);
    }

}

int main() {
    view_enhance();
    
    return 0;
}

/*


*/