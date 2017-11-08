#ifndef GPUMESH_H
#define GPUMESH_H

#include "src/data_class/opengl_object/opengl_mesh.h"
#include "src/glm_include.h"

#include "mesh_struct.h"

class GPUMesh : public OpenGLMesh {
public:
    GPUMesh(const std::vector<MVertex> &vertex_vector, const std::vector<MFace> &face_vector);
    virtual ~GPUMesh();
};

#endif //GPUMESH_H
