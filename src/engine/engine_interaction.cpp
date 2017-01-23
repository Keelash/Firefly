#include "engine_interaction.h"

#include "src/data_class/camera.h"
#include "src/glframe.h"

Engine_Interaction::Engine_Interaction():
    moveCamera_(false), zoomCamera_(false)
{

}

void Engine_Interaction::mousePressLeftEventHandler() {
    this->pos_onLeftPressed = QCursor::pos();
    this->moveCamera_ = true;
}

void Engine_Interaction::mousePressRightEventHandler() {
    this->pos_onRightPressed = QCursor::pos();
    this->zoomCamera_ = true;
}

void Engine_Interaction::mouseReleaseLeftEventHandler() {
    this->moveCamera_ = false;
}

void Engine_Interaction::mouseReleaseRightEventHandler() {
    this->zoomCamera_ = false;
}

void Engine_Interaction::update(DataBase *data) {
    Camera camera = *data->getCamera();
    QPoint mouse_pos = QCursor::pos();

    if (this->moveCamera_) {
        float diffX = (mouse_pos.x() - this->pos_onLeftPressed.x()) * 0.0005;
        float diffY = (mouse_pos.y() - this->pos_onLeftPressed.y()) * 0.0005;

        camera.rotateAroundUp(diffX);
        camera.rotateAroundRight(diffY);
    }

    if (this->zoomCamera_) {
        float diffX = (mouse_pos.x() - this->pos_onRightPressed.x()) * 0.0005;
        float diffY = (mouse_pos.y() - this->pos_onRightPressed.y()) * 0.0005;

        glm::vec2 diff(diffX, diffY);

        if (diffX > 0.0f) {
            camera.zoom(glm::length(diff));
        }
        else {
            camera.zoom(-1.0f * glm::length(diff));
        }
    }

    data->setCamera(camera);
}

