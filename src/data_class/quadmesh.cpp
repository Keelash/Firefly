#include "quadmesh.h"

QuadMesh* QuadMesh::instance_ = nullptr;

QuadMesh* QuadMesh::getInstance() {
    if(QuadMesh::instance_ == nullptr) {
        QuadMesh::instance_ = new QuadMesh();
    }

    return QuadMesh::instance_;
}

QuadMesh::QuadMesh() {
    std::vector<UVMesh::UVMesh_Vertex> vertex_vector;
    GLfloat vertice[] = {
        -1.0f,  1.0f,  0.0f, 1.0f,
        -1.0f, -1.0f,  0.0f, 0.0f,
         1.0f, -1.0f,  1.0f, 0.0f,

        -1.0f,  1.0f,  0.0f, 1.0f,
         1.0f, -1.0f,  1.0f, 0.0f,
         1.0f,  1.0f,  1.0f, 1.0f
    };

    for(int i = 0; i < 6; ++i) {
        UVMesh::UVMesh_Vertex v;
        v.pos = glm::vec3(vertice[4*i+0], vertice[4*i+1], 0.0f);
        v.uv = glm::vec2(vertice[4*i+2], vertice[4*i+3]);

        vertex_vector.push_back(v);
    }

    this->setData((GLfloat*) &vertex_vector[0], vertex_vector.size(), sizeof(UVMesh_Vertex));
    this->defineDataSet(0, 3, GL_FLOAT, GL_FALSE, sizeof(UVMesh_Vertex), (GLvoid*) 0);
    this->defineDataSet(1, 2, GL_FLOAT, GL_FALSE, sizeof(UVMesh_Vertex), (GLvoid*) (3*sizeof(GLfloat)));
}

QuadMesh::~QuadMesh() {

}
