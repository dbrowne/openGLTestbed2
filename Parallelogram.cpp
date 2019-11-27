//
// Created by Dwight J. Browne on 11/13/19.
//

#include "Parallelogram.h"
#include <cmath>
#include <iostream>
#include "Prim_base.h"

Paralleogram::Paralleogram() {
    theta = 90;
    a = 2;
    b = 2;
    coords[0] = 0;
    coords[1] = 0;
    coords[2] = 1;
    point_count = 6;
    color[0] = new Color(1.0, 0.0, 0.0, 1.0);
    color[1] = new Color(0.0, 1.0, 0.0, 1.0);
    color[2] = new Color(0.0, 0.0, 1.0, 1.0);

}

Paralleogram::~Paralleogram() = default;

Paralleogram::Paralleogram(float *vx1, float *vx2, float *vx3, float *vx4, float w) {
    have_vertices = true;
    set_point(0, vx1);
    set_point(1, vx2);
    set_point(2, vx3);
    set_point(3, vx3);
    set_point(4, vx4);
    set_point(5, vx1);
    color[0] = new Color(1.0, 0.0, 0.0, 1.0);
    color[1] = new Color(0.0, 1.0, 0.0, 1.0);
    color[2] = new Color(1.0, .5, 1.0, 1.0);
    wind = w;
}


Paralleogram::Paralleogram(float *vx1, float *vx2, float *vx3, float *vx4, float w, Color **colors) {
    have_vertices = true;
    set_point(0, vx1);
    set_point(1, vx2);
    set_point(2, vx3);
    set_point(3, vx3);
    set_point(4, vx4);
    set_point(5, vx1);

    for (int i = 0; i < 3; i++) {
        color[i] = new Color(colors[i]->r, colors[i]->g, colors[i]->b, colors[i]->a);
    }
    wind = w;
}


Paralleogram::Paralleogram(float angle, float side1, float side2, float x, float y, float z) {
    theta = angle;
    a = side1;
    b = side2;
    coords[0] = x;
    coords[1] = y;
    coords[2] = z;
    point_count = 6;
    color[0] = new Color(1.0, 0.0, 0.0, 1.0);
    color[1] = new Color(0.0, 1.0, 0.0, 1.0);
    color[2] = new Color(0.0, 0.0, 1.0, 1.0);
}


Paralleogram::Paralleogram(float angle, float side1, float side2, float x, float y, float z, bool w) {
    theta = angle;
    a = side1;
    b = side2;
    coords[0] = x;
    coords[1] = y;
    coords[2] = z;
    point_count = 6;
    color[0] = new Color(1.0, 0.0, 0.0, 1.0);
    color[1] = new Color(0.0, 1.0, 0.0, 1.0);
    color[2] = new Color(0.0, 0.0, 1.0, 1.0);
    wind = w;
}


Paralleogram::Paralleogram(float angle, float side1, float side2, float x, float y, float z, bool w, Color **colors) {
    theta = angle;
    a = side1;
    b = side2;
    coords[0] = x;
    coords[1] = y;
    coords[2] = z;
    point_count = 6;
    for (int i = 0; i < 3; i++) {
        color[i] = new Color(colors[i]->r, colors[i]->g, colors[i]->b, colors[i]->a);
    }
    wind = w;
}


void Paralleogram::increment(int int_val) {}

void Paralleogram::set_point(int idx, float *v) {
    for (int i = 0; i < 3; i++) {
        vv[idx][i] = v[i];
    }
}

float *Paralleogram::get_point(int idx) {
    return vv[idx];

}

void Paralleogram::gen_vertices() {
    float cvt = 3.1415967 / 180.0;
    float ang = theta * cvt;
    int idx = 0;
    float v1[3], v2[3], v3[3], v4[3], v5[3], v6[3];


    float x_offset = chk(b * cos(ang));
    float y_offset = chk(b * sin(ang));
    int offset;
    int sz;
    vertex_count = point_count;
    offset = VERTEX_SIZE + COLOR_SIZE + TEXTURE_SIZE + NORMAL_SIZE;
    sz = offset * vertex_count;

    vertex_size = sz;


    vertices = (float *) malloc(sz * sizeof(float));
    if (!vertices) {
        std::cout << "Parallelogram:  malloc failed\n";
        exit(-1);
    }
    for (int i = 0; i < sz; i++) {
        vertices[i] = -99.0;
    }
    index_size = vertex_count;
    indices = (unsigned int *) malloc(index_size * sizeof(unsigned int));
    if (!indices) {
        std::cout << "Parallelogram: Malloc failed. Cannot allocate indices\n";
        exit(-1);
    }

    indices[0] = 0;
    indices[1] = 1;
    indices[2] = 2;
    indices[3] = 2;
    indices[4] = 3;
    indices[5] = 0;
    if (!have_vertices) {
        v1[0] = coords[0];
        v1[1] = coords[1];
        v1[2] = coords[2];

        v2[0] = coords[0] + a;
        v2[1] = coords[1];
        v2[2] = coords[2];

        v3[0] = coords[0] + a + x_offset;
        v3[1] = coords[1] + y_offset;
        v3[2] = coords[2];

        v4[0] = coords[0] + a + x_offset;
        v4[1] = coords[1] + y_offset;
        v4[2] = coords[2];

        v5[0] = coords[0] + x_offset;
        v5[1] = coords[1] + y_offset;
        v5[2] = coords[2];

        v6[0] = coords[0];
        v6[1] = coords[1];
        v6[2] = coords[2];

        set_point(0, v1);
        set_point(1, v2);
        set_point(2, v3);
        set_point(3, v4);
        set_point(4, v5);
        set_point(5, v6);
    } else {   // really quick fix since I feel behind with addressing really stupid syntax issues
        Extra::set_v(vv[0], v1);
        Extra::set_v(vv[1], v2);
        Extra::set_v(vv[2], v3);
        Extra::set_v(vv[3], v4);
        Extra::set_v(vv[4], v5);
        Extra::set_v(vv[5], v6);
    }

    //lower left corner:
    set_vertex(idx, v1[0], v1[1], v1[2]);
    set_vertex_color(idx, 0);
    set_tex_pos(idx, 0, 0);
    if (wind) {
        Extra::gen_normal3(idx, 9, v1, v2, v3, vertices);
    } else {
        Extra::gen_normal3(idx, 9, v3, v2, v1, vertices);

    }
    idx += offset;

    // lower right corner:
    set_vertex(idx, v2[0], v2[1], v2[2]);
    set_vertex_color(idx, 1);
    set_tex_pos(idx, 0, 1);
    if (wind) {
        Extra::gen_normal3(idx, 9, v2, v3, v1, vertices);
    } else {
        Extra::gen_normal3(idx, 9, v1, v3, v2, vertices);

    }

    idx += offset;

    // upper right corner:
    set_vertex(idx, v3[0], v3[1], v3[2]);
    set_vertex_color(idx, 2);
    set_tex_pos(idx, 1, 1);
    if (wind) {
        Extra::gen_normal3(idx, 9, v3, v1, v2, vertices);
    } else {
        Extra::gen_normal3(idx, 9, v2, v1, v3, vertices);

    }
    idx += offset;

    // Triangle #2

    // upper right corner:
    set_vertex(idx, v4[0], v4[1], v4[2]);
    set_vertex_color(idx, 1);
    set_tex_pos(idx, 1, 1);
    if (wind) {
        Extra::gen_normal3(idx, 9, v4, v5, v6, vertices);
    } else {
        Extra::gen_normal3(idx, 9, v6, v5, v4, vertices);

    }
    idx += offset;
    // Upper left corner:

    set_vertex(idx, v5[0], v5[1], v5[2]);
    set_vertex_color(idx, 2);
    set_tex_pos(idx, 1, 0);
    if (wind) {
        Extra::gen_normal3(idx, 9, v5, v6, v4, vertices);
    } else {
        Extra::gen_normal3(idx, 9, v4, v6, v5, vertices);

    }
    idx += offset;

    // lower left
    set_vertex(idx, v6[0], v6[1], v6[2]);
    set_vertex_color(idx, 1);
    set_tex_pos(idx, 0, 0);
    if (wind) {
        Extra::gen_normal3(idx, 9, v6, v4, v5, vertices);
    } else {
        Extra::gen_normal3(idx, 9, v5, v4, v6, vertices);

    }

}

int Paralleogram::get_vertex_count() {
    return vertex_count;
}

unsigned int *Paralleogram::get_indices() {
    return indices;
}

float *Paralleogram::get_vertices() {
    return vertices;
}

void Paralleogram::set_vertex(int idx, float x1, float y1, float z1) {
    vertices[idx] = x1;
    vertices[idx + 1] = y1;
    vertices[idx + 2] = z1;

}

void Paralleogram::set_tex_pos(int idx, float x, float y) {
    vertices[idx + 7] = x;
    vertices[idx + 8] = y;
}

void Paralleogram::set_vertex_color(int idx, int vtx) {
    vertices[idx + 3] = color[vtx]->r;
    vertices[idx + 4] = color[vtx]->g;
    vertices[idx + 5] = color[vtx]->b;
    vertices[idx + 6] = color[vtx]->a;
}

bool Paralleogram::has_bottom() {
    return true;
}

int Paralleogram::get_vertex_size() {
    return vertex_size;
}

float Paralleogram::chk(float inp) {
    if (abs(inp) < 9.28108e-06) {
        return 0.0;
    } else {
        return inp;
    }

}

void Paralleogram::print_vertices() {
    std::cout << " #:    vertex:\t\tcolor:\t\ttex \t\tNormals\n";
    int offset = VERTEX_SIZE + COLOR_SIZE + TEXTURE_SIZE;
    int cntr = 0;
    int vtx_cnt = 0;
    int pc = 0;
    pc = 2;

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

void Paralleogram::dump_vertex(int offset) {
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

    for (int j = 9; j <= 11; j++) {
        std::cout << vertices[offset + j] << ", ";
    }
    std::cout << "\n";
}

void Paralleogram::rotate(int axis, float angle) {
    Extra::rotate(axis, angle, vertices, VERTEX_SIZE + COLOR_SIZE + TEXTURE_SIZE,
                  vertex_stride, vertex_size);
}

void Paralleogram::translate(glm::vec3 offset) {
    Extra::translate(offset, vertices, VERTEX_SIZE + COLOR_SIZE + TEXTURE_SIZE,
                     vertex_stride, vertex_size);
}