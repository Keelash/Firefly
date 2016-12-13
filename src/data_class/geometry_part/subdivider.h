#ifndef SUBDIVIDER
#define SUBDIVIDER

#include "half_edge.h"

class A_Subdivide {
public :
    virtual void subdivide(HE_Mesh &in, HE_Mesh &out) = 0;
};

class Loop_Subdivider : public A_Subdivide {
public:
    virtual void subdivide(HE_Mesh &in, HE_Mesh &out);
};

#endif//SUBDIVIDER
