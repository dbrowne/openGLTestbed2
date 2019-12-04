//
// Created by Dwight J. Browne on 11/27/19.
//

#include "Dragonfly.h"


Dragonfly::Dragonfly(Shader *shade) {
    vertex_size = 0;
    ss = shade;
    int i;
    Color *c[3];


    c[0] = new Color(0, 1, .1, 1);
    c[1] = new Color(0, .8, .2, 1);
    c[2] = new Color(.5, 0, 0.3, 1);

    // HEAD
    head = new Sphere(1.6, 36, 36, true, c);
    head->translate(glm::vec3(0, 3.5, -.85));
    vertex_size += head->getInterleavedVertexSize();





    //TAIL SEGMENT

    c[0]->r = .6;
    c[0]->g = .8;
    c[0]->b = 0;
    c[1]->r = 0.1;
    c[1]->g = 0.9;
    c[1]->b = 0;
    c[2]->r = .2;
    c[2]->g = 1;
    c[2]->b = .13;
    for (i = 0; i < tail_segment_count; i++) {
        if (i == tail_segment_count - 1) {
            tail_segments[i] = new Cylinder(0.15, .425, 48, .5, 0, 0, 0, c);
            c[0]->b = float(i) * (float(i) / 8. + c[2]->b);
            c[2]->b = float(i) * (float(i) / 8. + c[2]->b);
            tail_segments[i]->gen_vertices();
            vertex_size += tail_segments[i]->get_vertex_size() * sizeof(float);
            tail_segments[i]->rotate(0, 90);
            tail_segments[i]->translate(glm::vec3(0, -1 - i * 2, -.85));
        } else {
            tail_segments[i] = new Cylinder(0.425, .15, 48, 2, 0, 0, 0, c);
            c[2]->b = float(i) * (float(i) / 8. + c[2]->b);
            tail_segments[i]->gen_vertices();
            vertex_size += tail_segments[i]->get_vertex_size() * sizeof(float);
            tail_segments[i]->rotate(0, 90);
            tail_segments[i]->translate(glm::vec3(0, -1 - i * 2, -.85));
        }
    }

    c[0]->r = .6;
    c[0]->g = .8;
    c[0]->b = 0;
    c[1]->r = 0.1;
    c[1]->g = 0.9;
    c[1]->b = 0;
    c[2]->r = .2;
    c[2]->g = 1;
    c[2]->b = 1.0;


    c[0]->r = 0;
    c[0]->g = 0;
    c[0]->b = 1;
    c[1]->r = 0.5;
    c[1]->g = 0.5;
    c[1]->b = 1;
    c[2]->r = .8;
    c[2]->g = .5;
    c[2]->b = 1;

    ey1 = new Sphere(.5, 72, 18, true, c);
    vertex_size += ey1->getInterleavedVertexSize();
    ey2 = new Sphere(.5, 72, 18, true, c);
    vertex_size += ey2->getInterleavedVertexSize();

    ey1->rotate(0, 105);
    ey1->rotate(1, 45);
    ey1->translate(glm::vec3(1, 4, .45));

    ey2->rotate(0, 105);
    ey2->rotate(1, -45);
    ey2->translate(glm::vec3(-1, 4, .45));

    //mouth
    float y_off = 4.95;
    mouth[0] = new Box(90, 2, .25, .0625, 0, 0, 0);
    mouth[0]->gen_vertices();
    vertex_size += mouth[0]->get_vertex_size() * sizeof(float);
    mouth[0]->translate(glm::vec3(-1, y_off, -1.25));

    mouth[1] = new Box(90, 2, .25, .0625, 0, 0, 0);
    mouth[1]->gen_vertices();
    vertex_size += mouth[1]->get_vertex_size() * sizeof(float);
    mouth[1]->translate(glm::vec3(-1, y_off, -1.75));

    mouth[2] = new Box(90, .25, .0625, .5, 0, 0, 0);
    mouth[2]->gen_vertices();
    vertex_size += mouth[2]->get_vertex_size() * sizeof(float);
    mouth[2]->rotate(0, 180);
    mouth[2]->rotate(2, 90);
    mouth[2]->translate(glm::vec3(-1, y_off, -1.1875));

    mouth[3] = new Box(90, .25, .0625, .5625, 0, 0, 0);
    mouth[3]->gen_vertices();
    vertex_size += mouth[3]->get_vertex_size() * sizeof(float);
    mouth[3]->rotate(0, 180);
    mouth[3]->rotate(2, 90);
    mouth[3]->translate(glm::vec3(1., y_off, -1.1875));

    c[0]->r = 0;
    c[0]->g = 0;
    c[0]->b = 0;
    c[1]->r = 0;
    c[1]->g = 0;
    c[1]->b = 0;
    c[2]->r = 0;
    c[2]->g = 0;
    c[2]->b = 0;

    mouth[4] = new Box(90, 2, .5625, .005, 0, 0, 0, c);
    mouth[4]->gen_vertices();
    vertex_size += mouth[4]->get_vertex_size() * sizeof(float);
    mouth[4]->rotate(0, -90);
    mouth[4]->translate(glm::vec3(-1, y_off, -1.1875));

    //////////////////////////////////////////////////////////////////////


    c[0]->r = .3;
    c[0]->g = .4;
    c[0]->b = 0;
    c[1]->r = 0.1;
    c[1]->g = 0.45;
    c[1]->b = 0;
    c[2]->r = .1;
    c[2]->g = .5;
    c[2]->b = .07;

    torso[0] = new Cylinder(.75, 1.125, 36, 3, 0, 0, 0, c);
    torso[0]->gen_vertices();
    vertex_size += torso[0]->get_vertex_size() * sizeof(float);
    torso[0]->rotate(0, 90.0);
    torso[0]->translate(glm::vec3(0., 3., -.85));

    torso[1] = new Cylinder(.45, .749, 36, 1, 0, 0, 0, c);
    torso[1]->gen_vertices();
    vertex_size += torso[1]->get_vertex_size() * sizeof(float);
    torso[1]->rotate(0, 90.0);
    torso[1]->translate(glm::vec3(0., 0., -.85));

    c[0]->r = .15;
    c[0]->g = .2;
    c[0]->b = 0;
    c[1]->r = 0.05;
    c[1]->g = 0.23;
    c[1]->b = 0;
    c[2]->r = .05;
    c[2]->g = .25;
    c[2]->b = .03;


    torso[2] = new Cylinder(.195, .45, 36, .5, 0, 0, 0, c);
    torso[2]->gen_vertices();
    vertex_size += torso[2]->get_vertex_size() * sizeof(float);
    torso[2]->rotate(0, 90.0);
    torso[2]->translate(glm::vec3(0., -1., -.85));


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
    for (int i = 0; i < TOOTH_COUNT; i++) {
        cntr += teeth[i]->get_vertex_size();
    }
    vertex_size += cntr * sizeof(float);

    for (int i = 0; i < WING_COUNT; i++) {
        if (i < 2) {
            wings[i] = new Ellipse(3.75 - (5 * i), .5, -.155 - i * .002, 4.05, .5, 2, 32);
            wings[i + 2] = new Ellipse(3.75 - (5 * i), 1.5, -.156 - i * .002, 4.05, .5, 2, 32);
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

void Dragonfly::draw() {
    int i;
    head->draw();
    for (i = 0; i < tail_segment_count; i++) {
        tail_segments[i]->draw();
    }
    ss->setInt("useTex", 1);
    ey1->draw(1);
    ey2->draw(1);
    ss->setInt("useTex", 0);
    for (i = 0; i < MOUTH_PIECES; i++) {
        mouth[i]->draw();
    }
    for (i = 0; i < TORSO_COUNT; i++) {
        torso[i]->draw();
    }
    for (i = 0; i < TOOTH_COUNT; i++) {
        teeth[i]->draw();
    }

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    for (i = 0; i < WING_COUNT; i++) {
        wings[i]->draw();
    }
    glDisable(GL_BLEND);

}


void Dragonfly::translate(glm::vec3 offset) {
    int i;
    head->translate(offset);
    for (i = 0; i < tail_segment_count; i++) {
        tail_segments[i]->translate(offset);
    }
    ey1->translate(offset);
    ey2->translate(offset);
    for (i = 0; i < MOUTH_PIECES; i++) {
        mouth[i]->translate(offset);
    }
    for (i = 0; i < TORSO_COUNT; i++) {
        torso[i]->translate(offset);
    }
    for (i = 0; i < TOOTH_COUNT; i++) {
        teeth[i]->translate(offset);
    }

    for (i = 0; i < WING_COUNT; i++) {
        wings[i]->translate(offset);
    }

}

void Dragonfly::rotate(int axis, float angle) {
    int i;
    head->rotate(axis, angle);
    for (i = 0; i < tail_segment_count; i++) {
        tail_segments[i]->rotate(axis, angle);
    }
    ey1->rotate(axis, angle);
    ey2->rotate(axis, angle);
    for (i = 0; i < MOUTH_PIECES; i++) {
        mouth[i]->rotate(axis, angle);
    }
    for (i = 0; i < TORSO_COUNT; i++) {
        torso[i]->rotate(axis, angle);
    }
    for (i = 0; i < TOOTH_COUNT; i++) {
        teeth[i]->rotate(axis, angle);
    }

    for (i = 0; i < WING_COUNT; i++) {
        wings[i]->rotate(axis, angle);
    }
}


void Dragonfly::deletebuffers() {
    int i;
    head->deletebuffers();
    for (i = 0; i < tail_segment_count; i++) {
        tail_segments[i]->deletebuffers();
    }
    ey1->deletebuffers();
    ey2->deletebuffers();
    for (i = 0; i < MOUTH_PIECES; i++) {
        mouth[i]->deletebuffers();
    }
    for (i = 0; i < TORSO_COUNT; i++) {
        torso[i]->deletebuffers();
    }
    for (i = 0; i < TOOTH_COUNT; i++) {
        teeth[i]->deletebuffers();
    }

    for (i = 0; i < WING_COUNT; i++) {
        wings[i]->deletebuffers();
    }
}