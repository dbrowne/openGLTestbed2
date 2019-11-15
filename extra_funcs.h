//
// Created by Dwight J. Browne on 11/6/19.
//

#ifndef TESTBED2_EXTRA_FUNCS_H
#define TESTBED2_EXTRA_FUNCS_H

#include <GLFW/glfw3.h>
#include <cmath>
#include <iostream>
#define glCheckError() glCheckError_(__FILE__, __LINE__)

GLenum glCheckError_(const char *file, int line);

const int MAX_COORDS = 3;


// this is based on Song Ho Ahn'  Sphere.cpp
//float *gen_normal(float *v1, float *v2, float *v3)
//{
//    const float EPSILON = 0.000001f;
//    float *normal = nullptr;
//
//    normal = (float *) malloc(MAX_COORDS* sizeof(float));
//    if (!normal){
//        std::cout << "gen_normal: Malloc failed. Cannot allocate indices\n";
//        exit(-1);
//    }
//
//    float nx, ny, nz;
//
//    // find 2 edge vectors: v1-v2, v1-v3
//    float ex1 = v2[0] - v1[0];
//    float ey1 = v2[1] - v1[1];
//    float ez1 = v2[2] - v1[2];
//    float ex2 = v3[0] - v1[0];
//    float ey2 = v3[1] - v1[2];
//    float ez2 = v3[2] - v1[2];
//
//    // cross product: e1 x e2
//    nx = ey1 * ez2 - ez1 * ey2;
//    ny = ez1 * ex2 - ex1 * ez2;
//    nz = ex1 * ey2 - ey1 * ex2;
//
//    // normalize only if the length is > 0
//    float length = sqrtf(nx * nx + ny * ny + nz * nz);
//    if(length > EPSILON)
//    {
//        // normalize
//        float lengthInv = 1.0f / length;
//        normal[0] = nx * lengthInv;
//        normal[1] = ny * lengthInv;
//        normal[2] = nz * lengthInv;
//    }
//
//    return normal;
//}
//


#endif //TESTBED2_EXTRA_FUNCS_H
