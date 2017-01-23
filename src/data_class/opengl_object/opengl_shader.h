#ifndef OPENGLSHADER_H
#define OPENGLSHADER_H

#include <string>
#include <QOpenGLFunctions_3_3_Core>

#include "src/glm_include.h"

class OpenGlShader : protected QOpenGLFunctions_3_3_Core {
public:
    OpenGlShader(std::string vertex_shader, std::string fragment_shader);
    OpenGlShader();
    virtual ~OpenGlShader();

    void bindShader();
    void unbindShader();

    void setUniformLocation(const char* name, int value);
    void setUniformLocation(const char* name, float value);
    void setUniformLocation(const char* name, glm::vec2 &value);
    void setUniformLocation(const char* name, glm::vec3 &value);
    void setUniformLocation(const char* name, glm::vec4 &value);
    void setUniformLocation(const char* name, glm::mat4 &mat);
    void setTextureLocation(const char* name, int texUnit);

private:
    GLboolean CompileCode(const GLchar *vShaderCode, const GLchar *fShaderCode);
    GLboolean showError(GLuint shader, GLint op, std::string errorMsg);

    GLuint program_;
};

#endif // OPENGLSHADER_H
