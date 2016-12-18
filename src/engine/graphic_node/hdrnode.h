#ifndef SENSORNODE_H
#define SENSORNODE_H

#include <string>

#include "a_pipelinenode.h"
#include "blurr_effect.h"

class SensorNode : public A_PostProcessNode {
public:
    static const std::string vertex_path_;
    static const std::string fragment_path_;

    SensorNode(int width, int height);
    ~SensorNode();

    void draw(RenderBuffer *render, DataBase *data);
private:
    Shader *shader_;
    BlurrEffect blurr_;

    float min_mipMapLevel_;
    float brightness_key_;
};

#endif //SENSORNODE_H
