//
// Created by Dwight J. Browne on 11/15/19.
//

#ifndef TESTBED2_PRIM_BASE_H
#define TESTBED2_PRIM_BASE_H

#include <cmath>
#include <glm/vec3.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/string_cast.hpp>

namespace Extra {
    void gen_normal3(int idx, int offset, float *v1, float *v2, float *v3, float *out);

    void gen_normal2(int idx, int offset, float *v1, float *v2, float *out);

    void set_v(float *in, float *out);
    float chk(float inp);

    void rotate(int axis, float angle, float *verts, int offset2, int stride, int vert_size);

    void translate(glm::vec3 tr, float *verts, int offset2, int stride, int vert_size);
}

#endif //TESTBED2_PRIM_BASE_H
