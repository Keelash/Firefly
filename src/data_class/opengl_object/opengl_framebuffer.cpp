#include "opengl_framebuffer.h"

#include <iostream>

void A_OpenGlFramebuffer::enableBlending() {
    glEnable(GL_BLEND);
}

void A_OpenGlFramebuffer::disableBlending() {
    glDisable(GL_BLEND);
}

void A_OpenGlFramebuffer::setBlendingFunction(GLenum sfactor, GLenum dfactor) {
        glBlendFunc(sfactor, dfactor);
}

void A_OpenGlFramebuffer::enableDepthTest() {
    glEnable(GL_DEPTH_TEST);
}

void A_OpenGlFramebuffer::disableDepthTest() {
    glDisable(GL_DEPTH_TEST);
}

void A_OpenGlFramebuffer::setDepthTestFunction(GLenum func) {
    glDepthFunc(func);
}

void A_OpenGlFramebuffer::enableDepthWrite() {
    glDepthMask(GL_TRUE);
}

void A_OpenGlFramebuffer::disableDepthWrite() {
    glDepthMask(GL_FALSE);
}

void A_OpenGlFramebuffer::clear(GLbitfield mask) {
    glClear(mask);
}

void A_OpenGlFramebuffer::setPolygonMode(GLenum mode) {
    glPolygonMode(GL_FRONT_AND_BACK, mode);
}

void A_OpenGlFramebuffer::setViewport(int x, int y, int width, int height) {
    glViewport(x, y, width, height);
}

void A_OpenGlFramebuffer::getViewport(int &x, int &y, int &width, int &height) {
    GLint m_viewport[4];
    glGetIntegerv(GL_VIEWPORT, m_viewport);

    x = m_viewport[0]; y = m_viewport[1];
    width = m_viewport[2]; height = m_viewport[3];
}

void OpenGlScreenFramebuffer::bind() {
     glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

OpenGlFramebufferObject::OpenGlFramebufferObject(int width, int height)
    :A_OpenGlFramebuffer(), rbo_(0), width_(width), height_(height)
{
    glGenFramebuffers(1, &(this->framebuffer_));
}

OpenGlFramebufferObject::~OpenGlFramebufferObject() {
    glDeleteFramebuffers(1, &(this->framebuffer_));

    if (this->rbo_ != 0)
        glDeleteRenderbuffers(1, &(this->rbo_));
}

int OpenGlFramebufferObject::addTextureAsOutput(int attachment, GLint internalFormat, GLenum format, GLenum type) {
    OpenGlTexture *tex = new OpenGlTexture(this->width_, this->height_, internalFormat, format, type);
    GLuint c_att = GL_COLOR_ATTACHMENT0 + attachment;

    this->bind();
        tex->bindTexture();
            glFramebufferTexture2D(GL_FRAMEBUFFER, c_att, GL_TEXTURE_2D, tex->getTextureId(), 0);
        tex->unbindTexture();

        this->color_attachements_.push_back(c_att);
        this->attachments_.push_back(tex);

        glDrawBuffers(this->color_attachements_.size(), &this->color_attachements_[0]);

        if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
            std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << std::endl;
    this->unbind();

    return this->attachments_.size();
}

void OpenGlFramebufferObject::addRBO(GLenum format) {
    GLuint rbo;

    this->bind();

    glGenRenderbuffers(1, &rbo);
    glBindRenderbuffer(GL_RENDERBUFFER, rbo);
    glRenderbufferStorage(GL_RENDERBUFFER, format, this->width_, this->height_);
    glBindRenderbuffer(GL_RENDERBUFFER, 0);

    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo);

    this->rbo_ = rbo;

    if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << std::endl;

    this->unbind();
}

void OpenGlFramebufferObject::setFullTextureViewport() {
    this->setViewport(0, 0, width_, height_);
}



void OpenGlFramebufferObject::bind() {
    glBindFramebuffer(GL_FRAMEBUFFER, this->framebuffer_);
}

void OpenGlFramebufferObject::unbind() {
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void OpenGlFramebufferObject::blitFramebuffer(OpenGlFramebufferObject &output,
                                          int x1, int y1, int width1, int height1,
                                          int x2, int y2, int width2, int height2,
                                          GLbitfield mask)
{
    glBindFramebuffer(GL_READ_FRAMEBUFFER, this->framebuffer_);
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, output.framebuffer_);
    glBlitFramebuffer(x1, y1, width1, height1, x2, y2, width2, height2, mask, GL_NEAREST);
    glBindFramebuffer(GL_READ_FRAMEBUFFER, 0);
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
}
