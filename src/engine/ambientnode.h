#ifndef AMBIENTNODE_H
#define AMBIENTNODE_H

#include <string>

#include "a_pipelinenode.h"
#include "src/data_class/camera.h"

class AmbientNode : public A_ShadingNode {
public:
    static const std::string vertex_path;
    static const std::string fragment_path;

    AmbientNode();
    virtual ~AmbientNode();

    virtual void draw(GeometryBuffer *buffer, const DataBase *, RenderBuffer *render);

private:
    Shader *shader_;
};

#endif //AMBIENTNODE_H
