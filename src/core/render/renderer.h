#ifndef RENDERER_H
#define RENDERER_H

#include <vector>

#include "src/data_class/texture.h"
#include "src/data_class/framebuffer.h"

class DataBase;
class Shader;
class N_AmbientOcclusion;

class Renderer {
public:
    Renderer(unsigned int width, unsigned int height);
    ~Renderer();

    void drawScene(DataBase* data, float timeInSecond);

    Texture* getPosition();
    Texture* getNormal();
    Texture* getRender();
    Texture* getAo();

private:
    FramebufferObject *framebuffer_;

    Shader *zPassShader_;
    Shader *renderShader_;

    N_AmbientOcclusion *ambient_;
};

#endif//RENDERER_H
