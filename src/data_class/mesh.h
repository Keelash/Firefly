#ifndef MESH_H
#define MESH_H

#include "opengl_object/opengl_mesh.h"
#include "src/glm_include.h"


class G_Mesh : public OpenGLMesh {
public:

    //Declaration of the datatype used for this Mesh style
    typedef struct G_Mesh_Vertex_s {
        glm::vec3 pos;
        glm::vec3 normal;
        glm::vec2 uv;
    } G_Mesh_Vertex;

    typedef struct G_Mesh_Face_s {
        glm::ivec3 vertices;
    } G_Mesh_Face;


    //Declaration of the new class
    G_Mesh(std::vector<G_Mesh_Vertex> &vertex_vector,
         std::vector<G_Mesh_Face> &face_vector, unsigned int material_id): OpenGLMesh(DRAW_ELEMENT) {

        this->material_id_ = material_id;

        this->setData((GLfloat*) &vertex_vector[0], vertex_vector.size(), sizeof(G_Mesh_Vertex));
        this->defineDataSet(0, 3, GL_FLOAT, GL_FALSE, sizeof(G_Mesh_Vertex), (GLvoid*) 0);
        this->defineDataSet(1, 3, GL_FLOAT, GL_FALSE, sizeof(G_Mesh_Vertex), (GLvoid*) (3*sizeof(GLfloat)));
        this->defineDataSet(2, 3, GL_FLOAT, GL_FALSE, sizeof(G_Mesh_Vertex), (GLvoid*) (6*sizeof(GLfloat)));

        this->setElement((GLuint*) &face_vector[0], face_vector.size() * 3);
    }
    virtual ~G_Mesh() {  }

    unsigned int getMaterialId() const { return this->material_id_; }

private:
    unsigned int material_id_;
};


class G_UVMesh : public OpenGLMesh {
public:

    typedef struct G_UVMesh_Vertex_s {
        glm::vec3 pos;
        glm::vec2 uv;
    } G_UVMesh_Vertex;

    G_UVMesh(std::vector<G_UVMesh_Vertex> &vertex_vector): OpenGLMesh(DRAW_ARRAY) {
        this->setData((GLfloat*) &vertex_vector[0], vertex_vector.size(), sizeof(G_UVMesh_Vertex));
        this->defineDataSet(0, 3, GL_FLOAT, GL_FALSE, sizeof(G_UVMesh_Vertex), (GLvoid*) 0);
        this->defineDataSet(1, 2, GL_FLOAT, GL_FALSE, sizeof(G_UVMesh_Vertex), (GLvoid*) (3*sizeof(GLfloat)));
    }

    virtual ~G_UVMesh() {  }
};

#endif // MESH_H
