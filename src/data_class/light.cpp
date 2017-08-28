#include "light.h"

Light::Light(glm::vec3 position, float temperature, float intensity) :
    position_(position), colour_hue_(RGBfromTemp(temperature)), intensity_(intensity)
{

}

Light::Light(glm::vec3 position, glm::vec3 colour, float intensity) :
    position_(position), colour_hue_(colour), intensity_(intensity)
{

}

glm::vec3 Light::RGBfromTemp(float temperature) {
    //The algorithm was taken from : http://www.zombieprototypes.com/?p=210
    glm::vec3 rgb_value(255.0);
    float x;

    //R calculation
    if(temperature >= 6600.0f) {
        x = (temperature/100.0f) - 55.0f;
        rgb_value[0] = 351.97f + 0.11f*x +  -40.25f*glm::log(x);
    }

    //G calculation
    if(temperature <= 1000.0f)
        rgb_value[1] = 0.0f;
    else if(temperature > 1000.0f && temperature < 6600.0f) {
        x = (temperature/100.0f) - 2.0f;
        rgb_value[1] = -155.25f + -0.44f*x + 104.49*glm::log(x);
    }
    else if(temperature >= 6600.0f) {
        x = (temperature/100.0f) - 50.0f;
        rgb_value[1] = 325.45 + 0.08*x + -28.08*glm::log(x);
    }

    //B calculation
    if(temperature <= 2000.0f) {
        rgb_value[2] = 0.0f;
    }
    else if(temperature > 2000.0f && temperature < 6600.0f) {
        x = (temperature/100.0f) - 10.0f;
        rgb_value[2] = -254.77 + 0.83*x + 115.68*glm::log(x);
    }

    return rgb_value / glm::vec3(255.0);
}

void Light::bindLight(Shader *shader, glm::mat4 transform) const {
    glm::vec4 position = transform * glm::vec4(this->position_, 1.0f);

    shader->bindShader();

    shader->setUniformLocation("light_position", position);
    shader->setUniformLocation("light_colour", this->colour_hue_);
    shader->setUniformLocation("light_intensity", this->intensity_);
}
