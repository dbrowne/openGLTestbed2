//
// Created by Dwight J. Browne on 11/6/19.
//

#ifndef TESTBED2_EXTRA_FUNCS_H
#define TESTBED2_EXTRA_FUNCS_H

#include <GLFW/glfw3.h>

#define glCheckError() glCheckError_(__FILE__, __LINE__)

GLenum glCheckError_(const char *file, int line);

#endif //TESTBED2_EXTRA_FUNCS_H
