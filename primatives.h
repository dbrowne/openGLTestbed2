//
// Created by Dwight J. Browne on 11/3/19.
//@TODO:Correct Triangle windings
//@TODO:Add Test mode
//@TODO:FIX index array
//@TODO: Resize objects


#ifndef TESTBED2_PRIMATIVES_H
#define TESTBED2_PRIMATIVES_H

#include<cmath>
#include <vector>
#include "Color.h"

const double PI = 3.1415967;

class Axes {
private:
    float axes[3];
    Color axis_color[3];
    int symmetric;
    float *vertices{nullptr};
    float point_count;

    void prt_ax(int offst, int sz);

    unsigned int vertex_count = 6;


public:
    Axes(float ax_len);

    ~Axes();

    void set_axis_color(int axis, Color c);

    void set_axis_len(int axis, float axis_len);

    void print_vertices();


    float *get_vertices(void);

    void gen_vertices();

    void set_symmetric(int sym);

    const int VERTEX_SIZE = 3;
    const int COLOR_SIZE = 4;
    const int TEXTURE_SIZE = 0;
    const int NORMAL_SIZE = 0;
    int vertex_size;

    unsigned int get_vertex_count();

    int get_vertex_size();


};



class Polyg
{
private:
    float coord[3];
    float height;
    float radius;
    float *vertices{};
//    float vertices[216];
    unsigned int *indices{};
    int point_count;
    Color *color[3]{};    // for each vertex
    int vertex_size;
    int vertex_count;
    int index_size;
    bool bottom;

    void set_vertex_color(int idx, int vtx);

    void dump_vertex(int offset);

    void set_vertex(int idx, float x1, float y1, float z1);

    void set_tex_pos(int idx, float x, float y);   //set texture
    void set_normal(int idx);


public:
    const int VERTEX_SIZE = 3;
    const int NORMAL_SIZE = 3;
    const int COLOR_SIZE = 4;
    const int TEXTURE_SIZE = 2;
    const int MAX_VERT_ELEMS = 8;

    Polyg();

    Polyg(float rad, float pc);
    Polyg(float rad, float pc, float x, float y, float z, float h);
    Polyg(float rad, float pc, float h);
    Polyg(float rad, float pc, Color c1);
    Polyg(float rad, float pc, Color c1, float h);

    bool has_bottom();


    ~Polyg();

    void set_pos(float val, int axis);
    void set_height(float h);
    void set_radius(float radius);
    void set_point_Count(float point_count);
    void set_color(Color c);
    void set_color(int v, Color c);
    void set_color(Color c0, Color c1, Color c2);
    void set_alpha(float a);
    void set_alpha(int v, float a);
    void print_vertices(void);
    void print_indices(void);

    void increment(int int_val);
    void gen_vertices();
    float *get_vertices();

    unsigned int *get_indices();

    void set_index(int idx, int pos);

    int get_vertex_size(void);

    int get_index_size(void);

    int get_vertex_count();
};


#endif //TESTBED2_PRIMATIVES_H
