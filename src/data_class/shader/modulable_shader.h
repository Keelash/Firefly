#ifndef MODULABLE_SHADER
#define MODULABLE_SHADER

#include <map>
#include <string>

#include "shader.h"

class Modular_Shader {
public:
    Modular_Shader() {  }
    virtual ~Modular_Shader();

    virtual bool hasKey(int key);

    virtual void addMod(int key, ShaderCode code);
    virtual Shader *getMod(int key);

private:
    std::map<int, Shader*> shader_var_;
};

class GeometryShader : public Modular_Shader {
public:
    GeometryShader(std::string vert_path, std::string frag_path)
        : vertex_path_(vert_path), fragment_path_(frag_path) {  }
    virtual ~GeometryShader() {  }

    virtual void addMod(int key);

private:
    std::string vertex_path_;
    std::string fragment_path_;
};

#endif // MODULABLE_SHADER
