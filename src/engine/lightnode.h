#ifndef LIGHTNODE_H
#define LIGHTNODE_H

#include <string>

#include "a_pipelinenode.h"
#include "src/data_class/camera.h"

class LightNode: public A_ShadingNode {
public:
    static const std::string vertex_path;
    static const std::string fragment_path;

    LightNode();
    virtual ~LightNode();

    virtual void draw(GeometryBuffer *buffer, const DataBase *, RenderBuffer *render);

private:
    Shader *shader_;
};

#endif // LIGHTNODE_H
