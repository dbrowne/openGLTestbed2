//
// Created by Dwight J. Browne on 11/12/19.
//

#include "ellipse.h"
#include <iostream>
#include <cmath>
#include "Prim_base.h"

Ellipse::Ellipse() {
    coords[0] = 0.0;
    coords[1] = 0.0;
    coords[2] = 0.0;
    a = 1;
    b = 0.25;
    point_count = 9;
    initial_point_count = point_count;
    vertex_size = 0;
    vertex_count = 0;
    mult = 2.0;
    color[0] = new Color(1.0, 0.0, 0.0, 1.0);
    color[1] = new Color(0.0, 1.0, 0.0, 1.0);
    color[2] = new Color(0.0, 0.0, 1.0, 1.0);
}

Ellipse::Ellipse(float x, float y, float z, float a1, float b1, float m, int pc) {
    coords[0] = x;
    coords[1] = y;
    coords[2] = z;
    a = a1;
    b = b1;
    mult = m;
    point_count = pc;
    color[0] = new Color(1.0, 1.0, 0.0, 1.0);
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
    float v1[3], v2[3], v3[3];
    int v1_idx, v2_idx, v3_idx;

    offset = VERTEX_SIZE + COLOR_SIZE + TEXTURE_SIZE + NORMAL_SIZE;
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
            v1_idx = idx;
            v1[0] = coords[0];
            v1[1] = coords[1];
            v1[2] = coords[2];
            set_vertex_color(idx, 0);
            set_tex_pos(idx, 0.0, 0.0);
            idx += offset;
            set_vertex(idx, x, y, z);
            v2[0] = x;
            v2[1] = y;
            v2[2] = z;
            set_vertex_color(idx, 1);
            set_tex_pos(idx, 1, 1);
            v2_idx = idx;
        } else {
            x = a * cos(theta) + coords[0];
            y = b * sin(theta) + coords[1];
            z = coords[2];
            set_vertex(idx, x, y, z);
            v3[0] = x;
            v3[1] = y;
            v3[2] = z;
            set_vertex_color(idx, 2);
            set_tex_pos(idx, 1, 0);
            Extra::gen_normal3(v1_idx, 9, v1, v2, v3, vertices);
            Extra::gen_normal3(v2_idx, 9, v2, v3, v1, vertices);
            Extra::gen_normal3(idx, 9, v3, v1, v2, vertices);
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

float *Ellipse::get_coords() {
    return coords;
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


void Ellipse::print_vertices() {
    std::cout << " #:    vertex:\t\tcolor:\t\ttex:\t\tnorm \n";
    int offset = VERTEX_SIZE + COLOR_SIZE + TEXTURE_SIZE + NORMAL_SIZE;
    int cntr = 0;
    int vtx_cnt = 0;
    int pc = 0;
    pc = point_count;

    for (int i = 0; i < pc; i++) {
        std::cout << vtx_cnt++ << ":  ";
        dump_vertex(cntr);
        cntr += offset;
        std::cout << vtx_cnt++ << ":  ";
        dump_vertex(cntr);
        std::cout << vtx_cnt++ << ":  ";
        cntr += offset;
        dump_vertex(cntr);
        std::cout << "\n";

        cntr += offset;

    }
}

// could make this a little better but time is not on my side
void Ellipse::set_color(float r, float g, float b, float a, int idx) {
    color[idx]->r = r;
    color[idx]->g = g;
    color[idx]->b = b;
    color[idx]->a = a;
}

void Ellipse::dump_vertex(int offset) {
    for (int j = 0; j < 3; j++) {
        std::cout << vertices[offset + j] << ", ";
    }

    std::cout << ":\t\t ";
    for (int j = 3; j <= 6; j++) {
        std::cout << vertices[offset + j] << ", ";
    }
    std::cout << ":\t\t";
    for (int j = 7; j <= 8; j++) {
        std::cout << vertices[offset + j] << ", ";
    }
    std::cout << ":\t\t";
    for (int j = 9; j <= 11; j++) {
        std::cout << vertices[offset + j] << ", ";
    }
    std::cout << "\n";
}

void Ellipse::rotate(int axis, float angle) {
    Extra::rotate(axis, angle, vertices,
                  VERTEX_SIZE + COLOR_SIZE + TEXTURE_SIZE, vertex_stride, vertex_size);
}

void Ellipse::translate(glm::vec3 offset) {
    Extra::translate(offset, vertices, VERTEX_SIZE + COLOR_SIZE + TEXTURE_SIZE,
                     vertex_stride, vertex_size);
}