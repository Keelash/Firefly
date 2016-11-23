#include "opengl_shader.h"

#include <iostream>
#include <fstream>
#include <sstream>

OpenGlShader::OpenGlShader(std::string vertexshader_path, std::string fragmentshader_path) {
    this->initializeOpenGLFunctions();

    this->program_ = 0;
    this->define_ = "#version 330 core\n";
    this->loadShader(vertexshader_path, fragmentshader_path);
}

OpenGlShader::OpenGlShader() {
    this->initializeOpenGLFunctions();

    this->program_ = 0;
    this->define_ = "#version 330 core\n";
}

OpenGlShader::~OpenGlShader() {
    glDeleteShader(this->program_);
}

GLboolean OpenGlShader::loadShader(std::string vertexPath, std::string fragmentPath) {
    std::ifstream vertexFile, fragmentFile;
    std::string vertexCode, fragmentCode;

    if(this->program_ != 0) {
        glDeleteShader(this->program_);
    }

    this->program_ = glCreateProgram();

    vertexFile.exceptions(std::ifstream::badbit);
    fragmentFile.exceptions(std::ifstream::badbit);

    try {
        vertexFile.open(vertexPath);
        fragmentFile.open(fragmentPath);

        std::stringstream vertexStream;
        std::stringstream fragmentStream;

        vertexStream << vertexFile.rdbuf();
        fragmentStream << fragmentFile.rdbuf();

        vertexFile.close();
        fragmentFile.close();

        vertexCode = vertexStream.str();
        fragmentCode = fragmentStream.str();
    }
    catch (std::ifstream::failure e) {
        std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
        return GL_FALSE;
    }

    vertexCode.insert(0, this->define_);
    fragmentCode.insert(0, this->define_);

    return this->CompileCode(vertexCode.c_str(), fragmentCode.c_str());
}

void OpenGlShader::addDefine(const char* define) {
    this->define_ += "#define ";
    this->define_ += define;
    this->define_ += '\n';
}

GLboolean OpenGlShader::CompileCode(const GLchar* vShaderCode, const GLchar* fShaderCode) {
    GLuint vertexshader, fragmentshader;
    GLint success;

    //Vertexshader compilation
    vertexshader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexshader, 1, &vShaderCode, NULL);
    glCompileShader(vertexshader);

    glGetShaderiv(vertexshader, GL_COMPILE_STATUS, &success);
    success = this->showError(vertexshader,
                              GL_COMPILE_STATUS,
                              "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n"
                              );
    if (!success) {
        glDeleteShader(vertexshader);
        return success;
    }

    //Fragmentshader compilation
    fragmentshader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentshader, 1, &fShaderCode, NULL);
    glCompileShader(fragmentshader);

    glGetShaderiv(fragmentshader, GL_COMPILE_STATUS, &success);

    success = this->showError(fragmentshader,
                              GL_COMPILE_STATUS,
                              "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n"
                              );
    if (!success) {
        glDeleteShader(vertexshader);
        glDeleteShader(fragmentshader);
        return success;
    }

    //Shader compilation
    glAttachShader(this->program_, vertexshader);
    glAttachShader(this->program_, fragmentshader);
    glLinkProgram(this->program_);

    glDeleteShader(fragmentshader);
    glDeleteShader(vertexshader);

    success = this->showError(this->program_,
                              GL_LINK_STATUS,
                              "ERROR::SHADER::PROGRAM::LINKING_FAILED\n"
                              );

    return success;
}

GLboolean OpenGlShader::showError(GLuint shader, GLint op, std::string errorMsg) {
    GLint success;

    glGetProgramiv(shader, op, &success);
    if (success == GL_FALSE) {
        GLint maxLength = 0;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);

        //The maxLength includes the NULL character
        std::vector<GLchar> infoLog(maxLength);
        glGetShaderInfoLog(shader, maxLength, &maxLength, &infoLog[0]);

        std::cout << errorMsg << &infoLog[0] << std::endl;

        return GL_FALSE;
    }

        return GL_TRUE;
}

void OpenGlShader::bindShader() {
    glUseProgram(this->program_);
}

void OpenGlShader::unbindShader() {
    glUseProgram(0);
}

void OpenGlShader::setUniformLocation(const char *name, int value) {
    glUniform1i(glGetUniformLocation(this->program_, name), value);
}

void OpenGlShader::setUniformLocation(const char *name, float value) {
    glUniform1f(glGetUniformLocation(this->program_, name), value);
}

void OpenGlShader::setUniformLocation(const char *name, glm::vec2 &value) {
    glUniform2fv(glGetUniformLocation(this->program_, name), 1, glm::value_ptr(value));
}

void OpenGlShader::setUniformLocation(const char *name, glm::vec3 &value) {
    glUniform3fv(glGetUniformLocation(this->program_, name), 1, glm::value_ptr(value));
}

void OpenGlShader::setUniformLocation(const char *name, glm::vec4 &value) {
    glUniform4fv(glGetUniformLocation(this->program_, name), 1,  glm::value_ptr(value));
}

void OpenGlShader::setTextureLocation(const char* name, int texUnit){
    glUniform1i(glGetUniformLocation(this->program_, name), texUnit);
}

void OpenGlShader::setUniformLocation(const char* name, glm::mat4 &mat){
    glUniformMatrix4fv(glGetUniformLocation(this->program_, name), 1, GL_FALSE, glm::value_ptr(mat));
}
