#ifndef MESH_H
#define MESH_H

#include <OpenMesh/Core/Mesh/TriMesh_ArrayKernelT.hh>
#include <OpenMesh/Core/Mesh/Traits.hh>

#include "mesh_struct.h"
#include "halfedgemesh.h"
#include "gpumesh.h"

class Mesh {
public:
    Mesh();
    Mesh(const std::vector<MVertex> &vertex_vector, const std::vector<MFace> &face_vector);
    virtual ~Mesh() { delete this->g_mesh_; }

    void loadOnGPU();

    HalfEdgeMesh* getHalfEdgeMesh() { return &this->mesh_; }
    GPUMesh* getGraphicMesh() { return this->g_mesh_; }

private:
    HalfEdgeMesh mesh_;
    GPUMesh *g_mesh_;
};

#endif//MESH_H
