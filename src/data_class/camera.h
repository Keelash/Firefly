#ifndef CAMERA_H
#define CAMERA_H

#include <QVariant>

#include "../glm_include.h"

class Camera {
public:
    Camera(glm::vec3 position = glm::vec3(0.0, 0.0, 3.0),
           glm::vec3 look_at = glm::vec3(0.0),
           float fov = 80.0,
           float heigth = 400,
           float width = 600);
    ~Camera() { }

    static unsigned int Type() { return QVariant::Type::UserType + 4; }

    glm::mat4 getViewMatrix() const { return this->view_; }
    glm::mat4 getProjectionMatrix() const { return this->projection_; }

    glm::vec3 getDirection() const { return this->direction_; }
    glm::vec3 getPosition() const { return this->position_; }

    void resize(float width, float height);

    void translateLocal(glm::vec3 vec);
    void rotateAroundUp(float angle);
    void rotateAroundRight(float angle);
    void zoom(float value);

    static Camera createBaseCamera(int height, int width);

private:
    void createViewMatric();

    glm::mat4 view_;
    glm::mat4 projection_;

    glm::vec3 position_;
    glm::vec3 direction_;
    glm::vec3 right_;
    glm::vec3 up_;
    float fov_;
};

Q_DECLARE_METATYPE(const Camera*)

#endif // CAMERA_H
