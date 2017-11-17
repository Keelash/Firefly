#ifndef RENDERER_H
#define RENDERER_H

#include <vector>

#include "src/data_class/texture.h"
#include "src/data_class/framebuffer.h"

class DataBase;
class Shader;
class N_AmbientOcclusion;
class A_RenderNode;

class Renderer {
public:
    Renderer(unsigned int width, unsigned int height);
    ~Renderer();

    void drawScene(DataBase* data, float timeInSecond);

    void addNode(A_RenderNode* node) { this->nodes_.push_back(node); }

    Texture* getPosition();
    Texture* getNormal();
    Texture* getRender();
    Texture* getAo();

private:
    FramebufferObject *framebuffer_;

    Shader *zPassShader_;
    Shader *renderShader_;

    N_AmbientOcclusion *ambient_;

    std::vector<A_RenderNode*> nodes_;
};

#endif//RENDERER_H
