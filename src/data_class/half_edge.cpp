#include "half_edge.h"

HE_Mesh::HE_Mesh() {
    HEMesh_HalfEdge f;
    this->vector_halfedge_.push_back(f);
}

int HE_Mesh::addVertex(glm::vec3 pos, glm::vec3 norm, glm::vec2 uv) {
    HEMesh_Vertex v;

    v.pos = pos;
    v.norm = norm;
    v.uv = uv;

    this->vector_vertex_.push_back(v);
    return this->vector_vertex_.size() - 1;
}

int HE_Mesh::addFace(std::vector<unsigned int> &vector_vertex) {
    std::vector<HEMesh_HalfEdge> v_he;
    HEMesh_HalfEdge he;
    HEMesh_Face f;
    unsigned int face_size = vector_vertex.size();

    f.halfedge = this->vector_halfedge_.size();

    for(unsigned int i = 0; i < vector_vertex.size(); ++i) {
        unsigned int curr = vector_vertex[i];
        unsigned int next = vector_vertex[(i+1) % face_size];
        unsigned int he_size_next = this->vector_vertex_[next].halfedge.size();

        f.vertex.push_back(curr);

        he.face = this->vector_face_.size();
        he.next = this->vector_halfedge_.size() + (i+1)%face_size;
        he.vertex = curr;
        he.opposite = 0;

        for (unsigned int j = 0; j < he_size_next; ++j) {
            unsigned int pos = this->vector_vertex_[next].halfedge[j];

            if (this->vector_halfedge_[this->vector_halfedge_[pos].next].vertex == curr)
                he.opposite = pos;
        }

        v_he.push_back(he);
    }

    for (unsigned int i = 0; i < vector_vertex.size(); ++i)
        this->vector_vertex_[vector_vertex[i]].halfedge.push_back(this->vector_halfedge_.size() + i);

    for (unsigned int i = 0; i < v_he.size(); ++i) {
        this->vector_halfedge_[v_he[i].opposite].opposite = this->vector_halfedge_.size();
        this->vector_halfedge_.push_back(v_he[i]);
    }

    this->vector_face_.push_back(f);

    return this->vector_face_.size() - 1;
}
