#include "mesh.h"

Mesh::Mesh() : g_mesh_(nullptr) {
    this->mesh_.request_vertex_normals();
    this->mesh_.request_vertex_texcoords2D();
}

Mesh::Mesh(const std::vector<MVertex> &vertex_vector, const std::vector<MFace> &face_vector) {
    std::vector<HalfEdgeMesh::VertexHandle> vh;

    this->g_mesh_ = new GPUMesh(vertex_vector, face_vector);

    this->mesh_.request_vertex_normals();
    this->mesh_.request_vertex_texcoords2D();

    for(unsigned int i = 0; i < vertex_vector.size(); ++i){
        MVertex v = vertex_vector[i];
        HalfEdgeMesh::Point p(v.pos.x, v.pos.y, v.pos.z);
        HalfEdgeMesh::Normal n(v.normal.x, v.normal.y, v.normal.z);
        HalfEdgeMesh::TexCoord2D tx(v.uv.x, v.uv.y);
        HalfEdgeMesh::VertexHandle vh_curr = this->mesh_.add_vertex(p);

        this->mesh_.set_normal(vh_curr, n);
        this->mesh_.set_texcoord2D(vh_curr, tx);

        for(unsigned int i = 0; i < 4; ++i) {
            this->mesh_.data(vh_curr).setBoneId(i, v.boneId[i]);
            this->mesh_.data(vh_curr).setBoneWeight(i, v.boneWeight[i]);
        }

        vh.push_back(vh_curr);
    }

    for(unsigned int i = 0; i < face_vector.size(); ++i) {
        MFace f = face_vector[i];
        this->mesh_.add_face(vh[f.vertices.x], vh[f.vertices.y], vh[f.vertices.z]);
    }
}


void Mesh::loadOnGPU() {
    std::vector<MVertex> vertex_vector;
    std::vector<MFace> face_vector;

    if(this->g_mesh_ != nullptr) {
        return ;
    }

    HalfEdgeMesh *m = &this->mesh_;

    HalfEdgeMesh::VertexIter vi;
    for(vi = m->vertices_begin(); vi != m->vertices_end(); ++vi) {
        MVertex v;

        v.pos = glm::vec3(m->point(*vi)[0], m->point(*vi)[1], m->point(*vi)[2]);
        v.normal = glm::vec3(m->normal(*vi)[0], m->normal(*vi)[1], m->normal(*vi)[2]);
        vertex_vector.push_back(v);
    }

    HalfEdgeMesh::FaceIter fi;
    for(fi = m->faces_begin(); fi != m->faces_end(); ++fi) {
        MFace f;
        HalfEdgeMesh::HalfedgeHandle
          heh1(m->halfedge_handle(*fi)),
          heh2(m->next_halfedge_handle(m->next_halfedge_handle(heh1))),
          heh3(m->next_halfedge_handle(m->next_halfedge_handle(heh2)));

        f.vertices[0] = m->from_vertex_handle(heh1).idx();
        f.vertices[1] = m->from_vertex_handle(heh2).idx();
        f.vertices[2] = m->from_vertex_handle(heh3).idx();

        face_vector.push_back(f);
    }

    this->g_mesh_ = new GPUMesh(vertex_vector, face_vector);
}
