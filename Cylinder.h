//
// Created by Dwight J. Browne on 11/8/19.
//

#ifndef TESTBED2_CYLINDER_H
#define TESTBED2_CYLINDER_H

#include "Color.h"


class Cylinder {
private:
    float coords[3];
    float ra;
    float rb;
    float r1a;
    float r1b;
    float height;
    Color *color[3]{};
//    float vertices[324];
    float *vertices{};
    unsigned int *indices{};
    int vertex_size;
    int vertex_count;
    bool top;
    bool bottom;
    int point_count;
    int index_size;

//    int test_index[36]={0,1,2,0,2,3,0,3,1,1,4,5,1,5,2,2,5,6,2,6,3,3,6,4,3,4,1,754,7,6,5,7,4,6};

    void set_vertex(int idx, float x1, float y1, float z1);

    void set_vertex(int idx, float *p);

    void set_vertex_color(int idx, int vtx);

    void set_tex_pos(int idx, float x, float y);

    void set_side(int idx, float *a, float *b, float *c, float *d, int offset);

public:
    Cylinder();

    ~Cylinder();

    Cylinder(float r, int pc, float height);

    Cylinder(float r, int pc, float height, float x, float y, float z);

    Cylinder(float r, float r1, int pc, float h);

    float *get_vertices(void);

    void gen_vertices(void);

    void set_color(int idx, Color c);

    bool has_top(void);

    bool has_bottom(void);

    bool check_indices(void);

    void print_vertices();

    void dump_vertex(int offset);

    unsigned int *get_indices(void);

    int get_vertex_count(void);

    int get_vertex_size(void);

    int get_index_size();

    const int VERTEX_SIZE = 3;
    const int COLOR_SIZE = 4;
    const int TEXTURE_SIZE = 2;

};


#endif //TESTBED2_CYLINDER_H
