//
// Created by Dwight J. Browne on 11/13/19.
//

#ifndef TESTBED2_PARALLELOGRAM_H
#define TESTBED2_PARALLELOGRAM_H

#import "Color.h"

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

    void set_vertex(int idx, float x1, float y1, float z1);

    void set_vertex_color(int idx, int vtx);

    void set_tex_pos(int idx, float x, float y);

    float chk(float inp);

public:
    Paralleogram();

    ~Paralleogram();

    Paralleogram(float angle, float side1, float side2, float x, float y, float z);

    float *get_vertices();

    unsigned int *get_indices();

    int get_vertex_count();

    int get_vertex_size();

    void gen_vertices();

    bool has_bottom();

    void increment(int int_val);

    void print_vertices();

    void dump_vertex(int offset);

    const int VERTEX_SIZE = 3;
    const int COLOR_SIZE = 4;
    const int TEXTURE_SIZE = 2;
    const int NORMAL_SIZE = 3;


};

#endif //TESTBED2_PARALLELOGRAM_H

