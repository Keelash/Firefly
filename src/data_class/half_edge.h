#ifndef HALF_EDGE_H
#define HALF_EDGE_H

#include "src/glm_include.h"
#include <vector>

typedef struct HEMesh_Vertex_s {
    glm::vec3 pos;
    glm::vec3 norm;
    glm::vec2 uv;

    std::vector<unsigned int> halfedge;
} HEMesh_Vertex;

typedef struct HEMesh_Face_s {
    std::vector<unsigned int> vertex;
    unsigned int halfedge;
} HEMesh_Face;

typedef struct HEMesh_HalfEdge_s {
    unsigned int vertex;
    unsigned int face;
    unsigned int next;
    unsigned int opposite;
} HEMesh_HalfEdge;


class HE_Mesh {
public:
    HE_Mesh();
    ~HE_Mesh() {  }

    int addVertex(glm::vec3 pos, glm::vec3 norm, glm::vec2 uv);
    int addFace(std::vector<unsigned int> &vector_vertex);

private:
    std::vector<HEMesh_Vertex> vector_vertex_;
    std::vector<HEMesh_Face> vector_face_;
    std::vector<HEMesh_HalfEdge> vector_halfedge_;
};

#endif//HALF_EDGE_H
