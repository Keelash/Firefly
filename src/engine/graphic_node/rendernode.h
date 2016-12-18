#ifndef RENDERNODE_H
#define RENDERNODE_H

#include <string>

#include "../../gl_include.h"

#include "src/data_class/scene.h"
#include "src/data_class/camera.h"

#include "a_pipelinenode.h"
#include "src/data_class/graphic_part/modulable_shader.h"
#include "src/data_class/graphic_part/framebuffer.h"


class RenderNode : public A_GeometricNode {
public:
    RenderNode();
    ~RenderNode();

    virtual void drawGeometry(GeometryBuffer *gbuffer, DataBase *data);

    static const std::string vertex_path;
    static const std::string fragment_path;

private:
    Geometry_Shader shaders_;
};

#endif // RENDERNODE_H
