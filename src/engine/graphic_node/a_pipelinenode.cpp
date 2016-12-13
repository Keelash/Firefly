#include "a_pipelinenode.h"

#include <iostream>

A_QuadNode::A_QuadNode() {
    std::vector<G_UVMesh::G_UVMesh_Vertex> vertex_vector;
    GLfloat vertice[] = {
        -1.0f,  1.0f,  0.0f, 1.0f,
        -1.0f, -1.0f,  0.0f, 0.0f,
         1.0f, -1.0f,  1.0f, 0.0f,

        -1.0f,  1.0f,  0.0f, 1.0f,
         1.0f, -1.0f,  1.0f, 0.0f,
         1.0f,  1.0f,  1.0f, 1.0f
    };

    for(int i = 0; i < 6; ++i) {
        G_UVMesh::G_UVMesh_Vertex v;
        v.pos = glm::vec3(vertice[4*i+0], vertice[4*i+1], 0.0f);
        v.uv = glm::vec2(vertice[4*i+2], vertice[4*i+3]);

        vertex_vector.push_back(v);
    }

    this->quad_ = new G_UVMesh(vertex_vector);
}

A_QuadNode::~A_QuadNode() {
    delete this->quad_;
}
