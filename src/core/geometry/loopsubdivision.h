#ifndef LOOPSUBDIVISION_H
#define LOOPSUBDIVISION_H

#include <vector>

#include "src/data_class/model/halfedgemesh.h"
#include "transformfactory.h"

class Mesh;

class LoopSubdivision : public A_Transform {
public:
    LoopSubdivision();
    ~LoopSubdivision();

    static std::string& getTransformName() {
        static std::string name = "LoopSubdivision";
        return name;
    }

    unsigned int getMaxSubdivisionLevel() const { return this->max_level_; }

    unsigned int getCurrentSubdivisionLevel() const {return this->curr_level_; }
    void setCurrentSubdivisionLevel(unsigned int level) { this->curr_level_ = std::min(level, this->max_level_); }

    void addSubdivisionLevel();

    virtual void setBaseMesh(Mesh* mesh);
    virtual Mesh* getMesh();

private:
    void smoothVertex(const HalfEdgeMesh::VertexHandle &vh, HalfEdgeMesh *i_m, HalfEdgeMesh *o_m);
    HalfEdgeMesh::VertexHandle computeMidPoint(const HalfEdgeMesh::EdgeHandle &eh, HalfEdgeMesh *i_m, HalfEdgeMesh *o_m);

    std::vector<Mesh*> meshes_;

    unsigned int curr_level_;
    unsigned int max_level_;
};

REGISTER_TRANSFORM_TYPE(LoopSubdivision, "LoopSubdivision")

#endif//LOOPSUBDIVISION_H
