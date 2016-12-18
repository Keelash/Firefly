#include <iostream>

#include "rendernode.h"

const std::string RenderNode::vertex_path = std::string("./shader/scene_shader.vert");
const std::string RenderNode::fragment_path = std::string("./shader/scene_shader.frag");

RenderNode::RenderNode(): A_GeometricNode(), shaders_(vertex_path, fragment_path)
{

}

RenderNode::~RenderNode() {

}

void RenderNode::drawGeometry(GeometryBuffer *gbuffer, DataBase *data) {
    Camera &camera = data->getCamera();

    gbuffer->getFramebuffer()->bind();
    gbuffer->getFramebuffer()->clear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    gbuffer->getFramebuffer()->disableBlending();
    gbuffer->getFramebuffer()->enableDepthTest();

    data->getScene().draw(&this->shaders_, camera.getViewMatrix(), camera.getProjectionMatrix());
}

