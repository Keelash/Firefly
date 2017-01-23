#ifndef CAMERA_H
#define CAMERA_H

#include "../glm_include.h"

enum Camera_Mode {
    MODE_TRACKBALL_H, MODE_TRACKBALL_3D, MODE_FPS
};

class Camera {
public:
    Camera(Camera_Mode mode = MODE_TRACKBALL_H,
           glm::vec3 position = glm::vec3(1.0),
           glm::vec3 look_at = glm::vec3(0.0),
           float fov = 80.0,
           float heigth = 600,
           float width = 400);
    ~Camera() { }

    void setMode(Camera_Mode mode) { this->mode_ = mode; }

    glm::mat4 getViewMatrix() const { return this->view_; }
    glm::mat4 getProjectionMatrix() const { return this->projection_; }

    glm::vec3 getDirection() const { return this->direction_; }
    glm::vec3 getPosition() const { return this->position_; }
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
};

#endif // CAMERA_H
