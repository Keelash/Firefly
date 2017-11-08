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

    void setUniformLocation(const char* name, const int value);
    void setUniformLocation(const char* name, const float value);
    void setUniformLocation(const char* name, const glm::vec2 &value);
    void setUniformLocation(const char* name, const glm::vec3 &value);
    void setUniformLocation(const char* name, const std::vector<glm::vec3> &vec);
    void setUniformLocation(const char* name, const glm::vec4 &value);
    void setUniformLocation(const char* name, const std::vector<glm::mat4> &mats);
    void setUniformLocation(const char* name, const glm::mat4 &mat);
    void setTextureLocation(const char* name, const int texUnit);

private:
    GLboolean CompileCode(const GLchar *vShaderCode, const GLchar *fShaderCode);
    GLboolean showError(GLuint shader, GLint op, std::string errorMsg);

    GLuint program_;
};

#endif // OPENGLSHADER_H
