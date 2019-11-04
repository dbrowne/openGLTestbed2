//
// Created by Dwight J. Browne on 11/3/19.
//

#include "primatives.h"
#include <iostream>


Circle::Circle() {
    radius = 1.0;
    point_count = 365;
}

Circle::Circle(float rad, float pc) {
    radius = rad;
    point_count = pc;
}

Circle::~Circle() = default;

void Circle::set_point_Count(float pc) {
    point_count = pc;
}

void Circle::set_radius(float rad) {
    radius = rad;
}


void::Circle::gen_vertices() {
    int sz;
    int cntr;
    float theta =0;
    float x, y, z;
    float incr;
    z = 0.0;

    sz = VERTEX_SIZE*point_count;
    vertices = (float *)malloc(sz*sizeof(float));
    if (!vertices){
        std::cout <<"Circle: Malloc failed\n";
        exit(0);
    }

    incr = 2*PI/point_count;
    cntr = 0;
    while (theta <= 2*PI){
        x=radius*cos(theta);
        vertices[cntr] = x;
        y=radius*sin(theta);
        vertices[cntr+1] = y;

        vertices[cntr+2] = z;
        cntr +=VERTEX_SIZE;
        theta += incr;

    }

}

float*::Circle::get_vertices() {
    return vertices;
}

