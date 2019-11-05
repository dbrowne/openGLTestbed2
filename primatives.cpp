//
// Created by Dwight J. Browne on 11/3/19.
//

#include "primatives.h"
#include <iostream>
#include "Color.h"

Polyg::Polyg() {
    radius = 1.0;
    point_count = 4;
}

Polyg::Polyg(float rad, float pc) {
    radius = rad;
    point_count = pc;
    color[0] = new Color(1.0, 0.0, 0.0, 1.0);
    color[1] = new Color(0.0, 1.0, 0.0, 1.0);
    color[2] = new Color(0.0, 0.0, 1.0, 1.0);

}

Polyg::Polyg(float rad, float pc, const Color c1) {
    radius = rad;
    point_count = pc;
    color[0] = new Color(c1.r, c1.g, c1.b, c1.a);
    color[1] = new Color(c1.r, c1.g, c1.b, c1.a);
    color[2] = new Color(c1.r, c1.g, c1.b, c1.a);

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
    float theta = 0;
    float x, y, z;
    float incr;
    int offset = 0;
    int idx = 0;
    z = 0.0;

    offset = VERTEX_SIZE + COLOR_SIZE;
    sz = offset * point_count * 3;
    vertices = (float *) malloc(sz * sizeof(float));
    if (!vertices) {
        std::cout << "Polyg: Malloc failed\n";
        exit(0);
    }

    incr = 2 * PI / point_count;
    cntr = 0;

    while (cntr < 2 * point_count) {
        if (cntr % 2 == 0) {
            if (theta > 0) {
                theta -= incr;
            }
            vertices[idx] = 0;
            vertices[idx + 1] = 0;
            vertices[idx + 2] = z;
            set_vertex_color(idx, 0);
            idx += offset;
            x = radius * cos(theta);
            y = radius * sin(theta);
            vertices[idx] = x;
            vertices[idx + 1] = y;
            vertices[idx + 2] = z;
            set_vertex_color(idx, 1);
        } else {
            x = radius * cos(theta);
            y = radius * sin(theta);
            vertices[idx] = x;
            vertices[idx + 1] = y;
            vertices[idx + 2] = z;
            set_vertex_color(idx, 2);
        }
        idx += offset;
        cntr++;

        theta += incr;
    }
}

float *::Polyg::get_vertices() {
    return vertices;
}

void Polyg::set_vertex_color(int idx, int vtx) {
    vertices[idx + 3] = color[vtx]->r;
    vertices[idx + 4] = color[vtx]->g;
    vertices[idx + 5] = color[vtx]->b;
    vertices[idx + 6] = color[vtx]->a;

}

void Polyg::set_alpha(float a) {
    for (int i = 0; i < 3; i++) {
        color[i]->a = a;
    }
}

void Polyg::set_alpha(int v, float a) {
    color[v]->a = a;
}

void Polyg::set_color(Color c) {
    for (int i = 0; i < 3; i++) {
        color[i]->r = c.r;
        color[i]->g = c.g;
        color[i]->b = c.b;
        color[i]->a = c.a;
    }
}

void Polyg::set_color(int v, Color c) {
    color[v]->r = c.r;
    color[v]->g = c.g;
    color[v]->b = c.b;
    color[v]->a = c.a;
}

void Polyg::set_color(Color c0, Color c1, Color c2) {
    color[0]->r = c0.r;
    color[0]->g = c0.g;
    color[0]->b = c0.b;
    color[0]->a = c0.a;

    color[1]->r = c1.r;
    color[1]->g = c1.g;
    color[1]->b = c1.b;
    color[1]->a = c1.a;

    color[2]->r = c2.r;
    color[2]->g = c2.g;
    color[2]->b = c2.b;
    color[2]->a = c2.a;

}