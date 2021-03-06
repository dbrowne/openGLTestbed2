//
// Created by Dwight J. Browne on 11/20/19.
//
///////////////////////////////////////////////////////////////////////////////
// Sphere.h
// ========
// Sphere for OpenGL with (radius, sectors, stacks)
// The min number of sectors is 3 and The min number of stacks are 2.
//
//  AUTHOR: Song Ho Ahn (song.ahn@gmail.com)
// CREATED: 2017-11-01
// UPDATED: 2018-12-13
///////////////////////////////////////////////////////////////////////////////

#ifndef TESTBED2_SPHERE_H
#define TESTBED2_SPHERE_H

#include <vector>
#include "Color.h"
#include <glm/vec3.hpp>
class Sphere {
public:
    // Constants
    const int VERTEX_SIZE = 3;
    const int COLOR_SIZE = 4;
    const int TEXTURE_SIZE = 2;
    const int NORMAL_SIZE = 3;
    unsigned int sphere_vao;
    unsigned int sphere_vbo;
    int vertex_stride = VERTEX_SIZE + COLOR_SIZE + TEXTURE_SIZE + NORMAL_SIZE;
    bool first = true;

    // ctor/dtor

    Sphere(float radius = 1.0f, int sectorCount = 36, int stackCount = 18, bool ext = true);

    Sphere(float radius, int sectorCount, int stackCount, bool ext, Color **colors);

    ~Sphere() {}

    // getters/setters
    float getRadius() const { return radius; }

    int getSectorCount() const { return sectorCount; }

    int getStackCount() const { return stackCount; }

    void deletebuffers();

    void set(float radius, int sectorCount, int stackCount, bool smooth = true);

    void setRadius(float radius);

    void setSectorCount(int sectorCount);

    void setStackCount(int stackCount);

    void setSmooth(bool smooth);

    void setInterior();

    void translate(glm::vec3 offset);

    void rotate(int axis, float angle);
    // for vertex data
    unsigned int getVertexCount() const { return (unsigned int) vertices.size() / 3; }

    unsigned int getNormalCount() const { return (unsigned int) normals.size() / 3; }

    unsigned int getColorCount() const { return (unsigned int) colors.size() / 4; }

    unsigned int getTexCoordCount() const { return (unsigned int) texCoords.size() / 2; }

    unsigned int getIndexCount() const { return (unsigned int) indices.size(); }

    unsigned int getLineIndexCount() const { return (unsigned int) lineIndices.size(); }

    unsigned int getTriangleCount() const { return getIndexCount() / 3; }

    unsigned int getVertexSize() const { return (unsigned int) vertices.size() * sizeof(float); }

    unsigned int getNormalSize() const { return (unsigned int) normals.size() * sizeof(float); }

    unsigned int getTexCoordSize() const { return (unsigned int) texCoords.size() * sizeof(float); }

    unsigned int getIndexSize() const { return (unsigned int) indices.size() * sizeof(unsigned int); }

    unsigned int getLineIndexSize() const { return (unsigned int) lineIndices.size() * sizeof(unsigned int); }


    float *get_vertices();
    const float *getVertices() const { return vertices.data(); }

    const float *getNormals() const { return normals.data(); }

    const float *getTexCoords() const { return texCoords.data(); }

    const float *getColors() const { return colors.data(); }

    const unsigned int *getIndices() const { return indices.data(); }

    const unsigned int *getLineIndices() const { return lineIndices.data(); }

    // for interleaved vertices: V/N/T
    unsigned int getInterleavedVertexCount() const { return getVertexCount(); }    // # of vertices
    unsigned int getInterleavedVertexSize() const {
        return (unsigned int) interleavedVertices.size() * sizeof(float);
    }    // # of bytes
    int getInterleavedStride() const { return interleavedStride; }   //
    const float *getInterleavedVertices() const { return interleavedVertices.data(); }

    // draw in VertexArray modes[
    void draw(int useTex = 0, int tex_num = 1);                                  // draw surface
    void drawLines(const float lineColor[4]) const;     // draw lines only
    void drawWithLines(const float lineColor[4]); // draw surface and lines

    // debug
    void printSelf() const;

    void dumpInterleaved();

    float *outVertices{nullptr};
    int outVertices_count = 0;
    int outVertices_stride = VERTEX_SIZE + COLOR_SIZE + TEXTURE_SIZE + NORMAL_SIZE;
protected:

private:
    // member functions
    void updateRadius();

    void buildVerticesSmooth();

    void buildVerticesFlat();

    void buildInterleavedVertices();

    void clearArrays();

    void addVertex(float x, float y, float z);

    void addNormal(float x, float y, float z);

    void addTexCoord(float s, float t);

    void addColors(Color *c);

    void addIndices(unsigned int i1, unsigned int i2, unsigned int i3);

    bool exterior;    // exterior lighing or interior lighing

    std::vector<float> computeFaceNormal(float x1, float y1, float z1,
                                         float x2, float y2, float z2,
                                         float x3, float y3, float z3);

    // memeber vars
    float radius;
    int sectorCount;                        // longitude, # of slices
    int stackCount;                         // latitude, # of stacks
    bool smooth;
    Color *vertex_color[3];
    std::vector<float> vertices;
    std::vector<float> normals;
    std::vector<float> texCoords;
    std::vector<float> colors;
    std::vector<unsigned int> indices;
    std::vector<unsigned int> lineIndices;
    int vertex_size;

    // interleaved
    std::vector<float> interleavedVertices;
    int interleavedStride;                  // # of bytes to hop to the next vertex (should be 32 bytes)

};

#endif //TESTBED2_SPHERE_H
