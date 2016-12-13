#ifndef HALF_EDGE_H
#define HALF_EDGE_H

#include "src/glm_include.h"
#include <vector>

typedef struct HEMesh_Vertex_s {
    glm::vec3 pos;
    glm::vec3 norm;

    std::vector<unsigned int> halfedge;
} HEMesh_Vertex;

typedef struct HEMesh_Face_s {
    //std::vector<unsigned int> vertex;
    unsigned int halfedge;
} HEMesh_Face;

typedef struct HEMesh_HalfEdge_s {
    unsigned int vertex;
    unsigned int face;
    unsigned int next;
    unsigned int opposite;
} HEMesh_HalfEdge;


class HE_Mesh {
public:
    typedef std::vector<HEMesh_Face>::iterator Face_Iterator;
    typedef std::vector<HEMesh_Vertex>::iterator Vertex_Iterator;
    typedef std::vector<HEMesh_HalfEdge>::iterator HalfEdge_Iterator;


    HE_Mesh();
    ~HE_Mesh() {  }

    int addVertex(glm::vec3 pos, glm::vec3 norm);
    int addFace(std::vector<unsigned int> &vector_vertex);

    unsigned int nbFace() { return this->vector_face_.size(); }
    unsigned int nbVertex() { return this->vector_vertex_.size(); }
    unsigned int nbHalfEdge() { return this->vector_halfedge_.size() - 1; }

    HEMesh_Face getFace(unsigned int pos) { return this->vector_face_[pos]; }
    HEMesh_Vertex getVertex(unsigned int pos) { return this->vector_vertex_[pos]; }
    HEMesh_HalfEdge getHalfEdge(unsigned int pos) { return this->vector_halfedge_[pos+1]; }

    Face_Iterator faceBegin() { return this->vector_face_.begin(); }
    Face_Iterator faceEnd() { return this->vector_face_.end(); }

    Vertex_Iterator vertBegin() { return this->vector_vertex_.begin(); }
    Vertex_Iterator vertEnd() { return this->vector_vertex_.end(); }

    HalfEdge_Iterator heBegin() { return this->vector_halfedge_.begin()++; }
    HalfEdge_Iterator heEnd() { return this->vector_halfedge_.end(); }

private:
    std::vector<HEMesh_Vertex> vector_vertex_;
    std::vector<HEMesh_Face> vector_face_;
    std::vector<HEMesh_HalfEdge> vector_halfedge_;
};

#endif//HALF_EDGE_H
