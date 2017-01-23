#ifndef FRAMEBUFFER_H
#define FRAMEBUFFER_H

#include "opengl_object/opengl_framebuffer.h"
#include "texture.h"

typedef A_OpenGlFramebuffer A_Framebuffer;
typedef OpenGlFramebufferObject FramebufferObject;
typedef OpenGlScreenFramebuffer ScreenFramebuffer;

class RenderBuffer {
public:
    RenderBuffer(int width, int height) : framebuffer_(width, height) {
        this->framebuffer_.addTextureAsOutput(0, GL_RGBA16F, GL_RGBA, GL_FLOAT);
        this->framebuffer_.addTextureAsOutput(1, GL_RGBA16F, GL_RGBA, GL_FLOAT);
    }

    ~RenderBuffer() {  }

    A_Framebuffer* getFrameBuffer(){ return &this->framebuffer_; }

    Texture* getRenderTexture() { return this->framebuffer_.getTexture(0); }
    Texture* getBrightTexture() { return this->framebuffer_.getTexture(1); }

private:
    FramebufferObject framebuffer_;
};

enum F_TexType {
    F_TEXTURE_CR, F_TEXTURE_NM, F_TEXTURE_PR, F_NB_TEXTURE
};

class GeometryBuffer {
public:
    GeometryBuffer(int width, int height) : framebuffer_(width, height) {
        this->framebuffer_.addTextureAsOutput(0, GL_RGBA, GL_RGBA, GL_UNSIGNED_BYTE);
        this->framebuffer_.addTextureAsOutput(1, GL_RGBA16F, GL_RGBA, GL_FLOAT);
        this->framebuffer_.addTextureAsOutput(2, GL_RGBA16F, GL_RGBA, GL_FLOAT);
        this->framebuffer_.addRBO(GL_DEPTH24_STENCIL8);
    }
    ~GeometryBuffer() {  }

    inline Texture* getTexture(F_TexType type) { return this->framebuffer_.getTexture(type); }
    inline A_Framebuffer* getFramebuffer() { return &this->framebuffer_; }

private:
    FramebufferObject framebuffer_;
};



#endif//FRAMEBUFFER_H
