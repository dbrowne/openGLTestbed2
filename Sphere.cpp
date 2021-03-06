//
// Created by Dwight J. Browne on 11/20/19.
//
///////////////////////////////////////////////////////////////////////////////
// Sphere.cpp
// ==========
// Sphere for OpenGL with (radius, sectors, stacks)
// The min number of sectors is 3 and the min number of stacks are 2.
//
//  Based on CODE created by Song Ho Ahn (song.ahn@gmail.com)
// CREATED: 2017-11-01
// UPDATED: 2018-12-13
// MODIFIED By Dwight Browne to present vector array
///////////////////////////////////////////////////////////////////////////////

#ifdef _WIN32
#include <windows.h>    // include windows.h to avoid thousands of compile errors even though this class is not depending on Windows
#endif

#include <iostream>
#include <iomanip>
#include <cmath>
#include "glad.h"
#include "Sphere.h"
#include "extra_funcs.h"
#include "Prim_base.h"


// constants //////////////////////////////////////////////////////////////////
const int MIN_SECTOR_COUNT = 3;
const int MIN_STACK_COUNT = 2;


///////////////////////////////////////////////////////////////////////////////
// ctor
///////////////////////////////////////////////////////////////////////////////
Sphere::Sphere(float radius, int sectors, int stacks, bool ext) : interleavedStride(96) {
    smooth = false;
    exterior = ext;
    vertex_color[0] = new Color(.3, 1, .3, 1);
    vertex_color[1] = new Color(0, 1, 0, 1);
    vertex_color[2] = new Color(1, 1, .3, 1);

    set(radius, sectors, stacks, smooth);
}


Sphere::Sphere(float radius, int sectors, int stacks, bool ext, Color **colors) {
    smooth = false;
    exterior = ext;
    for (int i = 0; i < 3; i++) {
        vertex_color[i] = new Color(colors[i]->r, colors[i]->g, colors[i]->b, colors[i]->a);
    }
    set(radius, sectors, stacks, smooth);

}



///////////////////////////////////////////////////////////////////////////////
// setters
///////////////////////////////////////////////////////////////////////////////
void Sphere::set(float radius, int sectors, int stacks, bool smooth) {
    this->radius = radius;
    this->sectorCount = sectors;
    if (sectors < MIN_SECTOR_COUNT)
        this->sectorCount = MIN_SECTOR_COUNT;
    this->stackCount = stacks;
    if (sectors < MIN_STACK_COUNT)
        this->sectorCount = MIN_STACK_COUNT;
    this->smooth = smooth;


    buildVerticesFlat();
}


void Sphere::setRadius(float radius) {
    this->radius = radius;
    updateRadius();
}

void Sphere::setSectorCount(int sectors) {
    set(radius, sectors, stackCount, smooth);
}

void Sphere::setStackCount(int stacks) {
    set(radius, sectorCount, stacks, smooth);
}

void Sphere::setSmooth(bool smooth) {
    if (this->smooth == smooth)
        return;


    buildVerticesFlat();
}


///////////////////////////////////////////////////////////////////////////////
// print itself
///////////////////////////////////////////////////////////////////////////////
void Sphere::printSelf() const {
    std::cout << "===== Sphere =====\n"
            << "        Radius: " << radius << "\n"
            << "  Sector Count: " << sectorCount << "\n"
            << "   Stack Count: " << stackCount << "\n"
            << "Smooth Shading: " << (smooth ? "true" : "false") << "\n"
            << "Triangle Count: " << getTriangleCount() << "\n"
            << "   Index Count: " << getIndexCount() << "\n"
            << "  Vertex Count: " << getVertexCount() << "\n"
            << "  Normal Count: " << getNormalCount() << "\n"
            << "  colors Count: " << getColorCount() << "\n"
            << "TexCoord Count: " << getTexCoordCount() << std::endl;
}

///////////////////////////////////////////////////////////////////////////////
// Delete buffers
///////////////////////////////////////////////////////////////////////////////
void Sphere::deletebuffers() {
    glDeleteVertexArrays(1, &sphere_vao);
    glDeleteBuffers(1, &sphere_vbo);
}

///////////////////////////////////////////////////////////////////////////////
// draw a sphere in VertexArray mode
// OpenGL RC must be set before calling it
///////////////////////////////////////////////////////////////////////////////
void Sphere::draw(int useTex, int tex_num) {

    if (first) {
        glGenVertexArrays(1, &sphere_vao);
        glGenBuffers(1, &sphere_vbo);
        glBindVertexArray(sphere_vao);
        glBindBuffer(GL_ARRAY_BUFFER, sphere_vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(outVertices) * outVertices_count * outVertices_stride, outVertices,
                     GL_STATIC_DRAW);
        glCheckError();
        // position attribute
        glVertexAttribPointer(0, VERTEX_SIZE, GL_FLOAT, GL_FALSE,
                              (outVertices_stride) * sizeof(float),
                              (void *) 0);
        glEnableVertexAttribArray(0);
        glCheckError();
        //color attribute
        glVertexAttribPointer(1, COLOR_SIZE, GL_FLOAT, GL_FALSE,
                              (outVertices_stride) * sizeof(float),
                              (void *) (VERTEX_SIZE * sizeof(float)));
        glCheckError();
        glEnableVertexAttribArray(1);



        //texture attribute
        glVertexAttribPointer(2, TEXTURE_SIZE, GL_FLOAT, GL_FALSE,
                              (outVertices_stride) * sizeof(float),
                              (void *) ((VERTEX_SIZE + COLOR_SIZE) * sizeof(float)));
        glCheckError();
        if (useTex == 1) {
            glEnableVertexAttribArray(2);
        } else {
            glDisableVertexAttribArray(2);
        }
        //Normal attribute
        glVertexAttribPointer(3, NORMAL_SIZE, GL_FLOAT, GL_FALSE,
                              (outVertices_stride) * sizeof(float),
                              (void *) ((VERTEX_SIZE + COLOR_SIZE + TEXTURE_SIZE) * sizeof(float)));

        glCheckError();
        glEnableVertexAttribArray(3);
        glBindBuffer(GL_ARRAY_BUFFER, 0);


        first = false;
    }
    glBindVertexArray(sphere_vao);

    glCheckError();
    glDrawArrays(GL_TRIANGLES, 0, outVertices_count);
    glCheckError();

}

///////////////////////////////////////////////////////////////////////////////
// debug interleaved vertices
//
///////////////////////////////////////////////////////////////////////////////

void ::Sphere::dumpInterleaved() {
    std::size_t i;

    std::cout << " #:    vertex:\t\tcolor:\t\ttex:\t\tnorm \n";
    int offset = outVertices_stride;
    std::size_t count = interleavedVertices.size();
    std::cout << "# of interleavedVertices :" << interleavedVertices.size() << "\n";
    std::cout << "sizeof interleavedVertices :" << sizeof(interleavedVertices) << "sizeof Float " << sizeof(float)
              << "\n";
    for (i = 0; i < count; i += offset) {
        std::cout << "#" << i << " :";
        std::cout << interleavedVertices[i] << ", ";
        std::cout << interleavedVertices[i + 1] << ", ";
        std::cout << interleavedVertices[i + 2] << ", ";
        //color
        std::cout << interleavedVertices[i + 3] << ", ";
        std::cout << interleavedVertices[i + 4] << ", ";
        std::cout << interleavedVertices[i + 5] << ", ";
        std::cout << interleavedVertices[i + 6] << ", ";
        //texture
        std::cout << interleavedVertices[i + 7] << ", ";
        std::cout << interleavedVertices[i + 8] << ", ";
        //normals
        std::cout << interleavedVertices[i + 9] << ", ";
        std::cout << interleavedVertices[i + 10] << ", ";
        std::cout << interleavedVertices[i + 11] << "\n";


    }

}
///////////////////////////////////////////////////////////////////////////////
// draw lines only
// the caller must set the line width before call this
///////////////////////////////////////////////////////////////////////////////
void Sphere::drawLines(const float lineColor[4]) const {
    // set line colour
    glColor4fv(lineColor);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, lineColor);

    // draw lines with VA
    glDisable(GL_LIGHTING);
    glDisable(GL_TEXTURE_2D);
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, vertices.data());

    glDrawElements(GL_LINES, (unsigned int) lineIndices.size(), GL_UNSIGNED_INT, lineIndices.data());

    glDisableClientState(GL_VERTEX_ARRAY);
    glEnable(GL_LIGHTING);
    glEnable(GL_TEXTURE_2D);
}


///////////////////////////////////////////////////////////////////////////////
// draw a sphere surfaces and lines on top of it
// the caller must set the line width before call this
///////////////////////////////////////////////////////////////////////////////
void Sphere::drawWithLines(const float lineColor[4]) {
    glEnable(GL_POLYGON_OFFSET_FILL);
    glPolygonOffset(1.0, 1.0f); // move polygon backward
    this->draw();
    glDisable(GL_POLYGON_OFFSET_FILL);

    // draw lines with VA
    drawLines(lineColor);
}

///////////////////////////////////////////////////////////////////////////////
// set to interior lighting
///////////////////////////////////////////////////////////////////////////////
void Sphere::setInterior() {
    exterior = false;
}
///////////////////////////////////////////////////////////////////////////////
// update vertex positions only
///////////////////////////////////////////////////////////////////////////////
void Sphere::updateRadius() {
    float scale = sqrtf(
            radius * radius / (vertices[0] * vertices[0] + vertices[1] * vertices[1] + vertices[2] * vertices[2]));

    std::size_t i, j;
    std::size_t count = vertices.size();
    for (i = 0, j = 0; i < count; i += 3, j += 8) {
        vertices[i] *= scale;
        vertices[i + 1] *= scale;
        vertices[i + 2] *= scale;

        // for interleaved array
        interleavedVertices[j] *= scale;
        interleavedVertices[j + 1] *= scale;
        interleavedVertices[j + 2] *= scale;
    }
}


///////////////////////////////////////////////////////////////////////////////
// dealloc vectors
///////////////////////////////////////////////////////////////////////////////
void Sphere::clearArrays() {
    std::vector<float>().swap(vertices);
    std::vector<float>().swap(normals);
    std::vector<float>().swap(texCoords);
    std::vector<float>().swap(colors);
    std::vector<unsigned int>().swap(indices);
    std::vector<unsigned int>().swap(lineIndices);
}




///////////////////////////////////////////////////////////////////////////////
// generate vertices with flat shading
///////////////////////////////////////////////////////////////////////////////
void Sphere::buildVerticesFlat() {
    const float PI = 3.1415926f;
    // tmp vertex definition (x,y,z,s,t)
    struct Vertex {
        float x, y, z, s, t;
    };
    std::vector<Vertex> tmpVertices;

    float sectorStep = 2 * PI / sectorCount;
    float stackStep = PI / stackCount;
    float sectorAngle, stackAngle;

    // compute all vertices first, each vertex contains (x,y,z,s,t) except normal
    for (int i = 0; i <= stackCount; ++i) {
        stackAngle = PI / 2 - i * stackStep;        // starting from pi/2 to -pi/2
        float xy = radius * cosf(stackAngle);       // r * cos(u)
        float z = radius * sinf(stackAngle);        // r * sin(u)

        // add (sectorCount+1) vertices per stack
        // the first and last vertices have same position and normal, but different tex coords
        for (int j = 0; j <= sectorCount; ++j) {
            sectorAngle = j * sectorStep;           // starting from 0 to 2pi

            Vertex vertex;
            vertex.x = xy * cosf(sectorAngle);      // x = r * cos(u) * cos(v)
            vertex.y = xy * sinf(sectorAngle);      // y = r * cos(u) * sin(v)
            vertex.z = z;                           // z = r * sin(u)
            vertex.s = (float) j / sectorCount;        // s
            vertex.t = (float) i / stackCount;         // t
            tmpVertices.push_back(vertex);
        }
    }

    // clear memory of prev arrays
    clearArrays();

    Vertex v1, v2, v3, v4;                          // 4 vertex positions and tex coords
    std::vector<float> n;                           // 1 face normal

    int i, j, k, vi1, vi2;
    int index = 0;                                  // index for vertex
    for (i = 0; i < stackCount; ++i) {
        vi1 = i * (sectorCount + 1);                // index of tmpVertices
        vi2 = (i + 1) * (sectorCount + 1);

        for (j = 0; j < sectorCount; ++j, ++vi1, ++vi2) {
            // get 4 vertices per sector
            //  v1--v3
            //  |    |
            //  v2--v4
            v1 = tmpVertices[vi1];
            v2 = tmpVertices[vi2];
            v3 = tmpVertices[vi1 + 1];
            v4 = tmpVertices[vi2 + 1];

            // if 1st stack and last stack, store only 1 triangle per sector
            // otherwise, store 2 triangles (quad) per sector
            if (i == 0) // a triangle for first stack ==========================
            {
                // put a triangle
                addVertex(v1.x, v1.y, v1.z);
                addVertex(v2.x, v2.y, v2.z);
                addVertex(v4.x, v4.y, v4.z);
                addColors(vertex_color[0]);
                addColors(vertex_color[1]);
                addColors(vertex_color[2]);
//                addColors(color1);

                // put tex coords of triangle
                addTexCoord(v1.s, v1.t);
                addTexCoord(v2.s, v2.t);
                addTexCoord(v4.s, v4.t);

                // put normal
                n = computeFaceNormal(v1.x, v1.y, v1.z, v2.x, v2.y, v2.z, v4.x, v4.y, v4.z);
                for (k = 0; k < 3; ++k)  // same normals for 3 vertices
                {
                    if (exterior) {
                        addNormal(n[0], n[1], n[2]);
                    } else {
                        addNormal(-1.0 * n[0], -1.0 * n[1], -1.0 * n[2]);

                    }
                }

                // put indices of 1 triangle
                addIndices(index, index + 1, index + 2);

                // indices for line (first stack requires only vertical line)
                lineIndices.push_back(index);
                lineIndices.push_back(index + 1);

                index += 3;     // for next
            } else if (i == (stackCount - 1)) // a triangle for last stack =========
            {
                // put a triangle
                addVertex(v1.x, v1.y, v1.z);
                addVertex(v2.x, v2.y, v2.z);
                addVertex(v3.x, v3.y, v3.z);
                addColors(vertex_color[0]);
                addColors(vertex_color[1]);
                addColors(vertex_color[2]);

                // put tex coords of triangle
                addTexCoord(v1.s, v1.t);
                addTexCoord(v2.s, v2.t);
                addTexCoord(v3.s, v3.t);

                // put normal
                n = computeFaceNormal(v1.x, v1.y, v1.z, v2.x, v2.y, v2.z, v3.x, v3.y, v3.z);
                for (k = 0; k < 3; ++k)  // same normals for 3 vertices
                {
                    if (exterior) {
                        addNormal(n[0], n[1], n[2]);
                    } else {
                        addNormal(-1.0 * n[0], -1.0 * n[1], -1.0 * n[2]);
                    }
                }

                // put indices of 1 triangle
                addIndices(index, index + 1, index + 2);

                // indices for lines (last stack requires both vert/hori lines)
                lineIndices.push_back(index);
                lineIndices.push_back(index + 1);
                lineIndices.push_back(index);
                lineIndices.push_back(index + 2);

                index += 3;     // for next
            } else // 2 triangles for others ====================================
            {
                // put quad vertices: v1-v2-v3-v4
                addVertex(v1.x, v1.y, v1.z);
                addVertex(v2.x, v2.y, v2.z);
                addVertex(v4.x, v4.y, v4.z);

                addVertex(v4.x, v4.y, v4.z);
                addVertex(v3.x, v3.y, v3.z);
                addVertex(v1.x, v1.y, v1.z);

                addColors(vertex_color[0]);
                addColors(vertex_color[1]);
                addColors(vertex_color[2]);
                addColors(vertex_color[2]);
                addColors(vertex_color[1]);
                addColors(vertex_color[0]);

                // put tex coords of quad
                addTexCoord(v1.s, v1.t);
                addTexCoord(v2.s, v2.t);
                addTexCoord(v4.s, v4.t);

                addTexCoord(v4.s, v4.t);
                addTexCoord(v3.s, v3.t);
                addTexCoord(v1.s, v1.t);


                // put normal
                n = computeFaceNormal(v1.x, v1.y, v1.z, v2.x, v2.y, v2.z, v4.x, v4.y, v4.z);
                for (k = 0; k < 3; ++k)  // same normals for 4 vertices
                {
                    if (exterior) {
                        addNormal(n[0], n[1], n[2]);
                    } else {
                        addNormal(-1.0 * n[0], -1.0 * n[1], -1.0 * n[2]);

                    }
                }

                n = computeFaceNormal(v4.x, v4.y, v4.z, v3.x, v3.y, v3.z, v1.x, v1.y, v1.z);
                for (k = 0; k < 3; ++k)  // same normals for 4 vertices
                {
                    if (exterior) {
                        addNormal(n[0], n[1], n[2]);
                    } else {
                        addNormal(-1.0 * n[0], -1.0 * n[1], -1.0 * n[2]);

                    }
                }


                // put indices of quad (2 triangles)
                addIndices(index, index + 1, index + 2);
                addIndices(index + 2, index + 1, index + 3);

                // indices for lines
                lineIndices.push_back(index);
                lineIndices.push_back(index + 1);
                lineIndices.push_back(index);
                lineIndices.push_back(index + 2);

                index += 4;     // for next
            }
        }
    }

    // generate interleaved vertex array as well
    buildInterleavedVertices();
}


///////////////////////////////////////////////////////////////////////////////
// generate interleaved vertices: V/N/T
// stride must be 32 bytes
///////////////////////////////////////////////////////////////////////////////
void Sphere::buildInterleavedVertices() {
    std::vector<float>().swap(interleavedVertices);
    int yyy;
    std::size_t i, j, k;
    std::size_t count = vertices.size();
    for (i = 0, j = 0, k = 0; i < count; i += 3, j += 2, k += 4) {
        interleavedVertices.push_back(vertices[i]);
        interleavedVertices.push_back(vertices[i + 1]);
        interleavedVertices.push_back(vertices[i + 2]);
        interleavedVertices.push_back(colors[k]);
        interleavedVertices.push_back(colors[k + 1]);
        interleavedVertices.push_back(colors[k + 2]);
        interleavedVertices.push_back(colors[k + 3]);
        interleavedVertices.push_back(texCoords[j]);
        interleavedVertices.push_back(texCoords[j + 1]);
        interleavedVertices.push_back(normals[i]);
        interleavedVertices.push_back(normals[i + 1]);
        interleavedVertices.push_back(normals[i + 2]);
    }
    yyy = interleavedVertices.size();
    outVertices = (float *) malloc(yyy * sizeof(float));
    if (!outVertices) {
        std::cout << "failed malloc in " << __LINE__ << "\n";
        exit(-1);
    }
    outVertices_count = yyy / outVertices_stride;
    for (int i = 0; i < yyy; i++) {
        outVertices[i] = interleavedVertices[i];
    }
    vertex_size = yyy;

}


///////////////////////////////////////////////////////////////////////////////
// add single vertex to array
///////////////////////////////////////////////////////////////////////////////
void Sphere::addVertex(float x, float y, float z) {
    vertices.push_back(x);
    vertices.push_back(y);
    vertices.push_back(z);
}


///////////////////////////////////////////////////////////////////////////////
// add single normal to array
///////////////////////////////////////////////////////////////////////////////
void Sphere::addNormal(float nx, float ny, float nz) {
    normals.push_back(nx);
    normals.push_back(ny);
    normals.push_back(nz);
}


///////////////////////////////////////////////////////////////////////////////
// add single texture coord to array
///////////////////////////////////////////////////////////////////////////////
void Sphere::addTexCoord(float s, float t) {
    texCoords.push_back(s);
    texCoords.push_back(t);
}

///////////////////////////////////////////////////////////////////////////////
// add single Color to array
///////////////////////////////////////////////////////////////////////////////
void Sphere::addColors(Color *c) {
    colors.push_back(c->r);
    colors.push_back(c->g);
    colors.push_back(c->b);
    colors.push_back(c->a);
}

///////////////////////////////////////////////////////////////////////////////
// add 3 indices to array
///////////////////////////////////////////////////////////////////////////////
void Sphere::addIndices(unsigned int i1, unsigned int i2, unsigned int i3) {
    indices.push_back(i1);
    indices.push_back(i2);
    indices.push_back(i3);
}

float *Sphere::get_vertices() {
    return outVertices;
}
///////////////////////////////////////////////////////////////////////////////
// return face normal of a triangle v1-v2-v3
// if a triangle has no surface (normal length = 0), then return a zero vector
///////////////////////////////////////////////////////////////////////////////
std::vector<float> Sphere::computeFaceNormal(float x1, float y1, float z1,  // v1
                                             float x2, float y2, float z2,  // v2
                                             float x3, float y3, float z3)  // v3
{
    const float EPSILON = 0.000001f;

    std::vector<float> normal(3, 0.0f);     // default return value (0,0,0)
    float nx, ny, nz;

    // find 2 edge vectors: v1-v2, v1-v3
    float ex1 = x2 - x1;
    float ey1 = y2 - y1;
    float ez1 = z2 - z1;
    float ex2 = x3 - x1;
    float ey2 = y3 - y1;
    float ez2 = z3 - z1;

    // cross product: e1 x e2
    nx = ey1 * ez2 - ez1 * ey2;
    ny = ez1 * ex2 - ex1 * ez2;
    nz = ex1 * ey2 - ey1 * ex2;

    // normalize only if the length is > 0
    float length = sqrtf(nx * nx + ny * ny + nz * nz);
    if (length > EPSILON) {
        // normalize
        float lengthInv = 1.0f / length;
        normal[0] = nx * lengthInv;
        normal[1] = ny * lengthInv;
        normal[2] = nz * lengthInv;
    }

    return normal;
}


void Sphere::translate(glm::vec3 offset) {
    Extra::translate(offset, outVertices, VERTEX_SIZE + COLOR_SIZE + TEXTURE_SIZE,
                     vertex_stride, vertex_size);
}

void Sphere::rotate(int axis, float angle) {
    Extra::rotate(axis, angle, outVertices, VERTEX_SIZE + COLOR_SIZE + TEXTURE_SIZE,
                  vertex_stride, vertex_size);
}