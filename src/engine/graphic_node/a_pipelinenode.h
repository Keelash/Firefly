#ifndef A_PIPELINENODE
#define A_PIPELINENODE

#include "src/data_class/database.h"
#include "src/data_class/graphic_part/framebuffer.h"

class A_GeometricNode {
public:
    A_GeometricNode() { }
    virtual ~A_GeometricNode() {  }

    virtual void drawGeometry(GeometryBuffer *gbuffer, DataBase *data) = 0;
};

class A_QuadNode {
public:
    A_QuadNode();
    virtual ~A_QuadNode();
protected:
    SimpleUvMesh *quad_;
};


class A_ShadingNode : public A_QuadNode {
    virtual void draw(GeometryBuffer *buffer, DataBase *data, RenderBuffer *render) = 0;
};

class A_PostProcessNode : public A_QuadNode {
    virtual void draw(RenderBuffer *hdr, DataBase *data) = 0;
};

#endif //A_PIPELINENODE
