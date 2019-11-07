//
// Created by Dwight J. Browne on 11/3/19.
//

#include "primatives.h"
#include <iostream>
#include "Color.h"

Polyg::Polyg() {
    radius = 1.0;
    point_count = 16;
    z = 0;
    color[0] = new Color(1.0, 0.0, 0.0, 1.0);
    color[1] = new Color(0.0, 1.0, 0.0, 1.0);
    color[2] = new Color(0.0, 0.0, 1.0, 1.0);
}

Polyg::Polyg(float rad, float pc) {
    radius = rad;
    point_count = pc;
    z = 0;
    color[0] = new Color(1.0, 0.0, 0.0, 1.0);
    color[1] = new Color(0.0, 1.0, 0.0, 1.0);
    color[2] = new Color(0.0, 0.0, 1.0, 1.0);

}

Polyg::Polyg(float rad, float pc, const Color c1) {
    radius = rad;
    point_count = pc;
    z = 0;
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
    float x, y;
    float incr;
    int offset = 0;
    int idx = 0;
    int index_cntr = 0;
    int index_pos = 0;
    int bot_offset = 0;

    offset = VERTEX_SIZE + COLOR_SIZE + TEXTURE_SIZE;
    sz = offset * point_count * 3;

    if (z != 0) {
        bot_offset = sz;
        sz = sz * 2;
    }

    vertices = (float *) malloc(sz * sizeof(float));
    if (!vertices) {
        std::cout << "Polyg: Malloc failed. cannot allocate vertices\n";
        exit(-1);
    }

    indices = (unsigned int *) malloc(3 * point_count * sizeof(unsigned int));
    if (!indices) {
        std::cout << "Polyg: Malloc failed. Cannot allocate indices\n";
        exit(-1);
    }

    incr = 2 * PI / point_count;
    cntr = 0;

    while (cntr < 2 * point_count) {
        if (cntr % 2 == 0) {
            if (theta > 0) {
                theta -= incr;
            }
            x = radius * cos(theta);
            y = radius * sin(theta);

            set_vertex(idx, 0, 0, z);
            set_vertex_color(idx, 0);
            set_tex_pos(idx, 0.0, 0.0);
            if (z != 0) {
                set_vertex(idx + bot_offset, 0, 0, 0);
                set_vertex_color(idx + bot_offset, 0);
                set_tex_pos(idx + bot_offset, 0.0, 0.0);
            }
            indices[index_pos++] = 0;
            idx += offset;

            set_vertex(idx, x, y, 0);
            set_vertex_color(idx, 1);
            set_tex_pos(idx, 1, 1);
            if (z != 0) {
                set_vertex(idx + bot_offset, x, y, 0);
                set_vertex_color(idx + bot_offset, 0);
                set_tex_pos(idx + bot_offset, 1, 1);
            }
            index_cntr++;
            indices[index_pos++] = index_cntr;
        } else {
            x = radius * cos(theta);
            y = radius * sin(theta);
            set_vertex(idx, x, y, 0);
            set_vertex_color(idx, 2);
            set_tex_pos(idx, 1, 0);
            if (z != 0) {
                set_vertex(idx + bot_offset, x, y, 0);
                set_vertex_color(idx + bot_offset, 0);
                set_tex_pos(idx + bot_offset, 1, 1);
            }
            indices[index_pos++] = index_cntr + 1;
        }
        idx += offset;
        cntr++;

        theta += incr;
    }
}


float *::Polyg::get_vertices() {
    return vertices;
}

unsigned int *::Polyg::get_indices() {
    return indices;
}

void ::Polyg::set_vertex(int idx, float x, float y, float z1) {
    vertices[idx] = x;
    vertices[idx + 1] = y;
    vertices[idx + 2] = z1;
}

void Polyg::set_vertex_color(int idx, int vtx) {
    vertices[idx + 3] = color[vtx]->r;
    vertices[idx + 4] = color[vtx]->g;
    vertices[idx + 5] = color[vtx]->b;
    vertices[idx + 6] = color[vtx]->a;
}

void Polyg::set_tex_pos(int idx, float x, float y) {
    vertices[idx + 7] = x;
    vertices[idx + 8] = y;
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


void Polyg::print_vertices() {
    std::cout << " #:    vertex:\t\tcolor:\t\ttex \n";
    int offset = VERTEX_SIZE + COLOR_SIZE + TEXTURE_SIZE;
    int cntr = 0;
    int vtx_cnt = 0;
    int pc = 0;
    if (z != 0) {
        pc = 2 * point_count;
    } else {
        pc = point_count;
    }

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

void Polyg::dump_vertex(int offset) {
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
    std::cout << "\n";
}

void Polyg::print_indices() {
    int offset = 0;
    for (int i = 0; i < point_count; i++) {
        std::cout << indices[offset] << ", " << indices[offset + 1] << ", " << indices[offset + 2] << "\n";
        offset += 3;
        if (i % 3 == 0 && i != 0) {
            std::cout << "\n\n";
        }
    }
    std::cout << "\n";
}

void Polyg::set_index(int idx, int pos) {
    indices[idx] = pos;
}

void Polyg::set_z_axis(float z_val) {
    z = z_val;
}