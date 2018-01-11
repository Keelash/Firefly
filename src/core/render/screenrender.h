#ifndef SCREENRENDER_H
#define SCREENRENDER_H

#include "src/glm_include.h"

class Shader;
class Texture;

class ScreenRender {
public:
    ScreenRender(unsigned int width, unsigned int length);
    ~ScreenRender();

    void renderTexToScreen(Texture* tex);

private:
    unsigned int width_, length_;

    Shader* shader_;
};

#endif//SCREENRENDER_H
