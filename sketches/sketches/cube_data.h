#ifndef CUBE_DATA_H
#define CUBE_DATA_H

#include "vector.h"
#include "mesh.h"

static const vec3_t cube_vertices[8] = {
    { 1.000000f, -1.000000f, -1.000000f },
    { 1.000000f, -1.000000f, 1.000000f },
    { -1.000000f, -1.000000f, 1.000000f },
    { -1.000000f, -1.000000f, -1.000000f },
    { 1.000000f,  1.000000f, -0.999999f },
    { 0.999999f,  1.000000f,  1.000001f },
    { -1.000000f,  1.000000f,  1.000000f },
    { -1.000000f,  1.000000f, -1.000000f },
};

static const face_t cube_faces[12] = {
    { 0, 1, 2 },
    { 2, 3, 0 },
    { 4, 7, 6 },
    { 6, 5, 4 },
    { 0, 4, 5 },
    { 5, 1, 0 },
    { 1, 5, 6 },
    { 6, 2, 1 },
    { 2, 6, 7 },
    { 7, 3, 2 },
    { 4, 0, 3 },
    { 3, 7, 4 },
};

// A statically declared mesh that references the above arrays
static const mesh_t mesh = {
    .vertices = (vec3_t*)cube_vertices,
    .vertex_count = sizeof(cube_vertices) / sizeof(cube_vertices[0]),
    .faces = (face_t*)cube_faces,
    .face_count = sizeof(cube_faces) / sizeof(cube_faces[0])
};

#endif
