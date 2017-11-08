#ifndef QUADMESH_H
#define QUADMESH_H

#include "src/data_class/opengl_object/opengl_mesh.h"
#include "src/glm_include.h"

class UVMesh : public OpenGLMesh {
public:

    typedef struct G_UVMesh_Vertex_s {
        glm::vec3 pos;
        glm::vec2 uv;
    } UVMesh_Vertex;

    UVMesh(std::vector<UVMesh_Vertex> &vertex_vector);
    UVMesh();
    virtual ~UVMesh();
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
