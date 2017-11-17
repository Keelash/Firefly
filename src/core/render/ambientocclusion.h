#ifndef NEW_AMBIENTOCCLUSION_H
#define NEW_AMBIENTOCCLUSION_H

#include <vector>

#include "src/glm_include.h"
#include "src/data_class/framebuffer.h"

class Blurr;
class Shader;
class DataBase;
class Texture;
class Camera;

class N_AmbientOcclusion {
public:
    N_AmbientOcclusion(unsigned int width, unsigned int height);
    ~N_AmbientOcclusion();

    void CalculateAmbientOcclusion(Texture *position, Texture *normal, const Camera *camera);
    Texture* getAOTexture() { return this->result_; }

private:
    int kernelSize_;
    float sampleRadius_;
    float depthBias_;

    std::vector<glm::vec3> sample_;
    std::vector<glm::vec3> noise_;

    Blurr *blurr_;
    Shader* shader_;
    FramebufferObject *framebuffer_;
    Texture* result_;
};

#endif//NEW_AMBIENTOCCLUSION_H
