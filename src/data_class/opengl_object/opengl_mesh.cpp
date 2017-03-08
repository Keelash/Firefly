#include "opengl_mesh.h"

#include <iostream>

OpenGLMesh::OpenGLMesh(DrawType type) : vbo_(0), ebo_(0), type_(type) {
    this->initializeOpenGLFunctions();

    glGenVertexArrays(1, &this->vao_);
}

OpenGLMesh::OpenGLMesh(OpenGLMesh &other) :
    vao_(other.vao_), vbo_(other.vbo_), ebo_(other.ebo_),
    nbPoint_(other.nbPoint_), type_(other.type_) {

    this->initializeOpenGLFunctions();
}

OpenGLMesh::~OpenGLMesh() {
    glDeleteVertexArrays(1, &this->vao_);
}

void OpenGLMesh::bind(){
    glBindVertexArray(this->vao_);
}

void OpenGLMesh::unbind(){
    glBindVertexArray(0);
}

void OpenGLMesh::draw(){
    switch(this->type_) {
    case DRAW_ARRAY :
        glDrawArrays(GL_TRIANGLES, 0, this->nbPoint_);
        break;
    case DRAW_ELEMENT :
        glDrawElements(GL_TRIANGLES, this->nbPoint_, GL_UNSIGNED_INT, 0);
        break;
    }
}

void OpenGLMesh::setData(GLfloat *data_vector, GLuint nbPoint, GLuint data_size) {
    if(this->vbo_ == 0) {
        glGenBuffers(1, &this->vbo_);
    }

    glBindVertexArray(this->vao_);
    glBindBuffer(GL_ARRAY_BUFFER, this->vbo_);
        glBufferData(GL_ARRAY_BUFFER, nbPoint * data_size, data_vector, GL_STATIC_DRAW);
    glBindVertexArray(0);

    this->nbPoint_ = nbPoint;
}

void OpenGLMesh::setElement(GLuint *indices_vector, GLuint nbPoint) {
    if(this->ebo_ == 0) {
        glGenBuffers(1, &this->ebo_);
    }

    glBindVertexArray(this->vao_);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->ebo_);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, nbPoint * sizeof(GLuint), indices_vector, GL_STATIC_DRAW);
    glBindVertexArray(0);

    this->nbPoint_ = nbPoint;
}

void OpenGLMesh::defineDataSet(GLuint index, GLuint size, GLenum type,
                   GLboolean normalized, GLsizei stride, GLvoid* pointer)
{
    glBindVertexArray(this->vao_);
    glBindBuffer(GL_ARRAY_BUFFER, this->vbo_);
        glVertexAttribPointer(index, size, type, normalized, stride, pointer);
        glEnableVertexAttribArray(index);
    glBindVertexArray(0);
}
