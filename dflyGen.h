//
// Created by Dwight J. Browne on 12/4/19.
//

#ifndef TESTBED2_DFLYGEN_H
#define TESTBED2_DFLYGEN_H

#include "Dragonfly.h"
#include "Shader.h"
#include "DflyPos.h"


class Dfly {
private:
    const static int MAX_FLIES = 28;
    Dragonfly *dfly[MAX_FLIES];
    bool Generated_flies = false;
    DflyPos *posArr[MAX_FLIES];


public:
    Dfly();

    ~Dfly();

    Dragonfly **genFlies(Shader *s);

    int getFlyCount();

    void setPos(int index, float xa, float ya, float za, float x, float y, float z, bool hasa, bool hasc);
};


#endif //TESTBED2_DFLYGEN_H
