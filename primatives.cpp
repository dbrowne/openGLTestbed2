//
// Created by Dwight J. Browne on 11/3/19.
//

#include "primatives.h"
#include <iostream>
#include "Color.h"
#include "Prim_base.h"
#include "extra_funcs.h"

Axes::Axes(float ax_len) {

    symmetric = 0;
    point_count = 3;
    axis_color[0] = Color(1.0, 0.0, 0.0, 1.0);
    axis_color[1] = Color(0.0, 1.0, 0.0, 1.0);
    axis_color[2] = Color(0.0, 0.0, 1.0, 1.0);
    axes[0] = ax_len;
    axes[1] = ax_len;
    axes[2] = ax_len;
    vertex_size = 0;


}

void Axes::set_symmetric(int sym) {
    symmetric = 1;
}

float *::Axes::get_vertices() {
    return vertices;
}

unsigned int Axes::get_vertex_count() {
    return vertex_count;
}

int Axes::get_vertex_size() {
    return vertex_size;
}

void Axes::gen_vertices() {
    int offset;
    int sz;
    int cnt = 0;
    float start = 0.0;
    offset = VERTEX_SIZE + COLOR_SIZE + TEXTURE_SIZE + NORMAL_SIZE;
    sz = offset * point_count * 2;
    vertices = (float *) malloc(sz * sizeof(float));
    if (!vertices) {
        std::cout << "Polyg: Malloc failed. cannot allocate vertices\n";
        exit(-1);
    }

    for (int i = 0; i < sz; i++) {
        vertices[i] = 0.0;
    }

    if (symmetric == 1) {
        start = -1.0;
    }
    for (int i = 0; i < 3; i++) {
        vertices[cnt + i] = start * axes[i];
        vertices[cnt + VERTEX_SIZE] = axis_color[i].r;
        vertices[cnt + VERTEX_SIZE + 1] = axis_color[i].g;
        vertices[cnt + VERTEX_SIZE + 2] = axis_color[i].b;
        vertices[cnt + VERTEX_SIZE + 3] = axis_color[i].a;
        cnt += offset;
        vertices[cnt + i] = axes[i];
        vertices[cnt + VERTEX_SIZE] = axis_color[i].r;
        vertices[cnt + VERTEX_SIZE + 1] = axis_color[i].g;
        vertices[cnt + VERTEX_SIZE + 2] = axis_color[i].b;
        vertices[cnt + VERTEX_SIZE + 3] = axis_color[i].a;
        cnt += offset;
    }
    vertex_size = offset * vertex_count;
}

void Axes::draw() {
    if (first) {
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
        glBindVertexArray(VAO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices) * vertex_size, vertices, GL_STATIC_DRAW);
        // Position attribute
        glVertexAttribPointer(0, VERTEX_SIZE, GL_FLOAT, GL_FALSE,
                              (VERTEX_SIZE + COLOR_SIZE + TEXTURE_SIZE) * sizeof(float), (void *) 0);
        glCheckError();

        //color attribute
        glVertexAttribPointer(1, COLOR_SIZE, GL_FLOAT, GL_FALSE,
                              (VERTEX_SIZE + COLOR_SIZE + TEXTURE_SIZE) * sizeof(float),
                              (void *) (VERTEX_SIZE * sizeof(float)));
        glCheckError();
        glEnableVertexAttribArray(1);
        glEnableVertexAttribArray(0);
        first = false;
    }

    glBindVertexArray(VAO);
    glDrawArrays(GL_LINES, 0, vertex_count);


}


void Axes::print_vertices() {
    int cnt = 0;
    int sz = VERTEX_SIZE + COLOR_SIZE + TEXTURE_SIZE;
    for (unsigned int i = 0; i < vertex_count; i++) {
        prt_ax(cnt, sz);
        cnt += 7;
    }
}

void Axes::prt_ax(int offst, int sz) {

    for (int j = 0; j < sz; j++) {
        std::cout << vertices[offst + j] << ",";
    }
    std::cout << "\n";
}

Axes::~Axes() = default;

Polyg::Polyg() {
    radius = 1.0;
    point_count = 16;
    coord[0] = 0.0;
    coord[1] = 0.0;
    coord[2] = 0.0;
    height = 0.0;
    color[0] = new Color(1.0, 0.0, 0.0, 1.0);
    color[1] = new Color(0.0, 1.0, 0.0, 1.0);
    color[2] = new Color(0.0, 0.0, 1.0, 1.0);
}

Polyg::Polyg(float rad, float pc) {
    radius = rad;
    point_count = pc;
    coord[0] = 0.0;
    coord[1] = 0.0;
    coord[2] = 0.0;
    height = 0.0;
    color[0] = new Color(1.0, 0.0, 0.0, 1.0);
    color[1] = new Color(0.0, 1.0, 0.0, 1.0);
    color[2] = new Color(0.0, 0.0, 1.0, 1.0);

}


Polyg::Polyg(float rad, float pc, float h) {     // make them different default colors for testing
    radius = rad;
    point_count = pc;
    coord[0] = 0.0;
    coord[1] = 0.0;
    coord[2] = 0.0;
    height = h;
    color[0] = new Color(1.0, 0.0, 0.0, 1.0);
    color[1] = new Color(1.0, 1.0, 0.0, 1.0);
    color[2] = new Color(1.0, 1.0, 1.0, 1.0);

}
Polyg::Polyg(float rad, float pc, const Color c1) {
    radius = rad;
    point_count = pc;
    coord[0] = 0.0;
    coord[1] = 0.0;
    coord[2] = 0.0;
    height = 0.0;
    color[0] = new Color(c1.r, c1.g, c1.b, c1.a);
    color[1] = new Color(c1.r, c1.g, c1.b, c1.a);
    color[2] = new Color(c1.r, c1.g, c1.b, c1.a);

}

Polyg::Polyg(float rad, float pc, Color c1, float h) {
    radius = rad;
    point_count = pc;
    height = h;
    coord[0] = 0.0;
    coord[1] = 0.0;
    coord[2] = 0.0;
    color[0] = new Color(c1.r, c1.g, c1.b, c1.a);
    color[1] = new Color(c1.r, c1.g, c1.b, c1.a);
    color[2] = new Color(c1.r, c1.g, c1.b, c1.a);
}


Polyg::~Polyg() = default;

void Polyg::set_point_Count(float pc) {
    point_count = pc;
}

void Polyg::set_radius(float rad) {
    radius = rad;
}

Polyg::Polyg(float rad, float pc, float x, float y, float z, float h) {
    radius = rad;
    point_count = pc;
    height = h;
    coord[0] = x;
    coord[1] = y;
    coord[2] = z;
    height = h;
    color[0] = new Color(1.0, 0.0, 0.0, 1.0);
    color[1] = new Color(1.0, 1.0, 0.0, 1.0);
    color[2] = new Color(0.0, 0.0, 1.0, 1.0);


}


void ::Polyg::gen_vertices() {
    int sz;
    int cntr;
    float theta = 0;
    float x, y, z;
    float incr;
    int offset = 0;
    int idx = 0;
    int index_cntr = 0;
    int index_pos = 0;
    int bot_offset = 0;
    int idx_offset = 0;
    float v1[3], v2[3], v3[3];
    float v1a[3], v2a[3], v3a[3];
    int v1_idx = 0;
    int v2_idx = 0;
    int v3_idx = 0;
    z = 0;

    offset = VERTEX_SIZE + COLOR_SIZE + TEXTURE_SIZE + NORMAL_SIZE;
    sz = offset * point_count * 3;
    vertex_count = 3 * point_count;
    if (height != 0) {
        bot_offset = sz;
        sz = sz * 2;
        vertex_count = 6 * point_count;
        idx_offset = 3 * point_count;
        bottom = true;
    } else {
        vertex_count = 3 * point_count;
        bottom = false;
    }

    vertices = (float *) malloc(sz * sizeof(float));
    if (!vertices) {
        std::cout << "Polyg: Malloc failed. cannot allocate vertices\n";
        exit(-1);
    }
    vertex_size = sz;

    index_size = 3 * vertex_count;
    indices = (unsigned int *) malloc(index_size * sizeof(unsigned int));
    if (!indices) {
        std::cout << "Polyg: Malloc failed. Cannot allocate indices\n";
        exit(-1);
    }

    for (int i = 0; i < sz; i++)
        vertices[i] = -1;


    incr = 2 * PI / point_count;
    cntr = 0;

    while (cntr < 2 * point_count) {
        if (cntr % 2 == 0) {
            if (theta > 0) {
                theta -= incr;
            }
            x = Extra::chk(radius * cos(theta) + coord[0]);
            y = Extra::chk(radius * sin(theta) + coord[1]);

            set_vertex(idx, coord[0], coord[1], coord[2] + height);
            set_vertex_color(idx, 0);
            set_tex_pos(idx, 0.0, 0.0);
            v1[0] = coord[0];
            v1[1] = coord[1];
            v1[2] = coord[2] + height;

            v1_idx = idx;
            if (height != 0) {
                set_vertex(idx + bot_offset, coord[0], coord[1], coord[2]);
                set_vertex_color(idx + bot_offset, 0);
                set_tex_pos(idx + bot_offset, 0.0, 0.0);
                v1a[0] = coord[0];
                v1a[1] = coord[1];
                v1a[2] = coord[2];

                indices[index_pos + idx_offset] = point_count + 1;
            }
            indices[index_pos++] = 0;
            idx += offset;

            set_vertex(idx, x, y, coord[2]);
            set_vertex_color(idx, 1);
            set_tex_pos(idx, 1, 1);
            v2_idx = idx;
            v2[0] = x;
            v2[1] = y;
            v2[2] = coord[2];
            index_cntr++;
            if (height != 0) {
                set_vertex(idx + bot_offset, x, y, coord[2]);
                set_vertex_color(idx + bot_offset, 1);
                set_tex_pos(idx + bot_offset, 1, 1);
                indices[index_pos + idx_offset] = index_cntr;
                v2a[0] = x;
                v2a[1] = y;
                v2a[2] = coord[2];
            }

            indices[index_pos++] = index_cntr;
        } else {
            x = Extra::chk(radius * cos(theta) + coord[0]);
            y = Extra::chk(radius * sin(theta) + coord[1]);
            set_vertex(idx, x, y, coord[2]);
            set_vertex_color(idx, 2);
            set_tex_pos(idx, 1, 0);
            v3_idx = idx;
            v3[0] = x;
            v3[1] = y;
            v3[2] = z;

            if (height != 0) {
                set_vertex(idx + bot_offset, x, y, coord[2]);
                set_vertex_color(idx + bot_offset, 2);
                set_tex_pos(idx + bot_offset, 1, 1);
                indices[index_pos + idx_offset] = index_cntr + 1;
                v3a[0] = x;
                v3a[1] = y;
                v3a[2] = coord[2];
            }

            Extra::gen_normal3(v1_idx, 9, v2, v3, v1, vertices);
            Extra::gen_normal3(v2_idx, 9, v3, v1, v2, vertices);
            Extra::gen_normal3(v3_idx, 9, v1, v2, v3, vertices);

            if (height != 0) {
                Extra::gen_normal3(v1_idx + bot_offset, 9, v1a, v3a, v2a, vertices);
                Extra::gen_normal3(v2_idx + bot_offset, 9, v3a, v2a, v1a, vertices);
                Extra::gen_normal3(v3_idx + bot_offset, 9, v2a, v1a, v3a, vertices);

            }

            indices[index_pos++] = index_cntr + 1;
        }
        idx += offset;
        cntr++;

        theta += incr;

    }
    indices[index_pos - 1] = 1;

    if (height > 0) {
        indices[index_size - 1] = 1;
    }
}


float *::Polyg::get_vertices() {
    return vertices;
}

unsigned int *::Polyg::get_indices() {
    return indices;
}

int Polyg::get_index_size() {
    return index_size;
}

void Polyg::set_vertex(int idx, float x1, float y1, float z1) {
    vertices[idx] = x1;
    vertices[idx + 1] = y1;
    vertices[idx + 2] = z1;
}

void Polyg::set_vertex_color(int idx, int vtx) {
    vertices[idx + 3] = color[vtx]->r;
    vertices[idx + 4] = color[vtx]->g;
    vertices[idx + 5] = color[vtx]->b;
    vertices[idx + 6] = color[vtx]->a;
}

void Polyg::set_tex_pos(int idx, float x, float y) {
    vertices[idx + 7] = x;
    vertices[idx + 8] = y;
}
void Polyg::set_alpha(float a) {
    for (int i = 0; i < 3; i++) {
        color[i]->a = a;
    }
}

void Polyg::set_alpha(int v, float a) {
    color[v]->a = a;
}

void Polyg::set_color(Color c) {
    for (int i = 0; i < 3; i++) {
        color[i]->r = c.r;
        color[i]->g = c.g;
        color[i]->b = c.b;
        color[i]->a = c.a;
    }
}

void Polyg::set_color(int v, Color c) {
    color[v]->r = c.r;
    color[v]->g = c.g;
    color[v]->b = c.b;
    color[v]->a = c.a;
}

void Polyg::set_color(Color c0, Color c1, Color c2) {
    color[0]->r = c0.r;
    color[0]->g = c0.g;
    color[0]->b = c0.b;
    color[0]->a = c0.a;

    color[1]->r = c1.r;
    color[1]->g = c1.g;
    color[1]->b = c1.b;
    color[1]->a = c1.a;

    color[2]->r = c2.r;
    color[2]->g = c2.g;
    color[2]->b = c2.b;
    color[2]->a = c2.a;

}


void Polyg::print_vertices() {
    std::cout << " #:    vertex:\t\tcolor:\t\ttex \t\tNormal\n";
    int offset = VERTEX_SIZE + COLOR_SIZE + TEXTURE_SIZE + NORMAL_SIZE;
    int cntr = 0;
    int vtx_cnt = 0;
    int pc = 0;
    if (height != 0) {
        pc = 2 * point_count;
    } else {
        pc = point_count;
    }

    for (int i = 0; i < pc; i++) {
        std::cout << vtx_cnt++ << ":  ";
        dump_vertex(cntr);
        cntr += offset;
        std::cout << vtx_cnt++ << ":  ";
        dump_vertex(cntr);
        std::cout << vtx_cnt++ << ":  ";
        cntr += offset;
        dump_vertex(cntr);
        std::cout << "\n";

        cntr += offset;

    }
}

void Polyg::dump_vertex(int offset) {
    for (int j = 0; j < 3; j++) {
        std::cout << vertices[offset + j] << ", ";
    }

    std::cout << ":\t\t ";
    for (int j = 3; j <= 6; j++) {
        std::cout << vertices[offset + j] << ", ";
    }
    std::cout << ":\t\t";
    for (int j = 7; j <= 8; j++) {
        std::cout << vertices[offset + j] << ", ";
    }
    std::cout << ":\t\t";
    for (int j = 9; j <= 11; j++) {
        std::cout << vertices[offset + j] << ", ";
    }
    std::cout << "\n";
}

void Polyg::print_indices() {
    int offset = 0;
    for (int i = 0; i < vertex_count; i++) {
        std::cout << indices[offset] << ", " << indices[offset + 1] << ", " << indices[offset + 2] << "\n";
        offset += 3;
        if ((i + 1) % 3 == 0 && i != 0) {
            std::cout << "\n";
        }
    }
    std::cout << "\n";
}

void Polyg::set_index(int idx, int pos) {
    indices[idx] = pos;
}

void Polyg::set_height(float h) {
    height = h;
}

int Polyg::get_vertex_size() {
    return vertex_size;
}

int Polyg::get_vertex_count() {
    return vertex_count;
}

bool Polyg::has_bottom() {
    return bottom;
}

void Polyg::increment(int int_val) {}

void Polyg::rotate(int axis, float angle) {
    Extra::rotate(axis, angle, vertices,
                  VERTEX_SIZE + COLOR_SIZE + TEXTURE_SIZE, vertex_stride, vertex_size);
}

void Polyg::translate(glm::vec3 offset) {
    Extra::translate(offset, vertices, VERTEX_SIZE + COLOR_SIZE + TEXTURE_SIZE,
                     vertex_stride, vertex_size);
}

void Polyg::draw() {
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices) * vertex_count * vertex_stride, vertices,
                 GL_STATIC_DRAW);
    glCheckError();
    // position attribute
    glVertexAttribPointer(0, VERTEX_SIZE, GL_FLOAT, GL_FALSE,
                          (vertex_stride) * sizeof(float),
                          (void *) 0);
    glEnableVertexAttribArray(0);
    glCheckError();
    //color attribute
    glVertexAttribPointer(1, COLOR_SIZE, GL_FLOAT, GL_FALSE,
                          (vertex_stride) * sizeof(float),
                          (void *) (VERTEX_SIZE * sizeof(float)));
    glCheckError();
    glEnableVertexAttribArray(1);



    //texture attribute
    glVertexAttribPointer(2, TEXTURE_SIZE, GL_FLOAT, GL_FALSE,
                          (vertex_stride) * sizeof(float),
                          (void *) ((VERTEX_SIZE + COLOR_SIZE) * sizeof(float)));
    glCheckError();
    glEnableVertexAttribArray(3);
    //Normal attribute
    glVertexAttribPointer(3, NORMAL_SIZE, GL_FLOAT, GL_FALSE,
                          (vertex_stride) * sizeof(float),
                          (void *) ((VERTEX_SIZE + COLOR_SIZE + TEXTURE_SIZE) * sizeof(float)));

    glCheckError();
    glEnableVertexAttribArray(3);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(VAO);

    glCheckError();
    glDrawArrays(GL_TRIANGLES, 0, vertex_count);
    glCheckError();

}