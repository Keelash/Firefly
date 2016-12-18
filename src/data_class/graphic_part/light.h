#ifndef LIGHT_H
#define LIGHT_H

#include "src/glm_include.h"

#include "bindable.h"

class Light {
public:
    static glm::vec3 RGBfromTemp(float temp);

    Light(int id, glm::vec3 position, float temperature = 6000.0f, float intensity = 1.0f);
    Light(int id, glm::vec3 position, glm::vec3 colour = glm::vec3(1.0f), float intensity = 1.0f);
    ~Light() {  }

    inline void setTemperature(float temperature) {
        this->colour_hue_ = RGBfromTemp(temperature);
    }

    inline void setColour(glm::vec3 &colour) { this->colour_hue_ = colour;  }
    inline glm::vec3& getColour() { return this->colour_hue_; }

    inline void setIntensity(float intensity) { this->intensity_ = intensity; }
    inline float getIntensity() { return this->intensity_; }

    inline void setPosition(glm::vec3 &position) { this->position_ = position; }
    inline glm::vec3& getPosition() { return this->position_; }

    void bindLight(Shader *shader, glm::mat4 transform);
private:
    int id_;

    glm::vec3 position_;
    glm::vec3 colour_hue_;
    float intensity_;
};

#endif
