#include "opengl_mesh.h"

#include <iostream>

A_OpenGlMesh::A_OpenGlMesh() : vbo_(0) {
    this->initializeOpenGLFunctions();

    glGenVertexArrays(1, &this->vao_);
}

A_OpenGlMesh::~A_OpenGlMesh() {
    glDeleteVertexArrays(1, &this->vao_);
}

void A_OpenGlMesh::bind() {
    glBindVertexArray(this->vao_);
}

void A_OpenGlMesh::unbind() {
    glBindVertexArray(0);
}

void A_OpenGlMesh::setData(GLfloat *data_vector, GLuint nbPoint, GLuint data_size) {
    if(this->vbo_ == 0) {
        glGenBuffers(1, &this->vbo_);
    }

    glBindVertexArray(this->vao_);
    glBindBuffer(GL_ARRAY_BUFFER, this->vbo_);
        glBufferData(GL_ARRAY_BUFFER, nbPoint * data_size, data_vector, GL_STATIC_DRAW);
    glBindVertexArray(0);

    this->nbPoint_ = nbPoint;
}

void A_OpenGlMesh::defineDataSet(GLuint index, GLuint size, GLenum type,
                   GLboolean normalized, GLsizei stride, GLvoid* pointer)
{
    glBindVertexArray(this->vao_);
    glBindBuffer(GL_ARRAY_BUFFER, this->vbo_);
        glVertexAttribPointer(index, size, type, normalized, stride, pointer);
        glEnableVertexAttribArray(index);
    glBindVertexArray(0);
}

void OpenGL_ElementMesh::setElement(GLuint *indices_vector, GLuint nbPoint) {
    if(this->ebo_ == 0) {
        glGenBuffers(1, &this->ebo_);
    }

    glBindVertexArray(this->vao_);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->ebo_);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, nbPoint * sizeof(GLuint), indices_vector, GL_STATIC_DRAW);
    glBindVertexArray(0);

    this->nbPoint_ = nbPoint;
}

void OpenGL_ElementMesh::draw() {
    glDrawElements(GL_TRIANGLES, this->nbPoint_, GL_UNSIGNED_INT, 0);
}

void OpenGL_Mesh::draw() {
    glDrawArrays(GL_TRIANGLES, 0, this->nbPoint_);
}

