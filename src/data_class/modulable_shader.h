#ifndef MODULABLE_SHADER
#define MODULABLE_SHADER

#include <map>
#include <string>

#include "src/data_class/shader.h"

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

class Geometry_Shader : public Modular_Shader {
public:
    Geometry_Shader(std::string vert_path, std::string frag_path)
        : vertex_path_(vert_path), fragment_path_(frag_path) {  }
    virtual ~Geometry_Shader() {  }

    virtual void addMod(int key);

private:
    std::string vertex_path_;
    std::string fragment_path_;
};

#endif // MODULABLE_SHADER
