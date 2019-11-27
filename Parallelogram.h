//
// Created by Dwight J. Browne on 11/13/19.
//

#ifndef TESTBED2_PARALLELOGRAM_H
#define TESTBED2_PARALLELOGRAM_H

#import "Color.h"
#include <glm/vec3.hpp>

class Paralleogram {
private:
    Color *color[3]{nullptr};
    float coords[3]{};
    float *vertices{nullptr};
    unsigned int *indices{nullptr};
    float theta;
    float a;
    float b;
    int point_count = 6;
    int vertex_size;
    int vertex_count;
    int index_size;

    bool bottom = true;
    bool wind = true;
    bool have_vertices = false;
    float vv[6][3];


    void set_vertex(int idx, float x1, float y1, float z1);
    void set_vertex_color(int idx, int vtx);
    void set_tex_pos(int idx, float x, float y);
    float chk(float inp);

    void set_point(int idx, float *v);

public:
    Paralleogram();

    ~Paralleogram();

    Paralleogram(float angle, float side1, float side2, float x, float y, float z);

    Paralleogram(float angle, float side1, float side2, float x, float y, float z, bool w);

    Paralleogram(float angle, float side1, float side2, float x, float y, float z, bool w, Color **colors);

    Paralleogram(float *vx1, float *vx2, float *vx3, float *vx4, float w);

    Paralleogram(float *vx1, float *vx2, float *vx3, float *vx4, float w, Color **colors);


    void rotate(int axis, float angle);

    void translate(glm::vec3 offset);

    float *get_vertices();

    unsigned int *get_indices();

    int get_vertex_count();

    int get_vertex_size();

    void gen_vertices();

    bool has_bottom();

    void increment(int int_val);

    void print_vertices();

    void dump_vertex(int offset);

    float *get_point(int idx);

    const int VERTEX_SIZE = 3;
    const int COLOR_SIZE = 4;
    const int TEXTURE_SIZE = 2;
    const int NORMAL_SIZE = 3;
    int vertex_stride = VERTEX_SIZE + COLOR_SIZE + TEXTURE_SIZE + NORMAL_SIZE;

};

#endif //TESTBED2_PARALLELOGRAM_H

