#include "hdrnode.h"

const std::string SensorNode::vertex_path_ = std::string("./shader/hdr_shader.vert");
const std::string SensorNode::fragment_path_ = std::string("./shader/hdr_shader.frag");

SensorNode::SensorNode(int width, int heihgt):
    A_PostProcessNode(), shader_(vertex_path_, fragment_path_), blurr_(width, heihgt, 1)
{

}

SensorNode::~SensorNode() {

}

void SensorNode::draw(RenderBuffer *render, DataBase *data) {
    ScreenFramebuffer screen;
    Texture *blurred_bright = this->blurr_.applyEffect(render->getBrightTexture());

    screen.bind();
    screen.disableDepthTest();
    screen.disableBlending();

    this->shader_.bindShader();
    this->shader_.setUniformLocation("exposure", data->getCamera().getExposure());

    this->quad_->bind();

        render->getRenderTexture()->bindAsActiveTexture(0);
        this->shader_.setTextureLocation("render_texture", 0);

        blurred_bright->bindAsActiveTexture(1);
        this->shader_.setTextureLocation("bloom_texture", 1);

        this->quad_->draw();

    this->quad_->unbind();
}
