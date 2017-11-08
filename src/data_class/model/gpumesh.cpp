#include "gpumesh.h"

GPUMesh::GPUMesh(const std::vector<MVertex> &vertex_vector, const std::vector<MFace> &face_vector):
    OpenGLMesh(DRAW_ELEMENT) {

    std::size_t f = sizeof(GLfloat);

    this->setData((GLfloat*) &vertex_vector[0], vertex_vector.size(), sizeof(MVertex));
    this->defineDataSet(0, 3, GL_FLOAT, GL_FALSE, sizeof(MVertex), (GLvoid*) 0);
    this->defineDataSet(1, 3, GL_FLOAT, GL_FALSE, sizeof(MVertex), (GLvoid*) (3*f));
    this->defineDataSet(2, 2, GL_FLOAT, GL_FALSE, sizeof(MVertex), (GLvoid*) (6*f));

    this->defineDataSet(3, 4, GL_FLOAT, GL_FALSE, sizeof(MVertex), (GLvoid*) (8*f));
    this->defineDataSet(4, 4, GL_INT, GL_FALSE, sizeof(MVertex), (GLvoid*) (12*f));

    this->setElement((GLuint*) &face_vector[0], face_vector.size() * 3);
}

GPUMesh::~GPUMesh() {

}
