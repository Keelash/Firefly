#ifndef MESH_H
#define MESH_H

#include "opengl_object/opengl_mesh.h"
#include "src/glm_include.h"



class G_Mesh : public OpenGL_ElementMesh {
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


    G_Mesh(unsigned int id, std::vector<G_Mesh_Vertex> &vertex_vector,
         std::vector<G_Mesh_Face> &face_vector): OpenGL_ElementMesh(), id_(id) {

        this->setData((GLfloat*) &vertex_vector[0], vertex_vector.size(), sizeof(G_Mesh_Vertex));
        this->defineDataSet(0, 3, GL_FLOAT, GL_FALSE, sizeof(G_Mesh_Vertex), (GLvoid*) 0);
        this->defineDataSet(1, 3, GL_FLOAT, GL_FALSE, sizeof(G_Mesh_Vertex), (GLvoid*) (3*sizeof(GLfloat)));
        this->defineDataSet(2, 3, GL_FLOAT, GL_FALSE, sizeof(G_Mesh_Vertex), (GLvoid*) (6*sizeof(GLfloat)));

        this->setElement((GLuint*) &face_vector[0], face_vector.size() * 3);
    }
    virtual ~G_Mesh() {  }

    unsigned int getId() { return this->id_; }

private:
    unsigned int id_;
};


class G_UVMesh : public OpenGL_Mesh {
public:

    typedef struct G_UVMesh_Vertex_s {
        glm::vec3 pos;
        glm::vec2 uv;
    } G_UVMesh_Vertex;

    G_UVMesh(std::vector<G_UVMesh_Vertex> &vertex_vector): OpenGL_Mesh() {
        this->setData((GLfloat*) &vertex_vector[0], vertex_vector.size(), sizeof(G_UVMesh_Vertex));
        this->defineDataSet(0, 3, GL_FLOAT, GL_FALSE, sizeof(G_UVMesh_Vertex), (GLvoid*) 0);
        this->defineDataSet(1, 2, GL_FLOAT, GL_FALSE, sizeof(G_UVMesh_Vertex), (GLvoid*) (3*sizeof(GLfloat)));
    }

    virtual ~G_UVMesh() {  }
};

#endif // MESH_H
