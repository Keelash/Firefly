#include "shader_code.h"

#include <iostream>
#include <fstream>
#include <sstream>

ShaderCode::ShaderCode(const std::string &vertex, const std::string &fragment)
    : vertex_code_(vertex), fragment_code_(fragment) {

    this->define_ = "#version 330 core \n";
}

ShaderCode::ShaderCode() {
    this->define_ = "#version 330 core \n";
}

void ShaderCode::addDefine(std::string define) {
    this->define_ += "#define " + define + " \n";
}

void ShaderCode::createFromFile(std::string vertex_path, std::string fragment_path) {
    std::ifstream vertexFile, fragmentFile;

    vertexFile.exceptions(std::ifstream::badbit);
    fragmentFile.exceptions(std::ifstream::badbit);

    try {
        vertexFile.open(vertex_path);
        fragmentFile.open(fragment_path);

        std::stringstream vertexStream;
        std::stringstream fragmentStream;

        vertexStream << vertexFile.rdbuf();
        fragmentStream << fragmentFile.rdbuf();

        vertexFile.close();
        fragmentFile.close();

        this->vertex_code_ = vertexStream.str();
        this->fragment_code_ = fragmentStream.str();
    }
    catch (std::ifstream::failure e) {
        std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
    }
}
