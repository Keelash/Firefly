#include "subdivider.h"

void Loop_Subdivider::subdivide(HE_Mesh &in, HE_Mesh &out) {
    std::vector<int> midPoint_vector = std::vector<int>(in.nbHalfEdge(), -1);

    HE_Mesh::Vertex_Iterator v_it;
    HE_Mesh::HalfEdge_Iterator he_it;
    HE_Mesh::Face_Iterator fa_it;

    //We replace the existing point
    for(v_it = in.vertBegin(); v_it != in.vertEnd(); ++v_it) {
        HEMesh_Vertex v = *v_it;
        glm::vec3 pos(0.0f);

        float n = (float)v.halfedge.size();
        float B = (n == 2) ? 0.125f : (n == 3)? 0.1875f : 3.0f / (8.0f * n);

        pos = v.pos * (1.0f - n * B);

        for(int i = 0; i < v.halfedge.size(); ++i) {
            HEMesh_HalfEdge next_he = in.getHalfEdge(in.getHalfEdge(v.halfedge[i]).next);
            pos += in.getVertex(next_he.vertex).pos * B;
        }

        out.addVertex(pos, glm::vec3(0.0f));
    }

    //We compute the edge mid-point
    int i = 0;
    for(he_it = in.heBegin(); he_it != in.heEnd(); ++he_it) {
        HEMesh_HalfEdge he = *he_it;
        HEMesh_Vertex v1, v2, v3, v4;
        glm::vec3 pos;

        v1 = in.getVertex(he.vertex);
        v2 = in.getVertex(in.getHalfEdge(he.next).vertex);

        if(midPoint_vector[i] == -1) {
            if(he.opposite != 0) {
                v3 = in.getVertex(in.getHalfEdge(in.getHalfEdge(he.next).next).vertex);
                v4 = in.getVertex(in.getHalfEdge(in.getHalfEdge(in.getHalfEdge(he.opposite).next).next).vertex);

                pos = 0.375f * (v1.pos + v2.pos) + 0.175f * (v3.pos + v4.pos);
                midPoint_vector[he.opposite] = midPoint_vector[i++] = out.addVertex(pos, glm::vec3(0.0f));
            }
            else {
                pos = 0.5f * (v1.pos + v2.pos);

                midPoint_vector[i++] = out.addVertex(pos, glm::vec3(0.0f));
            }
        }
    }

    //We create the new faces
    for(fa_it = in.faceBegin(); fa_it != in.faceEnd(); ++fa_it) {
        HEMesh_HalfEdge he = in.getHalfEdge(fa_it->halfedge);
        unsigned int pv1, pv2, pv3, mv1, mv2, mv3;
        std::vector<unsigned int> face_ve;

        pv1 = he.vertex;
        pv2 = in.getHalfEdge(he.next).vertex;
        pv3 = in.getHalfEdge(in.getHalfEdge(he.next).next).vertex;

        mv1 = midPoint_vector[fa_it->halfedge];
        mv2 = midPoint_vector[he.next];
        mv3 = midPoint_vector[in.getHalfEdge(he.next).next];

        face_ve.push_back(pv1); face_ve.push_back(mv1); face_ve.push_back(mv3);
        out.addFace(face_ve);
        face_ve.clear();

        face_ve.push_back(mv1); face_ve.push_back(pv2); face_ve.push_back(mv2);
        out.addFace(face_ve);
        face_ve.clear();

        face_ve.push_back(mv2); face_ve.push_back(pv3); face_ve.push_back(mv3);
        out.addFace(face_ve);
        face_ve.clear();

        face_ve.push_back(mv1); face_ve.push_back(mv2); face_ve.push_back(mv3);
        out.addFace(face_ve);
        face_ve.clear();
    }
}
