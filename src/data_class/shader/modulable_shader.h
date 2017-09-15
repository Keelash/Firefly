#ifndef MODULABLE_SHADER
#define MODULABLE_SHADER

#include <map>
#include <string>

#include "shader.h"

class ModularShader {
public:
    ModularShader();
    virtual ~ModularShader();

    virtual bool hasKey(int key);

    virtual void addMod(int key, ShaderCode code);
    virtual Shader *getMod(int key);

private:
    std::map<int, Shader*> shader_var_;
};

#endif // MODULABLE_SHADER
