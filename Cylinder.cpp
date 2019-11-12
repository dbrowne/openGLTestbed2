//
// Created by Dwight J. Browne on 11/8/19.
//@TODO: Resize objects
//

#include "Cylinder.h"
#include <cmath>
#include <iostream>


Cylinder::Cylinder() {
    coords[0] = 0;
    coords[1] = 0;
    coords[2] = 0;
    height = 1;
    point_count = 3;
    initial_point_count = point_count;
    ra = 1.0;
    rb = 0;
    r1a = 1.0;
    r1b = 0;
    color[0] = new Color(1.0, 0.0, 0.0, 1.0);
    color[1] = new Color(0.0, 1.0, 0.0, 1.0);
    color[2] = new Color(0.0, 0.0, 1.0, 1.0);
    top = true;
    bottom = true;
}

void Cylinder::gen_vertices() {
    int offset;
    int bot_offset = 0;
    int top_offset = 0;
    int side_offset = 0;
    int sz;
    int idx = 0;
    float x, y, z, x1, y1, z1;
    float incr;
    int cntr = 0;
    float theta = 0;

    float a_point[3] = {0, 0, 0};
    float b_point[3] = {0, 0, 0};
    float c_point[3] = {0, 0, 0};
    float d_point[3] = {0, 0, 0};

    bottom = true;
    top = true;


    offset = VERTEX_SIZE + COLOR_SIZE + TEXTURE_SIZE;
    vertex_count = 12 * point_count;
    top_offset = 3 * point_count * offset;
    sz = offset * vertex_count;
    bot_offset = top_offset + 6 * point_count * offset;



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

    for (int i = 0; i < sz; i++) {
        vertices[i] = -99.0;
    }

    index_size = 12 * vertex_count;
    indices = (unsigned int *) malloc(index_size * sizeof(unsigned int));
    if (!indices) {
        std::cout << "Polyg: Malloc failed. Cannot allocate indices\n";
        exit(-1);
    }

    incr = 2.0 * 3.1415967 / point_count;

    while (cntr < 2 * point_count) {
        if (cntr % 2 == 0) {
            if (theta > 0) {
                theta -= incr;
            }
            // form top and bottom circles
            x = chk(ra * cos(theta) + coords[0]);    //top
            y = chk(ra * sin(theta) + coords[1]);
            z = coords[2] + height;

            x1 = chk(r1a * cos(theta) + coords[0]);   //bottom
            y1 = chk(r1a * sin(theta) + coords[1]);
            z1 = coords[2];
            //top center
            set_vertex(idx, coords[0], coords[1], z);
            set_vertex_color(idx, 0);
            set_tex_pos(idx, 0.0, 0.0);

            // bottom center
            set_vertex(idx + bot_offset, coords[0], coords[1], coords[2]);
            set_vertex_color(idx + bot_offset, 0);
            set_tex_pos(idx + bot_offset, 0.0, 0.0);

            idx += offset;

            //1st point on top
            set_vertex(idx, x, y, z);
            set_vertex_color(idx, 1);
            set_tex_pos(idx, 1, 1);

            //1st point on bottom
            set_vertex(idx + bot_offset, x1, y1, z1);
            set_vertex_color(idx + bot_offset, 1);
            set_tex_pos(idx + bot_offset, 1, 1);

            a_point[0] = x;
            a_point[1] = y;
            a_point[2] = z;
            b_point[0] = x1;
            b_point[1] = y1;
            b_point[2] = z1;
        } else {
            x = chk(ra * cos(theta) + coords[0]);
            y = chk(ra * sin(theta) + coords[1]);
            z = coords[2] + height;
            set_vertex(idx, x, y, z);
            set_vertex_color(idx, 2);
            set_tex_pos(idx, 1, 0);

            x1 = chk(r1a * cos(theta) + coords[0]);   //bottom
            y1 = chk(r1a * sin(theta) + coords[1]);
            z1 = coords[2];

            set_vertex(idx + bot_offset, x1, y1, z1);
            set_vertex_color(idx + bot_offset, 2);
            set_tex_pos(idx + bot_offset, 1, 1);
            d_point[0] = x;
            d_point[1] = y;
            d_point[2] = z;
            c_point[0] = x1;
            c_point[1] = y1;
            c_point[2] = z1;

            set_side(side_offset + top_offset, a_point, b_point, c_point, d_point, offset);
            side_offset += 6 * offset;
        }
        idx += offset;
        cntr++;

        theta += incr;

    }

}


Cylinder::~Cylinder() = default;

float *Cylinder::get_vertices() {
    return vertices;
}

void Cylinder::increment(int int_val) {
    point_count += int_val;
    if (point_count < 3) {
        point_count = initial_point_count;
    }

}
void Cylinder::set_point_count(int pc) {
    point_count = pc;
}

Cylinder::Cylinder(float r, float r1, int pc, float h) {
    coords[0] = 0.0;
    coords[1] = 0.0;
    coords[2] = 0.0;
    height = h;
    point_count = pc;
    initial_point_count = point_count;
    ra = r;
    rb = 0;
    r1a = r1;
    r1b = 0;
    color[0] = new Color(1.0, 0.0, 0.0, 1.0);
    color[1] = new Color(0.0, 1.0, 0.0, 1.0);
    color[2] = new Color(0.0, 0.0, 1.0, 1.0);
    top = true;
    bottom = true;
}

Cylinder::Cylinder(float r, float r1, int pc, float h, float x, float y, float z) {
    coords[0] = x;
    coords[1] = y;
    coords[2] = z;
    height = h;
    point_count = pc;
    initial_point_count = point_count;
    ra = r;
    rb = 0;
    r1a = r1;
    r1b = 0;
    color[0] = new Color(1.0, 0.0, 0.0, 1.0);
    color[1] = new Color(0.0, 1.0, 0.0, 1.0);
    color[2] = new Color(0.0, 0.0, 1.0, 1.0);
    top = true;
    bottom = true;
}


Cylinder::Cylinder(float r, int pc, float h, float x, float y, float z) {
    coords[0] = x;
    coords[1] = y;
    coords[2] = z;
    height = h;
    point_count = pc;
    initial_point_count = point_count;
    ra = r;
    rb = 0;
    r1a = r;
    r1b = 0;
    color[0] = new Color(1.0, 0.0, 0.0, 1.0);
    color[1] = new Color(0.0, 1.0, 0.0, 1.0);
    color[2] = new Color(0.0, 0.0, 1.0, 1.0);
    top = true;
    bottom = true;
}

Cylinder::Cylinder(float r, int pc, float h) {
    coords[0] = 0;
    coords[1] = 0;
    coords[2] = 0;
    height = h;
    point_count = pc;
    initial_point_count = point_count;
    ra = r;
    rb = 0;
    r1a = r;
    r1b = 0;
    color[0] = new Color(1.0, 0.0, 0.0, 1.0);
    color[1] = new Color(0.0, 1.0, 0.0, 1.0);
    color[2] = new Color(0.0, 0.0, 1.0, 1.0);
    top = true;
    bottom = true;

}

void ::Cylinder::set_vertex(int idx, float x1, float y1, float z1) {
    vertices[idx] = x1;
    vertices[idx + 1] = y1;
    vertices[idx + 2] = z1;
}

void Cylinder::set_vertex_color(int idx, int vtx) {
    vertices[idx + 3] = color[vtx]->r;
    vertices[idx + 4] = color[vtx]->g;
    vertices[idx + 5] = color[vtx]->b;
    vertices[idx + 6] = color[vtx]->a;
}

void Cylinder::set_tex_pos(int idx, float x, float y) {
    vertices[idx + 7] = x;
    vertices[idx + 8] = y;
}

void Cylinder::set_side(int idx, float *a, float *b, float *c, float *d, int offset) {
    set_vertex(idx, a);
    set_vertex_color(idx, 0);
    set_tex_pos(idx, 1, 1);
    idx += offset;

    set_vertex(idx, b);
    set_vertex_color(idx, 0);
    set_tex_pos(idx, 1, 1);
    idx += offset;

    set_vertex(idx, c);
    set_vertex_color(idx, 1);
    set_tex_pos(idx, 1, 1);
    idx += offset;


    set_vertex(idx, c);
    set_vertex_color(idx, 1);
    set_tex_pos(idx, 1, 1);
    idx += offset;

    set_vertex(idx, d);
    set_vertex_color(idx, 2);
    set_tex_pos(idx, 1, 1);
    idx += offset;

    set_vertex(idx, a);
    set_vertex_color(idx, 0);
    set_tex_pos(idx, 1, 1);
}

void Cylinder::set_vertex(int idx, float *p) {
    vertices[idx] = p[0];
    vertices[idx + 1] = p[1];
    vertices[idx + 2] = p[2];
}

void Cylinder::print_vertices() {
    std::cout << " #:    vertex:\t\tcolor:\t\ttex \n";
    int offset = VERTEX_SIZE + COLOR_SIZE + TEXTURE_SIZE;
    int cntr = 0;
    int vtx_cnt = 0;
    int pc = 0;
    pc = point_count * 4;

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

void Cylinder::dump_vertex(int offset) {
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

float Cylinder::chk(float inp) {
    if (abs(inp) < 9.28108e-06) {
        return 0.0;
    } else {
        return inp;
    }

}

unsigned int *::Cylinder::get_indices() {
    return indices;
}

int Cylinder::get_index_size() {
    return index_size;
}

int Cylinder::get_vertex_count() {
    return vertex_count;
}

int Cylinder::get_vertex_size() {
    return vertex_size;
}

bool Cylinder::has_bottom() {
    return bottom;
}

