//
// Created by Dwight J. Browne on 12/4/19.
//

#ifndef TESTBED2_DFLYPOS_H
#define TESTBED2_DFLYPOS_H

#include <glm/glm.hpp>

class DflyPos {
public:
    bool have_angles = true;
    float angles[3];
    bool have_vec = true;
    glm::vec3 position;
};


#endif //TESTBED2_DFLYPOS_H
