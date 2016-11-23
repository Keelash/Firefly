#ifndef OPENGLTEXTURE_H
#define OPENGLTEXTURE_H

#include <QOpenGLFunctions_3_3_Core>

class OpenGlTexture : protected QOpenGLFunctions_3_3_Core {
public:
    OpenGlTexture(const char* file);
    OpenGlTexture(int width, int height, GLint internalFormat, GLenum format, GLenum type);
    virtual ~OpenGlTexture();

    inline bool isValid() { return this->texid_ != 0; }

    void bindTexture();
    void unbindTexture();
    void bindAsActiveTexture(GLuint pos);

    GLuint getTextureId() { return this->texid_; }

private:
    void createFromFile(const char* path);

    GLuint texid_;
};

#endif // TEXTURE_H
