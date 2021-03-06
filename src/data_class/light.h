#ifndef LIGHT_H
#define LIGHT_H

#include <QVariant>

#include "src/glm_include.h"
#include "shader/shader.h"

class Light {
public:
    static glm::vec3 RGBfromTemp(float temp);

    Light(glm::vec3 position = glm::vec3(0.0f), float temperature = 6000.0f, float intensity = 1.0f);
    Light(glm::vec3 position = glm::vec3(0.0f), glm::vec3 colour = glm::vec3(1.0f), float intensity = 1.0f);
    ~Light() {  }

    static unsigned int Type() { return QVariant::Type::UserType + 3; }

    inline void setTemperature(float temperature) {
        this->colour_hue_ = RGBfromTemp(temperature);
    }

    inline void setColour(glm::vec3 &colour) { this->colour_hue_ = colour;  }
    inline glm::vec3& getColour() { return this->colour_hue_; }

    inline void setIntensity(float intensity) { this->intensity_ = intensity; }
    inline float getIntensity() { return this->intensity_; }

    void bindLight(Shader *shader) const;

    virtual void draw(Shader* shader, float timeInSecond = 0.f) { }
private:
    glm::vec3 position_;
    glm::vec3 colour_hue_;
    float intensity_;

    glm::mat4 Wroldtransform_;
};

Q_DECLARE_METATYPE(const Light*)

#endif
