#include "camera.h"

#include <iostream>

Camera::Camera(glm::vec3 position, glm::vec3 look_at,
               float fov, float heigth, float width) {

    this->projection_ = glm::perspective(fov, width/heigth, 0.1f, 1000.0f);

    this->position_ = position;
    this->direction_ = glm::normalize(look_at - position);
    this->up_ = glm::vec3(0.0, -1.0, 0.0);
    this->right_ = glm::normalize(glm::cross(this->up_, this->direction_));

    this->fov_ = fov;

    createViewMatric();

}

void Camera::resize(float width, float height) {
    this->projection_ = glm::perspective(this->fov_, width/height, 0.1f, 100.0f);
}


void Camera::createViewMatric() {
    this->view_ = glm::lookAt(this->position_, this->position_ + this->direction_, this->up_);
}

void Camera::translateLocal(glm::vec3 vec) {
    this->position_ -= vec[0] * this->right_ + vec[1] * this->up_ + vec[2] * this->direction_;
    createViewMatric();
}

void Camera::zoom(float value) {
    this->position_ += this->direction_ * value;
    createViewMatric();
}

void Camera::rotateAroundUp(float angle) {
    this->direction_ = glm::rotate(this->direction_, angle, this->up_);
    this->right_ = glm::rotate(this->right_, angle, this->up_);
    this->position_ = glm::rotate(this->position_, angle, this->up_);
    createViewMatric();
}

void Camera::rotateAroundRight(float angle) {
    this->direction_ = glm::rotate(this->direction_, angle, this->right_);
    this->position_ = glm::rotate(this->position_, angle, this->right_);
    createViewMatric();
}

Camera Camera::createBaseCamera(int height, int width) {
    return Camera(glm::vec3(0.0, 1.0, -3.0f), glm::vec3(0.0, 0.0, 0.0),
                  45.0f, height, width);
}
