#include "opengl_texture.h"

#include <iostream>
#include <QImage>

OpenGlTexture::OpenGlTexture(const char* file) {
    this->initializeOpenGLFunctions();

    this->createFromFile(file);
}

OpenGlTexture::OpenGlTexture(int width, int height, GLint internalFormat, GLenum format, GLenum type) {
    this->initializeOpenGLFunctions();

    glGenTextures(1, &this->texid_);
    glBindTexture(GL_TEXTURE_2D, this->texid_);
        glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, width, height, 0, format, type, NULL);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glBindTexture(GL_TEXTURE_2D, 0);
}

OpenGlTexture::~OpenGlTexture() {
    glDeleteTextures(1, (GLuint*)&(this->texid_));
}

void OpenGlTexture::bindTexture() {
    glBindTexture(GL_TEXTURE_2D, this->texid_);
}

void OpenGlTexture::unbindTexture() {
    glBindTexture(GL_TEXTURE_2D, 0);
}

void OpenGlTexture::bindAsActiveTexture(GLuint pos) {
    glActiveTexture(GL_TEXTURE0 + pos);
    glBindTexture(GL_TEXTURE_2D, this->texid_);
}

void OpenGlTexture::generateMipMap() {
    glGenerateMipmap(GL_TEXTURE_2D);
}

void OpenGlTexture::getPixel(int level, float* pixel) {
    glGetTexImage(GL_TEXTURE_2D, level, GL_RGBA, GL_FLOAT, pixel);
}

void OpenGlTexture::createFromFile(const char* file) {
    GLuint texture;
    QImage image(file);
    image.convertToFormat(QImage::Format_RGB888);



    if(!image.isNull()) {
        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image.width(), image.height(), 0, GL_BGRA, GL_UNSIGNED_BYTE, image.bits());

        glGenerateMipmap(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, 0);

        this->texid_ = texture;
    }
    else {
        std::cerr << "[TEXTURE] Error when loading: " << file << std::endl;
        this->texid_ = 0;
    }
}
