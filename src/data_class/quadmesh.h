#ifndef QUADMESH_H
#define QUADMESH_H

#include "mesh.h"

class UVMesh : public OpenGLMesh {
public:

    typedef struct G_UVMesh_Vertex_s {
        glm::vec3 pos;
        glm::vec2 uv;
    } UVMesh_Vertex;

    UVMesh(std::vector<UVMesh_Vertex> &vertex_vector): OpenGLMesh(DRAW_ARRAY) {
        this->setData((GLfloat*) &vertex_vector[0], vertex_vector.size(), sizeof(UVMesh_Vertex));
        this->defineDataSet(0, 3, GL_FLOAT, GL_FALSE, sizeof(UVMesh_Vertex), (GLvoid*) 0);
        this->defineDataSet(1, 2, GL_FLOAT, GL_FALSE, sizeof(UVMesh_Vertex), (GLvoid*) (3*sizeof(GLfloat)));
    }

    UVMesh() : OpenGLMesh(DRAW_ARRAY) {  }
    virtual ~UVMesh() {  }
};

class QuadMesh : public UVMesh {
public:
    static QuadMesh* getInstance();

    ~QuadMesh();

private :
    static QuadMesh* instance_;

    QuadMesh();
};

#endif // QUADMESH_H
