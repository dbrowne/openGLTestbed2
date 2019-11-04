//
// Created by Dwight J. Browne on 11/3/19.
//

#ifndef TESTBED2_PRIMATIVES_H
#define TESTBED2_PRIMATIVES_H
#include<math.h>
#include <vector>

const double PI = 3.141596;
const int VERTEX_SIZE = 3;

class Circle
{
private:
    float radius;
    float *vertices;
    float point_count;


public:
    Circle();

    Circle(float radius, float point_count);

    ~Circle();

    void set_radius(float radius);
    void set_point_Count(float point_count);

    void gen_vertices();
    float *get_vertices();

};


#endif //TESTBED2_PRIMATIVES_H
