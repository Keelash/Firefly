#ifndef CAMERA_H
#define CAMERA_H

#include "../glm_include.h"

enum Camera_Mode {
    MODE_FPS, MODE_TRACKBALL_H, MODE_TRACKBALL_3D
};

class Camera {
public:
    Camera(Camera_Mode mode = MODE_TRACKBALL_3D,
           glm::vec3 position = glm::vec3(1.0),
           glm::vec3 look_at = glm::vec3(0.0),
           float fov = 80.0,
           float heigth = 600,
           float width = 400,
           float exposure = 1.0f
           );
    ~Camera() { }

    void setMode(Camera_Mode mode) { this->mode_ = mode; }

    glm::mat4& getViewMatrix() { return this->view_; }
    glm::mat4& getProjectionMatrix() { return this->projection_; }

    glm::vec3& getDirection() { return this->direction_; }
    glm::vec3& getPosition() { return this->position_; }
    float getExposure() { return this->exposure_; }

    void resize(float height, float width);

    void translateLocal(glm::vec3 vec);
    void rotateAroundUp(float angle);
    void rotateAroundRight(float angle);
    void zoom(float value);

    static Camera createBaseCamera(int height, int width);

private:
    void createViewMatric();

    Camera_Mode mode_;

    glm::mat4 view_;
    glm::mat4 projection_;

    glm::vec3 position_;
    glm::vec3 direction_;
    glm::vec3 right_;
    glm::vec3 up_;
    float fov_;
    float exposure_;
};

#endif // CAMERA_H
