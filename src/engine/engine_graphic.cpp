#include "engine_graphic.h"

#include <iostream>

#include "src/glm_include.h"

#include "src/data_class/graphic_part/opengl_object/opengl_framebuffer.h"

Engine_Graphic::Engine_Graphic(QGLWidget *parent, DataBase *data):
    Engine_Abstract(parent), data_base_(data)
{
    ScreenFramebuffer screen;

    int width = parent->width();
    int height = parent->height();

    this->gbuffer_ = new GeometryBuffer(width, height);
    this->renderbuffer_ = new RenderBuffer(width, height);

    this->scene_rendering_node_ = new RenderNode();
    this->ambient_node_ = new AmbientNode();
    this->light_node_ = new LightNode();
    this->sensor_node_ = new SensorNode(width, height);

    screen.setViewport(0, 0, width, height);
}

Engine_Graphic::~Engine_Graphic() {
    delete this->gbuffer_;
    delete this->renderbuffer_;

    delete this->scene_rendering_node_;
    delete this->light_node_;
    delete this->ambient_node_;
    delete this->sensor_node_;
}

void Engine_Graphic::reloadShader() {
    //this->scene_rendering_node_->reloadShader();
    this->ambient_node_->reloadShader();
    this->light_node_->reloadShader();
}

void  Engine_Graphic::resize(int width, int height) {
    ScreenFramebuffer screen;

    screen.setViewport(0, 0, width, height);
}

void Engine_Graphic::update() {

    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    this->scene_rendering_node_->drawGeometry(this->gbuffer_, this->data_base_);
    //glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    this->ambient_node_->draw(this->gbuffer_, this->data_base_, this->renderbuffer_);
    this->light_node_->draw(this->gbuffer_, this->data_base_, this->renderbuffer_);

    this->sensor_node_->draw(this->renderbuffer_, this->data_base_);
}
