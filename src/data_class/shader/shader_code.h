#ifndef SHADERCODE_H
#define SHADERCODE_H

#include <string>

class ShaderCode {
public:
    ShaderCode(std::string &vertex, std::string &fragment);
    ShaderCode();
    ~ShaderCode() {  }

    void createFromFile(std::string vertex_path, std::string fragment_path);

    void addDefine(std::string define);

    std::string getVertexCode() { return (this->define_ + this->vertex_code_); }
    std::string getFragmentCode() { return (this->define_ + this->fragment_code_); }

private:
    std::string define_;

    std::string vertex_code_;
    std::string fragment_code_;
};

#endif//SHADERCODE_H
