//
// Created by Dwight J. Browne on 12/4/19.
//

#include "dflyGen.h"
#include "DflyPos.h"


Dfly::Dfly() {

}

Dfly::~Dfly() = default;

class Dragonfly **Dfly::genFlies(Shader *shader) {
    int xx;
    int yy;

    for (xx = 0; xx < MAX_FLIES; xx++) {
        posArr[xx] = new DflyPos;
        dfly[xx] = new Dragonfly(shader);
    }
    setPos(0, -4, 7, 5, 0, 0, 0, true, false);
    setPos(1, 3, -18, -7, 5, -4.5, -5, true, true);
    setPos(2, -5, 17, 1, 12, 5.5, 6, true, true);
    setPos(3, 8, -17, -4, -12, 5.5, -12, true, true);
    setPos(4, -6, -25, -2, 10, -5.5, 12, true, true);
    setPos(5, -3, 19, -4, 25, -25.5, -24, true, true);
    setPos(6, 5, -12, 3, -6, 45.5, 3, true, true);
    setPos(7, 7, 17, -6, -30, -37.5, 22, true, true);
    setPos(8, -3, 15, 3, 17, -10.5, 30, true, true);
    setPos(9, 8, -9, 3, 0, 15.5, -30, true, true);
    setPos(10, 12, -17, 4, -3, 12.5, 40, true, true);
    setPos(11, -6, 7, -2, -9, 33.5, 50, true, true);
    setPos(12, 6, 11, 5, -16, 12.5, -50, true, true);
    setPos(13, 15, -20, 2, -1, -12.5, 6, true, true);
    setPos(14, -5, -2, -2, 4, -5.5, -20, true, true);
    setPos(15, 5, 12, 2, 8, -15.5, -12, true, true);
    setPos(16, -9, -18, -1, 5, 17.5, -16, true, true);


    for (xx = 0; xx < MAX_FLIES; xx++) {
        if (posArr[xx]->have_angles == true) {
            for (yy = 0; yy < 3; yy++) {
                dfly[xx]->rotate(yy, posArr[xx]->angles[yy]);
            }
        }
        if (posArr[xx]->have_vec == true) {
            dfly[xx]->translate(posArr[xx]->position);
        }
    }
    for (xx = 0; xx < MAX_FLIES; xx++) {
        free(posArr[xx]);
    }
    return dfly;
}

int Dfly::getFlyCount() {
    return MAX_FLIES;
}

void Dfly::setPos(int index, float xa, float ya, float za, float x, float y, float z, bool hasa, bool hasc) {
    posArr[index]->have_angles = hasa;
    posArr[index]->have_vec = hasc;
    posArr[index]->angles[0] = xa;
    posArr[index]->angles[1] = ya;
    posArr[index]->angles[2] = za;
    posArr[index]->position[0] = x;
    posArr[index]->position[1] = y;
    posArr[index]->position[2] = z;
}
