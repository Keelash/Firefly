#ifndef MESH_H
#define MESH_H

#include "opengl_object/opengl_mesh.h"
#include "src/glm_include.h"

#include "animation.h"

class Mesh : public OpenGLMesh {
public:
    //Declaration of the datatype used for this Mesh style
    typedef struct G_Mesh_Vertex_s {
        glm::vec3 pos;
        glm::vec3 normal;
        glm::vec2 uv;

        glm::vec4 boneWeight = glm::vec4(0.0f);
        glm::ivec4 boneId = glm::ivec4(0);
    } G_Mesh_Vertex;

    typedef struct G_Mesh_Face_s {
        glm::ivec3 vertices;
    } G_Mesh_Face;

    //Declaration of the new class
    Mesh(std::vector<G_Mesh_Vertex> &vertex_vector,
         std::vector<G_Mesh_Face> &face_vector): OpenGLMesh(DRAW_ELEMENT) {

        std::size_t f = sizeof(GLfloat);

        this->setData((GLfloat*) &vertex_vector[0], vertex_vector.size(), sizeof(G_Mesh_Vertex));
        this->defineDataSet(0, 3, GL_FLOAT, GL_FALSE, sizeof(G_Mesh_Vertex), (GLvoid*) 0);
        this->defineDataSet(1, 3, GL_FLOAT, GL_FALSE, sizeof(G_Mesh_Vertex), (GLvoid*) (3*f));
        this->defineDataSet(2, 2, GL_FLOAT, GL_FALSE, sizeof(G_Mesh_Vertex), (GLvoid*) (6*f));

        this->defineDataSet(3, 4, GL_FLOAT, GL_FALSE, sizeof(G_Mesh_Vertex), (GLvoid*) (8*f));
        this->defineDataSet(4, 4, GL_INT, GL_FALSE, sizeof(G_Mesh_Vertex), (GLvoid*) (12*f));

        this->setElement((GLuint*) &face_vector[0], face_vector.size() * 3);
    }

    virtual ~Mesh() {  }

    int boneRoot_ = -1;
    AnimationsData *animations_ = nullptr;
};

#endif // MESH_H
