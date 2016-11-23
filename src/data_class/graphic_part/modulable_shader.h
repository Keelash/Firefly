#ifndef MODULABLE_SHADER
#define MODULABLE_SHADER

#include <map>
#include <string>

#include "src/data_class/graphic_part/shader.h"

class Shader_Mod {
public:
    Shader_Mod(std::string vertex_path, std::string frag_path);
    ~Shader_Mod();

    bool hasKey(int key);

    void addMod(int key);
    Shader *getMod(int key);

private:
    std::string vertex_path_;
    std::string fragment_path_;

    std::map<int, Shader*> shader_var_;
};

#endif // MODULABLE_SHADER
