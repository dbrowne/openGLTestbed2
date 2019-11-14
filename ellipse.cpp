//
// Created by Dwight J. Browne on 11/12/19.
//

#include "ellipse.h"
#include <iostream>
#include <cmath>

Ellipse::Ellipse() {
    coords[0] = 0.0;
    coords[1] = 0.0;
    coords[2] = 0.0;
    a = 1;
    b = -0.25;
    point_count = 18;
    initial_point_count = point_count;
    vertex_size = 0;
    vertex_count = 0;

    color[0] = new Color(1.0, 0.0, 0.0, 1.0);
    color[1] = new Color(0.0, 1.0, 0.0, 1.0);
    color[2] = new Color(0.0, 0.0, 1.0, 1.0);
}

Ellipse::~Ellipse() = default;

void Ellipse::gen_vertices() {
    int offset;
    int sz;
    int idx = 0;
    float x, y, z;
    int cntr = 0;
    float theta = 0;
    float incr;

    offset = VERTEX_SIZE + COLOR_SIZE + TEXTURE_SIZE;
    vertex_count = 3 * point_count;
    sz = offset * vertex_count;

    vertex_size = sz;
    if (!alloced) {
        vertices = (float *) malloc(sz * sizeof(float));
        alloced = true;
    } else {
        if (point_count > initial_point_count) {
            vertices = (float *) realloc(vertices, sz * sizeof(float));
        }
    }
    if (!vertices) {
        std::cout << "Cylinder: Malloc failed. cannot allocate vertices\n";
        exit(-1);
    }

    index_size = 12 * vertex_count;
    indices = (unsigned int *) malloc(index_size * sizeof(unsigned int));
    if (!indices) {
        std::cout << "Polyg: Malloc failed. Cannot allocate indices\n";
        exit(-1);
    }

    incr = mult * 3.1415967 / point_count;
    while (cntr < 2 * point_count) {
        if (cntr % 2 == 0) {
            if (theta > 0) {
                theta -= incr;
            }
            x = a * cos(theta) + coords[0];
            y = b * sin(theta) + coords[1];
            z = coords[2];

            set_vertex(idx, coords[0], coords[1], z);
            set_vertex_color(idx, 0);
            set_tex_pos(idx, 0.0, 0.0);
            idx += offset;
            set_vertex(idx, x, y, z);
            set_vertex_color(idx, 1);
            set_tex_pos(idx, 1, 1);
        } else {
            x = a * cos(theta) + coords[0];
            y = b * sin(theta) + coords[1];
            z = coords[2];
            set_vertex(idx, x, y, z);
            set_vertex_color(idx, 2);
            set_tex_pos(idx, 1, 0);
        }
        idx += offset;
        cntr++;

        theta += incr;
    }

}

void Ellipse::increment(int int_val) {}

float *Ellipse::get_vertices() {
    return vertices;
}

void Ellipse::set_vertex(int idx, float x1, float y1, float z1) {
    vertices[idx] = x1;
    vertices[idx + 1] = y1;
    vertices[idx + 2] = z1;
}

void Ellipse::set_vertex_color(int idx, int vtx) {
    vertices[idx + 3] = color[vtx]->r;
    vertices[idx + 4] = color[vtx]->g;
    vertices[idx + 5] = color[vtx]->b;
    vertices[idx + 6] = color[vtx]->a;
}

void Ellipse::set_tex_pos(int idx, float x, float y) {
    vertices[idx + 7] = x;
    vertices[idx + 8] = y;
}


int Ellipse::get_index_size() {
    return index_size;
}

int Ellipse::get_vertex_count() {
    return vertex_count;
}

int Ellipse::get_vertex_size() {
    return vertex_size;
}

unsigned int *::Ellipse::get_indices() {
    return indices;
}

bool Ellipse::has_bottom() {
    return true;
}

void Ellipse::set_mult(float m) {
    mult = m;
}