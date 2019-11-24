//
// Created by Dwight J. Browne on 11/15/19.
//

#ifndef TESTBED2_PRIM_BASE_H
#define TESTBED2_PRIM_BASE_H

#include <cmath>

namespace Extra {
    void gen_normal3(int idx, int offset, float *v1, float *v2, float *v3, float *out);

    void gen_normal2(int idx, int offset, float *v1, float *v2, float *out);

    void set_v(float *in, float *out);
    float chk(float inp);
}

#endif //TESTBED2_PRIM_BASE_H
