#ifndef OPENGLTEXTURE_H
#define OPENGLTEXTURE_H

#include <QOpenGLFunctions_3_3_Core>

class OpenGlTexture : protected QOpenGLFunctions_3_3_Core {
public:
    OpenGlTexture();
    OpenGlTexture(const OpenGlTexture& other);
    OpenGlTexture(const char* file);
    OpenGlTexture(int width, int height, GLint internalFormat, GLenum format, GLenum type);
    virtual ~OpenGlTexture();

    inline bool isValid() const { return this->texid_ != 0; }

    void bindTexture();
    void unbindTexture();
    void bindAsActiveTexture(GLuint pos);

    void getPixel(int level, float* pixel);
    void generateMipMap();

    unsigned int getWidth() const { return this->width_; }
    unsigned int getHeight() const { return this->height_; }

    GLuint getTextureId() { return this->texid_; }

private:
    void createFromFile(const char* path);

    GLuint texid_;

    unsigned int width_;
    unsigned int height_;
};

#endif // TEXTURE_H
