//
// Created by Dwight J. Browne on 11/27/19.
//

#include "Dragonfly.h"

Dragonfly::Dragonfly() {
    vertex_size = 0;
    const int WING_COUNT = 4;
    Color *c[3];
    Ellipse *wings[WING_COUNT];
    const int TEETH = 20;

    c[0] = new Color(0, 0, 1, 1);
    c[1] = new Color(0, 1, 1, 1);
    c[2] = new Color(1, 0, 0, 1);

    Sphere *yy = new Sphere(1.5, 72, 72, true, c);
    yy->translate(glm::vec3(0, 3.5, -.85));
    vertex_size += yy->getInterleavedVertexSize();

    c[0]->r = 0;
    c[0]->g = 0;
    c[0]->b = 1;
    c[1]->r = 0.5;
    c[1]->g = 0.5;
    c[1]->b = 1;
    c[2]->r = .8;
    c[2]->g = .5;
    c[2]->b = 1;
    int cyl_count = 6;
    Cylinder *tail_segments[cyl_count];
    for (int i = 0; i < cyl_count; i++) {
        tail_segments[i] = new Cylinder(1.25, 1, 36, 2, 0, 0, 0);
        tail_segments[i]->gen_vertices();
        vertex_size += tail_segments[i]->get_vertex_size() * sizeof(float);
        tail_segments[i]->rotate(0, 90);
        tail_segments[i]->translate(glm::vec3(0, -1 - i * 2, -.85));
    }

    Sphere *ey1 = new Sphere(.5, 72, 18, true, c);
    vertex_size += ey1->getInterleavedVertexSize();
    Sphere *ey2 = new Sphere(.5, 72, 18, true, c);
    vertex_size += ey2->getInterleavedVertexSize();

    ey1->rotate(0, 105);
    ey1->rotate(1, 15);
    ey1->translate(glm::vec3(1, 4, .45));

    ey2->rotate(0, 105);
    ey2->rotate(1, -15);
    ey2->translate(glm::vec3(-1, 4, .45));

    float y_off = 4.95;
    Box *bb = new Box(90, 2, .25, .0625, 0, 0, 0);
    bb->gen_vertices();
    vertex_size += bb->get_vertex_size() * sizeof(float);
    bb->translate(glm::vec3(-1, y_off, -1.25));

    Box *bb2 = new Box(90, 2, .25, .0625, 0, 0, 0);
    bb2->gen_vertices();
    vertex_size += bb2->get_vertex_size() * sizeof(float);
    bb2->translate(glm::vec3(-1, y_off, -1.75));

    Box *bb3 = new Box(90, .25, .0625, .5, 0, 0, 0);
    bb3->gen_vertices();
    vertex_size += bb3->get_vertex_size() * sizeof(float);
    bb3->rotate(0, 180);
    bb3->rotate(2, 90);
    bb3->translate(glm::vec3(-1, y_off, -1.1875));

    Box *bb4 = new Box(90, .25, .0625, .5625, 0, 0, 0);
    bb4->gen_vertices();
    vertex_size += bb4->get_vertex_size() * sizeof(float);
    bb4->rotate(0, 180);
    bb4->rotate(2, 90);
    bb4->translate(glm::vec3(1., y_off, -1.1875));

    c[0]->r = 0;
    c[0]->g = 0;
    c[0]->b = 0;
    c[1]->r = 0;
    c[1]->g = 0;
    c[1]->b = 0;
    c[2]->r = 0;
    c[2]->g = 0;
    c[2]->b = 0;

    Box *back = new Box(90, 2, .5625, .005, 0, 0, 0, c);
    back->gen_vertices();
    vertex_size += back->get_vertex_size() * sizeof(float);
    back->rotate(0, -90);
    back->translate(glm::vec3(-1, y_off, -1.1875));
    Cylinder *cc = new Cylinder(1.5, 1.125, 36, 4, 0, 0, 0);
    cc->gen_vertices();
    vertex_size += cc->get_vertex_size() * sizeof(float);
    cc->rotate(0, 90.0);
    cc->translate(glm::vec3(0., 3., -.85));

    Polyg *teeth[TEETH];
    float t_z = -1.70;
    float t_y = 5.0;
    teeth[0] = new Polyg(.0625, 36, .27);
    teeth[0]->gen_vertices();
    teeth[0]->translate(glm::vec3(0, t_y, t_z));

    teeth[1] = new Polyg(.0625, 36, .27);
    teeth[1]->gen_vertices();
    teeth[1]->translate(glm::vec3(-.25, t_y, t_z));


    teeth[2] = new Polyg(.0625, 36, .27);
    teeth[2]->gen_vertices();
    teeth[2]->rotate(0, -17);
    teeth[2]->translate(glm::vec3(-.45, t_y, t_z));

    teeth[3] = new Polyg(.0625, 36, .27);
    teeth[3]->gen_vertices();
    teeth[3]->rotate(0, -27);
    teeth[3]->translate(glm::vec3(-.65, t_y, t_z));


    teeth[4] = new Polyg(.0625, 36, .27);
    teeth[4]->gen_vertices();
    teeth[4]->rotate(0, -23);
    teeth[4]->translate(glm::vec3(.65, t_y, t_z));

    teeth[5] = new Polyg(.0625, 36, .27);
    teeth[5]->gen_vertices();
    teeth[5]->rotate(0, -32);
    teeth[5]->translate(glm::vec3(.45, t_y, t_z));

    teeth[6] = new Polyg(.0625, 36, .27);
    teeth[6]->gen_vertices();
    teeth[6]->rotate(0, -22);
    teeth[6]->translate(glm::vec3(.31, t_y, t_z));

    teeth[7] = new Polyg(.06, 36, .28);
    teeth[7]->gen_vertices();
    teeth[7]->rotate(0, -29);
    teeth[7]->translate(glm::vec3(.79, t_y, t_z));

    teeth[8] = new Polyg(.06, 36, .28);
    teeth[8]->gen_vertices();
    teeth[8]->rotate(0, -31);
    teeth[8]->translate(glm::vec3(-.83, t_y, t_z));

    teeth[9] = new Polyg(.06, 36, .28);
    teeth[9]->gen_vertices();
    teeth[9]->rotate(0, 187);
    teeth[9]->translate(glm::vec3(-.6, t_y, t_z + .5));

    teeth[10] = new Polyg(.06, 36, .28);
    teeth[10]->gen_vertices();
    teeth[10]->rotate(0, 197);
    teeth[10]->translate(glm::vec3(-.4, t_y, t_z + .5));

    teeth[11] = new Polyg(.06, 36, .28);
    teeth[11]->gen_vertices();
    teeth[11]->rotate(0, 205);
    teeth[11]->translate(glm::vec3(-.32, t_y, t_z + .5));

    teeth[12] = new Polyg(.06, 36, .28);
    teeth[12]->gen_vertices();
    teeth[12]->rotate(0, 190);
    teeth[12]->translate(glm::vec3(-.20, t_y, t_z + .5));


    teeth[13] = new Polyg(.06, 36, .28);
    teeth[13]->gen_vertices();
    teeth[13]->rotate(0, 211);
    teeth[13]->translate(glm::vec3(-.02, t_y, t_z + .5));

    teeth[14] = new Polyg(.06, 36, .28);
    teeth[14]->gen_vertices();
    teeth[14]->rotate(0, 180);
    teeth[14]->translate(glm::vec3(.16, t_y, t_z + .5));

    teeth[15] = new Polyg(.06, 36, .28);
    teeth[15]->gen_vertices();
    teeth[15]->rotate(0, 187);
    teeth[15]->translate(glm::vec3(.27, t_y, t_z + .5));


    teeth[16] = new Polyg(.06, 36, .28);
    teeth[16]->gen_vertices();
    teeth[16]->rotate(0, 195);
    teeth[16]->translate(glm::vec3(.35, t_y, t_z + .5));

    teeth[17] = new Polyg(.06, 36, .28);
    teeth[17]->gen_vertices();
    teeth[17]->rotate(0, 175);
    teeth[17]->translate(glm::vec3(.56, t_y, t_z + .5));


    teeth[18] = new Polyg(.06, 36, .28);
    teeth[18]->gen_vertices();
    teeth[18]->rotate(0, 195);
    teeth[18]->translate(glm::vec3(.69, t_y, t_z + .5));

    teeth[19] = new Polyg(.06, 36, .28);
    teeth[19]->gen_vertices();
    teeth[19]->rotate(0, 175);
    teeth[19]->translate(glm::vec3(.85, t_y, t_z + .5));
    int cntr = 0;
    for (int i = 0; i < TEETH; i++) {
        cntr += teeth[i]->get_vertex_size();
    }
    vertex_size += cntr * sizeof(float);

    for (int i = 0; i < WING_COUNT; i++) {
        if (i < 2) {
            wings[i] = new Ellipse(2.5 - (5 * i), .5, .25, 2.5, .5, 2, 32);
            wings[i + 2] = new Ellipse(2.5 - (5 * i), 1.5, .25, 2.5, .5, 2, 32);
            wings[i + 2]->set_color(.25, 1, .75, .4, 1);
            wings[i + 2]->set_color(.5, 0, .5, .9, 0);
            wings[i + 2]->set_color(1, 1, .5, .9, 2);
        }
        wings[i]->gen_vertices();
        vertex_size += wings[i]->get_vertex_size() * sizeof(float);

    }

    wings[0]->rotate(2, 20);
    wings[1]->rotate(2, -20);
    wings[2]->rotate(2, -20);
    wings[3]->rotate(2, 20);
    wings[1]->translate(glm::vec3(0, 1.05, 0));
    wings[0]->translate(glm::vec3(0, 1.05, 0));

}

Dragonfly::~Dragonfly() {}

void Dragonfly::draw() {}

void Dragonfly::translate(glm::vec3 offset) {}

void Dragonfly::rotate(int axis, float angle) {}
