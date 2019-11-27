//
// Created by Dwight J. Browne on 11/27/19.
//

#ifndef TESTBED2_DRAGONFLY_H
#define TESTBED2_DRAGONFLY_H

#include "Color.h"
#include "primatives.h"
#include "Block.h"
#include "Cylinder.h"
#include "Sphere.h"
#include "box.h"
#include "ellipse.h"


class Dragonfly {
private:
    float *vertices{};
    int vertex_size;
    int vertex_count;
    unsigned int VAO;
    unsigned int VBO;

public:
    Dragonfly();

    ~Dragonfly();

    void draw();

    void rotate(int axis, float angle);

    void translate(glm::vec3 offset);

    float *get_vertices;

};

#endif //TESTBED2_DRAGONFLY_H
