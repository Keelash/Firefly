#ifndef SCREENRENDER_H
#define SCREENRENDER_H

#include "src/glm_include.h"

class Shader;
class Texture;

class ScreenRender {
public:
    ScreenRender();
    ~ScreenRender();

    void renderTexToScreen(Texture* tex, const glm::ivec2 &res);

private:
    Shader* shader_;
};

#endif//SCREENRENDER_H
