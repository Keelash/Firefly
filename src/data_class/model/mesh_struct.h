#ifndef STRUCT_MESH_H
#define STRUCT_MESH_H

#include "src/glm_include.h"

typedef struct MVertex_s {
    glm::vec3 pos;
    glm::vec3 normal;
    glm::vec2 uv;

    glm::vec4 boneWeight = glm::vec4(0.0f);
    glm::ivec4 boneId = glm::ivec4(0);
} MVertex;

typedef struct MFace_s {
    glm::ivec3 vertices;
} MFace;

#endif//STRUCT_MESH_H
