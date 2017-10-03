#ifndef MESH_H
#define MESH_H

#include "opengl_object/opengl_mesh.h"
#include "src/glm_include.h"



class Mesh : public OpenGLMesh {
public:

    //Declaration of the datatype used for this Mesh style
    typedef struct G_Mesh_Vertex_s {
        glm::vec3 pos;
        glm::vec3 normal;
        glm::vec2 uv;

        glm::ivec4 boneId = glm::ivec4(0);
        glm::vec4 boneWeight = glm::vec4(0.0f);
    } G_Mesh_Vertex;

    typedef struct G_Mesh_Face_s {
        glm::ivec3 vertices;
    } G_Mesh_Face;

    typedef struct Bones_s {
        glm::mat4 offset_;
        glm::mat4 toParent_;
        std::vector<unsigned int> children_;
    } Bones;

    //Declaration of the new class
    Mesh(std::vector<G_Mesh_Vertex> &vertex_vector,
         std::vector<G_Mesh_Face> &face_vector): OpenGLMesh(DRAW_ELEMENT) {

        std::size_t f = sizeof(GLfloat), i = sizeof(GLint);

        this->setData((GLfloat*) &vertex_vector[0], vertex_vector.size(), sizeof(G_Mesh_Vertex));
        this->defineDataSet(0, 3, GL_FLOAT, GL_FALSE, sizeof(G_Mesh_Vertex), (GLvoid*) 0);
        this->defineDataSet(1, 3, GL_FLOAT, GL_FALSE, sizeof(G_Mesh_Vertex), (GLvoid*) (3*f));
        this->defineDataSet(2, 3, GL_FLOAT, GL_FALSE, sizeof(G_Mesh_Vertex), (GLvoid*) (6*f));

        this->defineDataSet(3, 4, GL_INT, GL_FALSE, sizeof(G_Mesh_Vertex), (GLvoid*) (9*f));
        this->defineDataSet(4, 4, GL_FLOAT, GL_FALSE, sizeof(G_Mesh_Vertex), (GLvoid*) (9*f+3*i));

        this->setElement((GLuint*) &face_vector[0], face_vector.size() * 3);
    }

    virtual ~Mesh() {  }

    int boneRoot_ = -1;
    std::vector<Bones> bones_;
};

#endif // MESH_H
