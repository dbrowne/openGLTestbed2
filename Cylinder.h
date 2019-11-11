//
// Created by Dwight J. Browne on 11/8/19.
//

#ifndef TESTBED2_CYLINDER_H
#define TESTBED2_CYLINDER_H

#include "Color.h"


class Cylinder {
private:
    float coords[3]{};
    float ra;
    float rb;
    float r1a;
    float r1b;
    float height;
    Color *color[3]{nullptr};
    float *vertices{nullptr};
    unsigned int *indices{nullptr};
    int vertex_size{};
    int vertex_count{};
    bool top;
    bool bottom;
    int point_count;
    int index_size{};
    bool alloced = false;  // to allow for resizing

    void set_vertex(int idx, float x1, float y1, float z1);

    void set_vertex(int idx, float *p);

    void set_vertex_color(int idx, int vtx);

    void set_tex_pos(int idx, float x, float y);

    void set_side(int idx, float *a, float *b, float *c, float *d, int offset);

public:
    Cylinder();

    ~Cylinder();

    Cylinder(float r, int pc, float height);

    void set_point_count(int pc);

    Cylinder(float r, int pc, float height, float x, float y, float z);

    Cylinder(float r, float r1, int pc, float height, float x, float y, float z);

    Cylinder(float r, float r1, int pc, float h);

    float *get_vertices();

    void gen_vertices();

    void set_color(int idx, Color c);

    bool has_top();

    bool has_bottom();

    bool check_indices();

    void print_vertices();

    void dump_vertex(int offset);

    unsigned int *get_indices();

    int get_vertex_count();

    int get_vertex_size();

    int get_index_size();

    float chk(float inp);

    const int VERTEX_SIZE = 3;
    const int COLOR_SIZE = 4;
    const int TEXTURE_SIZE = 2;

};


#endif //TESTBED2_CYLINDER_H
