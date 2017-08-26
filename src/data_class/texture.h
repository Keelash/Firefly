#ifndef TEXTURE_H
#define TEXTURE_H

#include <QVariant>

#include "opengl_object/opengl_texture.h"

class Texture : public OpenGlTexture {
public:
    Texture() : OpenGlTexture() {  }
    Texture(const Texture& other) : OpenGlTexture(other) {  }
    Texture(const char* file) : OpenGlTexture(file) {  }
    Texture(int width, int height, GLint internalFormat, GLenum format, GLenum type) :
        OpenGlTexture(width, height, internalFormat, format, type) {  }

    ~Texture() {  }

    static unsigned int Type() { return QVariant::Type::UserType + 1; }
};

Q_DECLARE_METATYPE(Texture*)

#endif // TEXTURE_H

