//
// Created by Dwight J. Browne on 11/27/19.
//

#include "Dragonfly.h"

Dragonfly::Dragonfly() {
    vertex_size = 0;

    Color *c[3];


    c[0] = new Color(0, 0, 1, 1);
    c[1] = new Color(0, 1, 1, 1);
    c[2] = new Color(1, 0, 0, 1);

    // HEAD
    head = new Sphere(1.5, 72, 72, true, c);
    head->translate(glm::vec3(0, 3.5, -.85));
    vertex_size += head->getInterleavedVertexSize();


    c[0]->r = 0;
    c[0]->g = 0;
    c[0]->b = 1;
    c[1]->r = 0.5;
    c[1]->g = 0.5;
    c[1]->b = 1;
    c[2]->r = .8;
    c[2]->g = .5;
    c[2]->b = 1;


    //TAIL SEGMENT


    for (int i = 0; i < tail_segment_count; i++) {
        tail_segments[i] = new Cylinder(1.25, 1, 36, 2, 0, 0, 0);
        tail_segments[i]->gen_vertices();
        vertex_size += tail_segments[i]->get_vertex_size() * sizeof(float);
        tail_segments[i]->rotate(0, 90);
        tail_segments[i]->translate(glm::vec3(0, -1 - i * 2, -.85));
    }

    ey1 = new Sphere(.5, 72, 18, true, c);
    vertex_size += ey1->getInterleavedVertexSize();
    ey2 = new Sphere(.5, 72, 18, true, c);
    vertex_size += ey2->getInterleavedVertexSize();

    ey1->rotate(0, 105);
    ey1->rotate(1, 15);
    ey1->translate(glm::vec3(1, 4, .45));

    ey2->rotate(0, 105);
    ey2->rotate(1, -15);
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



    torso = new Cylinder(1.5, 1.125, 36, 4, 0, 0, 0);
    torso->gen_vertices();
    vertex_size += torso->get_vertex_size() * sizeof(float);
    torso->rotate(0, 90.0);
    torso->translate(glm::vec3(0., 3., -.85));


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

void Dragonfly::draw() {
    int i;
    head->draw();
    for (i = 0; i < tail_segment_count; i++) {
        tail_segments[i]->draw();
    }
    ey1->draw();
    ey2->draw();
    for (i = 0; i < MOUTH_PIECES; i++) {
        mouth[i]->draw();
    }
    torso->draw();
    for (i = 0; i < TOOTH_COUNT; i++) {
        teeth[i]->draw();
    }

    for (i = 0; i < WING_COUNT; i++) {
        wings[i]->draw();
    }

}

//void Dragonfly::draw() {
//    if (first) {
//        build();
//
//
//        glGenVertexArrays(1, &VAO);
//        glGenBuffers(1, &VBO);
//        glBindVertexArray(VAO);
//        glBindBuffer(GL_ARRAY_BUFFER, VBO);
//        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices) * vertex_count * stride, vertices, GL_STATIC_DRAW);
//        glCheckError();
//        // position attribute
//        glVertexAttribPointer(0, VERTEX_SIZE, GL_FLOAT, GL_FALSE,
//                              (stride) * sizeof(float),
//                              (void *) 0);
//        glEnableVertexAttribArray(0);
//        glCheckError();
//        //color attribute
//        glVertexAttribPointer(1, COLOR_SIZE, GL_FLOAT, GL_FALSE,
//                              (stride) * sizeof(float),
//                              (void *) (VERTEX_SIZE * sizeof(float)));
//        glCheckError();
//        glEnableVertexAttribArray(1);
//        //texture attribute
//        glVertexAttribPointer(2, TEXTURE_SIZE, GL_FLOAT, GL_FALSE,
//                              (stride) * sizeof(float),
//                              (void *) ((VERTEX_SIZE + COLOR_SIZE) * sizeof(float)));
//        glCheckError();
//        glEnableVertexAttribArray(2);
//        //Normal attribute
//        glVertexAttribPointer(3, NORMAL_SIZE, GL_FLOAT, GL_FALSE,
//                              (stride) * sizeof(float),
//                              (void *) ((VERTEX_SIZE + COLOR_SIZE + TEXTURE_SIZE) * sizeof(float)));
//
//        glCheckError();
//        glEnableVertexAttribArray(3);
//        first = false;
//    }
//
//    glBindVertexArray(VAO);
//
//    glCheckError();
//    glDrawArrays(GL_TRIANGLES, 0, vertex_count);
//    glCheckError();
//
//}

//void Dragonfly::build() {
//    int curr_size = vertex_size;
//    int offset =0;
//    int sz =0;
//    int seg_size=0;
//    float *ptr;
//    vertices = (float *)malloc(vertex_size);
//    if(!vertices){
//        std::cout<<"Cannot malloc! "<<__LINE__<<"\n";
//        exit(-1);
//    }
//    // Head
//    ptr = head->get_vertices();
//    sz = head->getInterleavedVertexSize();
//    memcpy (&vertices[offset],ptr,sz);
//    vertex_count += head->outVertices_count;
//    offset +=sz;
//
//    for (int i = 0; i < 1; i++) {
//          sz= tail_segments[i]->get_vertex_size() * sizeof(float);
//          ptr = tail_segments[i]->get_vertices();
//          memcpy (&vertices[offset], ptr,sz);
//          vertex_count += tail_segments[i]->get_vertex_count();
//          offset +=sz;
//    }
//
//    translate(glm::vec3(2,3,3));
//
//}
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
    torso->translate(offset);
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
    torso->rotate(axis, angle);
    for (i = 0; i < TOOTH_COUNT; i++) {
        teeth[i]->rotate(axis, angle);
    }

    for (i = 0; i < WING_COUNT; i++) {
        wings[i]->rotate(axis, angle);
    }
}
