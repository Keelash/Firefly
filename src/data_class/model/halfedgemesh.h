#ifndef HALFEDGEMESH_H
#define HALFEDGEMESH_H

#include <OpenMesh/Core/Mesh/TriMesh_ArrayKernelT.hh>
#include <OpenMesh/Core/Mesh/Traits.hh>

struct HalfEdgeTraits : public OpenMesh::DefaultTraits {
    VertexTraits {
        public:
        VertexT() {
            for(unsigned int i = 0; i < 4; ++i) {
                this->bonesId_[i] = 0;
                this->bonesWeight_[i] = 0.0f;
            }
        }

        const unsigned int getBoneId(unsigned int pos) const { return this->bonesId_[pos]; }
        void setBoneId(unsigned int pos, unsigned int value) { this->bonesId_[pos] = value; }

        const float getBoneWeight(unsigned int pos) const { return this->bonesWeight_[pos]; }
        void setBoneWeight(unsigned int pos, float value) { this->bonesWeight_[pos] = value; }

        private:
        unsigned int bonesId_[4];
        float bonesWeight_[4];
    };
};

typedef OpenMesh::TriMesh_ArrayKernelT<HalfEdgeTraits> HalfEdgeMesh;

#endif//HALFEDGEMESH_H
