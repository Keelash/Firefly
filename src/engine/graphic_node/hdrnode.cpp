#include "hdrnode.h"

const std::string SensorNode::vertex_path_ = std::string("./shader/hdr_shader.vert");
const std::string SensorNode::fragment_path_ = std::string("./shader/hdr_shader.frag");

SensorNode::SensorNode(int width, int height):
    A_PostProcessNode(), blurr_(width, height, 3)
{
    this->shader_.loadShader(vertex_path_, fragment_path_);
    this->min_mipMapLevel_ = (int)glm::floor(glm::log2((float)glm::max(width, height)));
    this->brightness_key_ = 1.0f;
}

SensorNode::~SensorNode() {

}

void SensorNode::draw(RenderBuffer *render, DataBase *data) {
    ScreenFramebuffer screen;
    Texture *blurred_bright = this->blurr_.applyEffect(render->getBrightTexture());
    float pixel[4];

    screen.bind();
    screen.disableDepthTest();
    screen.disableBlending();

    render->getRenderTexture()->bindTexture();
        render->getRenderTexture()->generateMipMap();
        render->getRenderTexture()->getPixel(this->min_mipMapLevel_, pixel);
    render->getRenderTexture()->unbindTexture();

    float luminance = pixel[0] * 0.2126f + pixel[1] * 0.7152f + pixel[2] * 0.0722f;
    this->brightness_key_ = (1.03f - 2.0f / (2.0f + glm::log(luminance + 1))) / (luminance+0.001);
    this->brightness_key_ = glm::max(glm::min(1.0f, this->brightness_key_), 0.05f);


    this->shader_.bindShader();
    this->quad_->bind();

        render->getRenderTexture()->bindAsActiveTexture(0);
        this->shader_.setTextureLocation("render_texture", 0);

        blurred_bright->bindAsActiveTexture(1);
        this->shader_.setTextureLocation("bloom_texture", 1);

        this->shader_.setUniformLocation("brightness_key", this->brightness_key_);

        this->quad_->draw();

    this->quad_->unbind();
}
