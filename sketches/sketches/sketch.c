#include "../colors.h"
#include "f22.h"
// #include "cube_data.h"
#include "rendering.h"

#include <math.h>
#include <stdlib.h>
#include <time.h>

vec3_t camera_position = {0, 0, -6};
float fov_factor       = 640.0;
vec3_t rotation;

vec2_t project(vec3_t point, float fov_factor) {
    vec2_t projected_point = {
        .x = (fov_factor * point.x) / point.z,
        .y = (fov_factor * point.y) / point.z,
    };
    return projected_point;
}

void drawSketch(int width, int height, SetPixelColorFunc setPixelColor, GetPixelColorFunc getPixelColor) {
    Color colors[] = {BLACK, WHITE, GREEN, BLUE, RED, YELLOW, ORANGE};

    srand(time(NULL)); // Use current time as seed

    rotation.x = ((float) rand() / RAND_MAX) * (2.0f * M_PI);
    rotation.y = ((float) rand() / RAND_MAX) * (2.0f * M_PI);
    rotation.z = ((float) rand() / RAND_MAX) * (2.0f * M_PI);

    for (int i = 0; i < mesh.face_count; i++) {
        face_t face = mesh.faces[i];

        // gather 3d vertices for face (triangle)
        vec3_t v1 = mesh.vertices[face.a];
        vec3_t v2 = mesh.vertices[face.b];
        vec3_t v3 = mesh.vertices[face.c];

        // apply 3D transformations
        v1 = vec3_rotate_x(v1, rotation.x);
        v1 = vec3_rotate_y(v1, rotation.y);
        v1 = vec3_rotate_z(v1, rotation.z);
        v2 = vec3_rotate_x(v2, rotation.x);
        v2 = vec3_rotate_y(v2, rotation.y);
        v2 = vec3_rotate_z(v2, rotation.z);
        v3 = vec3_rotate_x(v3, rotation.x);
        v3 = vec3_rotate_y(v3, rotation.y);
        v3 = vec3_rotate_z(v3, rotation.z);

        // apply camera position
        v1.z -= camera_position.z;
        v2.z -= camera_position.z;
        v3.z -= camera_position.z;

        // project to 2D
        vec2_t p1 = project(v1, fov_factor);
        vec2_t p2 = project(v2, fov_factor);
        vec2_t p3 = project(v3, fov_factor);

        // offset point to middle of screen (origin correct)
        p1.x += (width / 2);
        p1.y += (height / 2);
        p2.x += (width / 2);
        p2.y += (height / 2);
        p3.x += (width / 2);
        p3.y += (height / 2);

        // select a random color (skip black)
        int color_count    = sizeof(colors) / sizeof(colors[0]);
        Color random_color = colors[1 + rand() % (color_count - 1)];

        // draw triangle
        draw_line(p1.x, p1.y, p2.x, p2.y, random_color, setPixelColor);
        draw_line(p2.x, p2.y, p3.x, p3.y, random_color, setPixelColor);
        draw_line(p3.x, p3.y, p1.x, p1.y, random_color, setPixelColor);
    }
}
