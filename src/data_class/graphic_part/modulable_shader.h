#ifndef MODULABLE_SHADER
#define MODULABLE_SHADER

#include <map>
#include <string>

#include "src/data_class/graphic_part/shader.h"

class Module_Shader {
public:

private:
    std::string shader_mod_;
    unsigned int id_;
};

class Modular_Shader {
public:
    Modular_Shader(std::string vertex_path, std::string frag_path);
    ~Modular_Shader();

    bool hasKey(int key);

    void addMod(int key);
    Shader *getMod(int key);

private:
    std::string vertex_path_;
    std::string fragment_path_;

    std::map<int, Shader*> shader_var_;
};

#endif // MODULABLE_SHADER
