//
// Created by Dwight J. Browne on 11/3/19.
//

#include "primatives.h"
#include <iostream>


Polyg::Polyg() {
    radius = 1.0;
    point_count = 4;
}

Polyg::Polyg(float rad, float pc) {
    radius = rad;
    point_count = pc;
}

Polyg::~Polyg() = default;

void Polyg::set_point_Count(float pc) {
    point_count = pc;
}

void Polyg::set_radius(float rad) {
    radius = rad;
}


void ::Polyg::gen_vertices() {
    int sz;
    int cntr;
    float theta =0;
    float x, y, z;
    float incr;
    int offset = 0;
    int idx =0;
    z = 0.0;

    offset = VERTEX_SIZE+COLOR_SIZE;
    sz = offset*point_count*3;
    vertices = (float *)malloc(sz*sizeof(float));
    if (!vertices){
        std::cout << "Polyg: Malloc failed\n";
        exit(0);
    }

    incr = 2*PI/point_count;
    cntr = 0;

    while (cntr <2*point_count){
        if (cntr%2 ==0){
            if (theta >0){
                theta -=incr;
            }
            vertices[idx] =0;
            vertices[idx+1] =0;
            vertices[idx+2] =z;
            vertices[idx+3] = 1.0;
            vertices[idx+4] = 1.0;
            vertices[idx+5] = 1.0;
            idx += offset;

        }
        x=radius*cos(theta);
        y=radius*sin(theta);
        vertices[idx] = x;
        vertices[idx+1] =y;
        vertices[idx+2] =z;
        vertices[idx+3] = 1.0;
        vertices[idx+4] = 1.0;
        vertices[idx+5] = 1.0;
        idx += offset;
        cntr++;

        theta += incr;
//        std::cout << " " << x << " , " << y <<" , "<<z<<"\n";
    }
    idx -= offset;
    theta =0;
    vertices[idx]=radius*cos(theta);
    vertices[idx+1]=radius*sin(theta);
    vertices[idx+2]=z;
    vertices[idx+3]=1.0;
    vertices[idx+4]=1.0;
    vertices[idx+5]=1.0;

}

float *::Polyg::get_vertices() {
    return vertices;
}

