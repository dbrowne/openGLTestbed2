//
// Created by Dwight J. Browne on 11/16/19.
//

#include "LightCube.h"

LightCube::LightCube() {}

LightCube::~LightCube() = default;

void LightCube::increment(int int_val) {}

void LightCube::gen_vertices() {}

bool LightCube::has_bottom() { return true; }

float *LightCube::get_vertices() {
    return vertices;
}

void LightCube::print_vertices() {}

void LightCube::dump_vertex(int offset) {}

unsigned int *LightCube::get_indices() {
    return nullptr;
}

int LightCube::get_vertex_size() {
    return VERTEX_SZ;
}


int LightCube::get_vertex_count() {
    return 36;
}