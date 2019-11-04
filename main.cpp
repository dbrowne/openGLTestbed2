#include <iostream>
#include "primatives.h"
int main() {
    Circle xxx;
    float *vecs;
    float points;
    int cntr;
    points =365;
    xxx.set_point_Count(points);
    xxx.gen_vertices();

    vecs = xxx.get_vertices();

    cntr =0;

    while (cntr <3*points){
        std::cout << vecs[cntr++] <<","<< vecs[cntr++]<<","<<vecs[cntr++]<<"\n";
    }



    return 0;
}