#ifndef MESH_H
#define MESH_H

#include "opengl_object/opengl_mesh.h"
#include "src/glm_include.h"

typedef struct Model_Vertex_s {
    glm::vec3 pos;
    glm::vec3 normal;
    glm::vec2 uv;
} Model_Vertex;

typedef struct Model_Face_s {
    glm::ivec3 vertices;
} Model_Face;

class Mesh : public OpenGL_ElementMesh {
public:
    Mesh(unsigned int id, std::vector<Model_Vertex> &vertex_vector,
         std::vector<Model_Face> &face_vector): OpenGL_ElementMesh(), id_(id) {

        this->setData((GLfloat*) &vertex_vector[0], vertex_vector.size(), sizeof(Model_Vertex));
        this->defineDataSet(0, 3, GL_FLOAT, GL_FALSE, sizeof(Model_Vertex), (GLvoid*) 0);
        this->defineDataSet(1, 3, GL_FLOAT, GL_FALSE, sizeof(Model_Vertex), (GLvoid*) (3*sizeof(GLfloat)));
        this->defineDataSet(2, 3, GL_FLOAT, GL_FALSE, sizeof(Model_Vertex), (GLvoid*) (6*sizeof(GLfloat)));

        this->setElement((GLuint*) &face_vector[0], face_vector.size() * 3);
    }
    virtual ~Mesh() {  }

    unsigned int getId() { return this->id_; }

private:
    unsigned int id_;
};

typedef struct SimpleUVMesh_Vertex_s {
    glm::vec3 pos;
    glm::vec2 uv;
} SimpleUVMesh_Vertex;

class SimpleUvMesh : public OpenGL_Mesh {
public:
    SimpleUvMesh(std::vector<SimpleUVMesh_Vertex> &vertex_vector): OpenGL_Mesh() {
        this->setData((GLfloat*) &vertex_vector[0], vertex_vector.size(), sizeof(SimpleUVMesh_Vertex));
        this->defineDataSet(0, 3, GL_FLOAT, GL_FALSE, sizeof(SimpleUVMesh_Vertex), (GLvoid*) 0);
        this->defineDataSet(1, 2, GL_FLOAT, GL_FALSE, sizeof(SimpleUVMesh_Vertex), (GLvoid*) (3*sizeof(GLfloat)));
    }

    virtual ~SimpleUvMesh() {  }
};

#endif // MESH_H
