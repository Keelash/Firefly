#ifndef SHADER_H
#define SHADER_H

#include "opengl_object/opengl_shader.h"
#include "shader_code.h"

class Shader : public OpenGlShader {
public:
    Shader(ShaderCode &code)
        : OpenGlShader(code.getVertexCode(), code.getFragmentCode()) {
    }
    virtual ~Shader() {  }
};

#endif // SHADER_H
