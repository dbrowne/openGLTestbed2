//
// Created by Dwight J. Browne on 11/12/19.
//

#ifndef TESTBED2_ELLIPSE_H
#define TESTBED2_ELLIPSE_H

#include "Color.h"

class Ellipse {
private:
    Color *color[3]{nullptr};
    float coords[3]{};
    float a;
    float b;
    float *vertices{nullptr};
    unsigned int *indices{nullptr};
    int point_count;
    int vertex_size;
    int vertex_count;
    int index_size;
    bool alloced = false;  // to allow for resizing
    int initial_point_count;
    float mult;

    void set_vertex(int idx, float x1, float y1, float z1);

    void set_vertex_color(int idx, int vtx);

    void set_tex_pos(int idx, float x, float y);


public:
    Ellipse();

    ~Ellipse();

    Ellipse(float x, float y, float z, float a1, float b1, float mult, int pc);
    void gen_vertices();

    void set_color(Color c, int idx);

    void set_color(float r, float g, float b, float a, int idx);
    float *get_vertices();

    int get_vertex_count();

    int get_vertex_size();

    void set_mult(float m);

    int get_index_size();

    unsigned int *get_indices();

    bool has_bottom();

    void increment(int int_val);

    void dump_vertex(int offset);

    void print_vertices();

    float *get_coords();

    const int VERTEX_SIZE = 3;
    const int COLOR_SIZE = 4;
    const int TEXTURE_SIZE = 2;
    const int NORMAL_SIZE = 3;
};

#endif //TESTBED2_ELLIPSE_H
