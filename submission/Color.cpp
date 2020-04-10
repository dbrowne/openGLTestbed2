//
// Created by Dwight J. Browne on 11/4/19.
//

#include "Color.h"

Color::Color() {
    r = 1.0;
    g = 1.0;
    b = 1.0;
    a = 1.0;
}


Color::Color(float r1, float g1, float b1, float a1) {
    r = r1;
    g = g1;
    b = b1;
    a = a1;
}

Color::~Color() = default;

