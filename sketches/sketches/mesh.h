#ifndef TYPES_H
#define TYPES_H

#import "vector.h"

typedef struct {
    int a;
    int b;
    int c;
} face_t;

typedef struct {
    vec2_t points[3];
} triangle_t;

typedef struct {
    vec3_t* vertices;   // Pointer to array of 3D vertices
    int vertex_count;   // Number of vertices

    face_t* faces;      // Pointer to array of face indices (triangles)
    int face_count;     // Number of faces
} mesh_t;

#endif
