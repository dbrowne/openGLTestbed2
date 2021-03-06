//
// Created by Dwight J. Browne on 11/27/19.
//

#ifndef TESTBED2_DRAGONFLY_H
#define TESTBED2_DRAGONFLY_H

#include "Color.h"
#include "primatives.h"
#include "Cylinder.h"
#include "Sphere.h"
#include "box.h"
#include "ellipse.h"
#include "Shader.h"
#include <cmath>
#include <glm/vec3.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "DflyPos.h"

class Dragonfly {
private:
    float *vertices{};
    int vertex_size = 0;
    int vertex_count = 0;
    unsigned int VAO;
    unsigned int VBO;
    bool first = true;
    static const int MOUTH_PIECES = 5;
    void build();
    static const int TORSO_COUNT = 3;

    static const int TOOTH_COUNT = 20;
    static const int WING_COUNT = 4;
    Sphere *head;
    const int VERTEX_SIZE = 3;
    const int COLOR_SIZE = 4;
    const int TEXTURE_SIZE = 2;
    const int NORMAL_SIZE = 3;
    int stride = VERTEX_SIZE + COLOR_SIZE + TEXTURE_SIZE + NORMAL_SIZE;
    static const int tail_segment_count = 8;
    Cylinder *tail_segments[tail_segment_count];
    Sphere *ey1;
    Sphere *ey2;
    Box *mouth[MOUTH_PIECES];
    Cylinder *torso[TORSO_COUNT];
    Polyg *teeth[TOOTH_COUNT];
    Ellipse *wings[WING_COUNT];
    Shader *ss;

    int wing_off = 1;
    glm::mat4 Model45p;
    glm::mat4 Model45m;
    DflyPos *dp;


public:
    Dragonfly(Shader *shade);

    Dragonfly();

    ~Dragonfly();

    void draw(glm::mat4 matty, float yaw, float pitch, int move, float angle);

    void deletebuffers();
    void rotate(int axis, float angle);

    void translate(glm::vec3 offset);

    float *get_vertices;

};

#endif //TESTBED2_DRAGONFLY_H
