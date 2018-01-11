#ifndef OPENGLFRAMEBUFFER
#define OPENGLFRAMEBUFFER

#include <QOpenGLFunctions_3_3_Core>

#include "opengl_texture.h"

class A_OpenGlFramebuffer : protected QOpenGLFunctions_3_3_Core {
public:
    A_OpenGlFramebuffer() { this->initializeOpenGLFunctions(); }

    void enableBlending();
    void disableBlending();
    void setBlendingFunction(GLenum sfactor, GLenum dfactor);

    void enableDepthTest();
    void disableDepthTest();
    void setDepthTestFunction(GLenum func);

    void enableDepthWrite();
    void disableDepthWrite();

    void setPolygonMode(GLenum mode);

    void clear(GLbitfield mask);
    virtual void setViewport(int x, int y, int width, int height);
    void getViewport(int &x, int &y, int &width, int &height);

    virtual void bind() = 0;
};

class OpenGlScreenFramebuffer : public A_OpenGlFramebuffer {
public:
    virtual void bind();
};

class OpenGlFramebufferObject : public A_OpenGlFramebuffer {
public:
    OpenGlFramebufferObject(int width, int height);
    virtual ~OpenGlFramebufferObject();

    inline OpenGlTexture* getTexture(unsigned int pos) { return this->attachments_[pos]; }

    int addTextureAsOutput(int attachment, GLint internalFormat, GLenum format, GLenum type);
    void addRBO(GLenum format);

    void setFullTextureViewport();

    virtual void bind();
    void unbind();

    void blitFramebuffer(OpenGlFramebufferObject &output,
                         int x1, int y1, int width1, int height1,
                         int x2, int y2, int width2, int height2,
                         GLbitfield mask);

private:
    int width_;
    int height_;

    GLuint framebuffer_;
    GLuint rbo_;

    std::vector<GLuint> color_attachements_;
    std::vector<OpenGlTexture*> attachments_;
};

#endif//OPENGLFRAMEBUFFER
