#include "loopsubdivision.h"

#include <map>

#include "src/data_class/model/mesh.h"
#include "src/mesh_transform/loopsubdivision/gui/loopsubdivision_ui.h"

LoopSubdivision::LoopSubdivision() :
    curr_level_(0), max_level_(0) {

    this->ui_ = new LoopSubdivision_UI(this);
}

LoopSubdivision::~LoopSubdivision() {
    for(unsigned int i = 1; i < this->meshes_.size(); ++i) {
        delete this->meshes_[i];
    }
}

void LoopSubdivision::addSubdivisionLevel() {
    HalfEdgeMesh* o_mesh = this->meshes_[this->meshes_.size() - 1]->getHalfEdgeMesh();
    Mesh* new_mesh = new Mesh();
    HalfEdgeMesh *n_mesh = new_mesh->getHalfEdgeMesh();
    std::map<HalfEdgeMesh::EdgeHandle, HalfEdgeMesh::VertexHandle> edgeMap;

    n_mesh->request_vertex_normals();
    n_mesh->request_face_normals();
    n_mesh->request_vertex_texcoords2D();

    HalfEdgeMesh::VertexIter v_i;
    for(v_i = o_mesh->vertices_begin(); v_i != o_mesh->vertices_end(); ++v_i) {
        this->smoothVertex(*v_i, o_mesh, n_mesh);
    }

    HalfEdgeMesh::EdgeIter e_i;
    for(e_i = o_mesh->edges_begin(); e_i != o_mesh->edges_end(); ++e_i) {
        edgeMap[*e_i] = this->computeMidPoint(*e_i, o_mesh, n_mesh);
    }

    HalfEdgeMesh::FaceIter f_i;
    for(f_i = o_mesh->faces_begin(); f_i != o_mesh->faces_end(); ++f_i) {
        HalfEdgeMesh::HalfedgeHandle
                heh1(o_mesh->halfedge_handle(*f_i)),
                heh2(o_mesh->next_halfedge_handle(o_mesh->next_halfedge_handle(heh1))),
                heh3(o_mesh->next_halfedge_handle(o_mesh->next_halfedge_handle(heh2)));

        HalfEdgeMesh::VertexHandle
                vh1 = o_mesh->from_vertex_handle(heh1),
                vh2 = o_mesh->from_vertex_handle(heh2),
                vh3 = o_mesh->from_vertex_handle(heh3);

        HalfEdgeMesh::EdgeHandle
                eh1 = o_mesh->edge_handle(heh1),
                eh2 = o_mesh->edge_handle(heh2),
                eh3 = o_mesh->edge_handle(heh3);


        n_mesh->add_face(edgeMap[eh1], edgeMap[eh3], vh3);
        n_mesh->add_face(edgeMap[eh2], edgeMap[eh3], edgeMap[eh1]);
        n_mesh->add_face(vh1, edgeMap[eh2], edgeMap[eh1]);
        n_mesh->add_face(vh2, edgeMap[eh3], edgeMap[eh2]);
    }


    n_mesh->update_normals();
    n_mesh->release_face_normals();

    new_mesh->loadOnGPU();

    this->meshes_.push_back(new_mesh);
    ++this->max_level_;
}


void LoopSubdivision::smoothVertex(const HalfEdgeMesh::VertexHandle &vh, HalfEdgeMesh *i_m, HalfEdgeMesh *o_m) {
    HalfEdgeMesh::Point pos(0.0,0.0,0.0);

    if(i_m->is_boundary(vh)) {
      HalfEdgeMesh::HalfedgeHandle heh, prev_heh;

      heh = i_m->halfedge_handle(vh);
      prev_heh = i_m->prev_halfedge_handle(heh);

      HalfEdgeMesh::VertexHandle to_vh = i_m->to_vertex_handle(heh);
      HalfEdgeMesh::VertexHandle from_vh = i_m->from_vertex_handle(prev_heh);


      // ( v_l + 6 v + v_r ) / 8
      pos  = i_m->point(vh);
      pos *= 6.0;
      pos += i_m->point(to_vh) + i_m->point(from_vh);
      pos /= 8;
    }
    else {
      HalfEdgeMesh::VertexVertexIter vvit;
      unsigned int valence(0);

      // Calculate Valence and sum up neighbour points
      for(vvit = i_m->vv_iter(vh); vvit.is_valid(); ++vvit) {
        ++valence;
        pos += i_m->point(*vvit);
      }

      float B = (1.f / (float)valence) * (5.f/8.f - 3.f/8.f + 0.25f*std::cos(2.f*3.14f /(float)valence) * std::cos(2.f*3.14f/(float)valence));
      pos = i_m->point(vh) * (1.0 - valence * B) + pos * B;
    }

    o_m->add_vertex(pos);
}

HalfEdgeMesh::VertexHandle LoopSubdivision::computeMidPoint(const HalfEdgeMesh::EdgeHandle &eh, HalfEdgeMesh *i_m, HalfEdgeMesh *o_m) {
    HalfEdgeMesh::HalfedgeHandle heh, opp_heh;

    heh = i_m->halfedge_handle(eh, 0);
    opp_heh = i_m->halfedge_handle(eh, 1);

    HalfEdgeMesh::Point pos(i_m->point(i_m->to_vertex_handle(heh)));
    pos += i_m->point(i_m->to_vertex_handle(opp_heh));

    if(i_m->is_boundary(eh)) {
      pos *= 0.5;
    }
    else {
      pos *= 3.0f;
      pos += i_m->point(i_m->to_vertex_handle(i_m->next_halfedge_handle(heh)));
      pos += i_m->point(i_m->to_vertex_handle(i_m->next_halfedge_handle(opp_heh)));
      pos /= 8.0f;
    }

    return o_m->add_vertex(pos);
}

void LoopSubdivision::setBaseMesh(Mesh* mesh) {
    this->meshes_.push_back(mesh);
}

Mesh* LoopSubdivision::getMesh() {
    return this->meshes_[this->curr_level_];
}

QWidget* LoopSubdivision::getGUI() {
    return this->ui_;
}
