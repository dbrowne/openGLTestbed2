//
// Created by Dwight J. Browne on 11/3/19.
//@TODO:remove default constructor
//@TODO:Correct Triangle windings
//@TODO:Add Test mode
//@TODO:FIX index array


#ifndef TESTBED2_PRIMATIVES_H
#define TESTBED2_PRIMATIVES_H

#include<cmath>
#include <vector>
#include "Color.h"

const double PI = 3.1415967;


class Polyg
{
private:
    float radius;
    float z;
    float *vertices{};
    unsigned int *indices{};
    float point_count;
    Color *color[3]{};    // for each vertex


    void set_vertex_color(int idx, int vtx);

    void dump_vertex(int offset);

    void set_vertex(int idx, float x, float y, float z1);

    void set_tex_pos(int idx, float x, float y);


public:
    const int VERTEX_SIZE = 3;
    const int COLOR_SIZE = 4;
    const int TEXTURE_SIZE = 2;
    const int MAX_VERT_ELEMS = 8;

    Polyg();

    Polyg(float radius, float point_count);

    Polyg(float rad, float pc, Color c1);

    ~Polyg();

    void set_z_axis(float z_val); // not the most elegant but I am working fast and this is my 2nd C++ program
    void set_radius(float radius);
    void set_point_Count(float point_count);

    void set_color(Color c);

    void set_color(int v, Color c);

    void set_color(Color c0, Color c1, Color c2);

    void set_alpha(float a);

    void set_alpha(int v, float a);

    void print_vertices(void);

    void print_indices(void);

    void gen_vertices();
    float *get_vertices();

    unsigned int *get_indices();

    void set_index(int idx, int pos);
};


#endif //TESTBED2_PRIMATIVES_H
