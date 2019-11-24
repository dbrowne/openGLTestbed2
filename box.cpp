//
// Created by Dwight J. Browne on 11/23/19.
//

#include "box.h"


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


int Box::gen_vertices() {
    Paralleogram *sides[6] = {};
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


    float *vpa, *vpb;

    sides[0] = new Paralleogram(theta, a, b, coords[0], coords[1], coords[2], -1); //back
    sides[1] = new Paralleogram(theta, a, b, coords[0], coords[1], coords[2] + height); //Front

    for (int i = 0; i < 3; i++) {
        vpa = sides[1]->get_point(i);
        vpb = sides[0]->get_point(i);
        for (int j = 0; j < 3; j++) {
            va[i][j] = vpa[j];
            vb[i][j] = vpb[j];
        }
    }

    vpa = sides[1]->get_point(5);
    vpb = sides[0]->get_point(5);
    for (int i = 0; i < 3; i++) {
        va[3][i] = vpa[i];
        vb[3][i] = vpb[i];
    }
    sides[2] = new Paralleogram(va[3], va[2], vb[2], vb[3], 1); //top
    sides[3] = new Paralleogram(vb[0], vb[1], va[1], va[0], 1); //bottom
    sides[4] = new Paralleogram(vb[1], va[1], va[2], vb[2], 1); //right side
    sides[5] = new Paralleogram(vb[0], va[0], va[3], vb[3], 1); //left side






}

int Box::get_vertex_count() {}

float *Box::get_vertices() {}

int Box::get_vertex_size() {}

unsigned int *Box::get_indices() {}

void Box::dump_vertex(int offset) {}

bool Box::has_bottom() { return true; }

void Box::increment(int int_val) {}

float Box::chk(float inp) {}

void Box::set_vertex(int idx, float x1, float y1, float z1) {}

void Box::set_tex_pos(int idx, float x, float y) {}

Box::~Box() = default;

void Box::set_vertex_color(int idx, int vtx) {

}
