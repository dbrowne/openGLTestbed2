//
// Created by Dwight J. Browne on 11/23/19.
//

#ifndef TESTBED2_BOX_H
#define TESTBED2_BOX_H

#include "Parallelogram.h"
#include "Color.h"
#include "Prim_base.h"

class Box {
private:
    Color *color[3]{nullptr};
    float coords[3]{};
    float *vertices{nullptr};
    float theta;
    float a;
    float b;
    float height;
    float point_count;
    int vertex_size;
    int vertex_count;
    int index_size;
    bool bottom = true;
    Paralleogram *sides[6] = {};
    unsigned int box_vao;
    unsigned int box_vbo;
    int vertex_stride = 0;
    void set_vertex(int idx, float x1, float y1, float z1);

    void set_vertex_color(int idx, int vtx);

    void set_tex_pos(int idx, float x, float y);


public:
    Box();

    ~Box();

    Box(float angle, float side1, float side2, float h, float x, float y, float z);

    float *get_vertices();

    unsigned int *get_indices();

    int get_vertex_count();

    int get_vertex_size();

    void gen_vertices();

    bool has_bottom();

    void increment(int int_val);

    void print_vertices();

    void dump_vertex(int offset);

    void delete_buffers();

    const int VERTEX_SIZE = 3;
    const int COLOR_SIZE = 4;
    const int TEXTURE_SIZE = 2;
    const int NORMAL_SIZE = 3;

    void rotate(int axis, float angle);

    void translate(glm::vec3 offset);

    void draw();

private:
    void set_v(float *in, float *out);


};

#endif //TESTBED2_BOX_H
