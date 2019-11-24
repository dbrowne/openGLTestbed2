//
// Created by Dwight J. Browne on 11/15/19.
//

#include "Prim_base.h"

// this is based on Song Ho Ahn'  Sphere.cpp

void Extra::set_v(float *in, float *out) {
    for (int i = 0; i < 3; i++) {
        out[i] = in[i];
    }
}
void Extra::gen_normal3(int idx, int offset, float *v1, float *v2, float *v3, float *out) {
    const float EPSILON = 0.000001f;

    float nx, ny, nz;

    // find 2 edge vectors: v1-v2, v1-v3
    float ex1 = v2[0] - v1[0];
    float ey1 = v2[1] - v1[1];
    float ez1 = v2[2] - v1[2];
    float ex2 = v3[0] - v1[0];
    float ey2 = v3[1] - v1[1];
    float ez2 = v3[2] - v1[2];

    // cross product: e1 x e2
    nx = ey1 * ez2 - ez1 * ey2;
    ny = ez1 * ex2 - ex1 * ez2;
    nz = ex1 * ey2 - ey1 * ex2;

    // normalize only if the length is > 0
    float length = sqrtf(nx * nx + ny * ny + nz * nz);
    if (length > EPSILON) {
        // normalize
        float lengthInv = 1.0f / length;
        out[idx + offset] = nx * lengthInv;
        out[idx + offset + 1] = ny * lengthInv;
        out[idx + offset + 2] = nz * lengthInv;
    }
}

// This is based on http://www.lighthouse3d.com/opengl/terrain/index.php?normals
void Extra::gen_normal2(int idx, int offset, float *v1, float *v2, float *out) {
    float vx, vy, vz;
    float nvx, nvy, nvz;
    float i;
    vx = v1[1] * v2[2] - v1[2] * v2[1];
    vy = v1[2] * v2[0] - v1[0] * v2[2];
    vz = v1[0] * v2[1] - v1[1] * v2[0];
    i = sqrt(vx * vx + vy * vy + vz * vz);
    nvx = vx / i;
    nvy = vy / i;
    nvz = vz / i;
    out[idx + offset] = nvx;
    out[idx + offset + 1] = nvy;
    out[idx + offset + 2] = nvz;
}

float Extra::chk(float inp) {
    if (abs(inp) < 9.28108e-06) {
        return 0.0;
    } else {
        return inp;
    }

}