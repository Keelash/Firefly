#ifndef QUADMESH_H
#define QUADMESH_H

#include "mesh.h"

class QuadMesh : public UVMesh {
public:
    static QuadMesh* getInstance();

    ~QuadMesh();

private :
    static QuadMesh* instance_;

    QuadMesh();
};

#endif // QUADMESH_H
