//
// Created by Dwight J. Browne on 11/23/19.
//

#include "box.h"
#include "glad.h"
#include <iostream>
#include "extra_funcs.h"
Box::Box() {
    //unit cube
    theta = 90;
    a = 1;
    b = 1;
    height = 1;
    point_count = 6;
    coords[0] = 0;
    coords[1] = 0;
    coords[2] = 0;
    color[0] = new Color(1, 0, 0, 1);
    color[0] = new Color(1, 1, 1, 1);
    color[0] = new Color(0, 0, 1, 1);
}

Box::Box(float angle, float side1, float side2, float h, float x, float y, float z) {
    theta = angle;
    a = side1;
    b = side2;

    height = h;
    coords[0] = x;
    coords[1] = y;
    coords[2] = z;
    color[0] = new Color(1, 0, 1, 1);
    color[0] = new Color(0, 1, 1, 1);
    color[0] = new Color(1, 1, 0, 1);
}

void Box::gen_vertices() {

    vertex_stride = VERTEX_SIZE + COLOR_SIZE + TEXTURE_SIZE + NORMAL_SIZE;

    float va[4][3], vb[4][3]; // this represents the vertices of the two sides that will form the edges
    // va4........va3       Front para
    // va1........va2

    // vb4........vb3      Back para
    // vb1........vb2

    // top para =    va4, va3, vb3, vb4
    //               va4.............va3
    //               vb4.............va3
    // bottom = vb1, vb2, va2, va1
    // right side = vb2,va2, va3, vb3
    // left side = vb1, va1, va4, vb4

    int vx_size = 0;
    float *vpa, *vpb;
    int offset = 0;
    int side_count = 6;

    sides[0] = new Paralleogram(theta, a, b, coords[0], coords[1], coords[2], false); //back
    sides[0]->gen_vertices();
//    sides[0]->print_vertices();

    sides[1] = new Paralleogram(theta, a, b, coords[0], coords[1], coords[2] + height); //Front
    sides[1]->gen_vertices();

    for (int i = 0; i < 3; i++) {
        vpa = sides[1]->get_point(i);
        vpb = sides[0]->get_point(i);
        for (int j = 0; j < 3; j++) {
            va[i][j] = vpa[j];
            vb[i][j] = vpb[j];
        }
    }

    vpa = sides[1]->get_point(4);
    vpb = sides[0]->get_point(4);
    for (int i = 0; i < 3; i++) {
        va[3][i] = vpa[i];
        vb[3][i] = vpb[i];
    }
    sides[2] = new Paralleogram(va[3], va[2], vb[2], vb[3], true); //top
    sides[3] = new Paralleogram(va[0], va[1], vb[1], vb[0], false); //bottom
    sides[4] = new Paralleogram(va[1], vb[1], vb[2], va[2], true); //right side
    sides[5] = new Paralleogram(va[0], vb[0], vb[3], va[3], true); //left side

    for (int i = 2; i < 6; i++) {
        sides[i]->gen_vertices();
    }


    vx_size = sides[1]->get_vertex_size();
    vertex_size = 6 * vx_size;
    vertices = (float *) malloc(sizeof(float) * vertex_size);
    if (vertices == nullptr) {
        std::cout << "Box::gen_vertices:  cannot allocate memory \n";
        exit(-1);
    }

    for (int i = 0; i < side_count; i++) {
        vpa = sides[i]->get_vertices();
        std::memcpy(&vertices[offset], vpa, vx_size * sizeof(float));
        offset += vx_size;
    }

    vertex_count = 6 * side_count;

}

int Box::get_vertex_count() {


    return (vertex_count);

}

float *Box::get_vertices() {
    return vertices;
}

int Box::get_vertex_size() {
    return (vertex_size);
}

unsigned int *Box::get_indices() {
    return nullptr;
}

void Box::dump_vertex(int offset) {}

bool Box::has_bottom() { return true; }

void Box::increment(int int_val) {}

void Box::set_vertex(int idx, float x1, float y1, float z1) {}

void Box::set_tex_pos(int idx, float x, float y) {}

Box::~Box() = default;

void Box::set_vertex_color(int idx, int vtx) {

}

void Box::print_vertices() {
    for (int i = 0; i < 6; i++) {
        sides[i]->print_vertices();
    }
}

void Box::delete_buffers() {
    glDeleteVertexArrays(1, &box_vao);
    glDeleteBuffers(1, &box_vbo);
}

void Box::draw() {

    glGenVertexArrays(1, &box_vao);
    glGenBuffers(1, &box_vbo);
    glBindVertexArray(box_vao);
    glBindBuffer(GL_ARRAY_BUFFER, box_vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices) * vertex_count * vertex_stride, vertices,
                 GL_STATIC_DRAW);
    glCheckError();
    // position attribute
    glVertexAttribPointer(0, VERTEX_SIZE, GL_FLOAT, GL_FALSE,
                          (vertex_stride) * sizeof(float),
                          (void *) 0);
    glEnableVertexAttribArray(0);
    glCheckError();
    //color attribute
    glVertexAttribPointer(1, COLOR_SIZE, GL_FLOAT, GL_FALSE,
                          (vertex_stride) * sizeof(float),
                          (void *) (VERTEX_SIZE * sizeof(float)));
    glCheckError();
    glEnableVertexAttribArray(1);



    //texture attribute
    glVertexAttribPointer(2, TEXTURE_SIZE, GL_FLOAT, GL_FALSE,
                          (vertex_stride) * sizeof(float),
                          (void *) ((VERTEX_SIZE + COLOR_SIZE) * sizeof(float)));
    glCheckError();
    glEnableVertexAttribArray(3);
    //Normal attribute
    glVertexAttribPointer(3, NORMAL_SIZE, GL_FLOAT, GL_FALSE,
                          (vertex_stride) * sizeof(float),
                          (void *) ((VERTEX_SIZE + COLOR_SIZE + TEXTURE_SIZE) * sizeof(float)));

    glCheckError();
    glEnableVertexAttribArray(3);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(box_vao);

    glCheckError();
    glDrawArrays(GL_TRIANGLES, 0, vertex_count);
    glCheckError();

};