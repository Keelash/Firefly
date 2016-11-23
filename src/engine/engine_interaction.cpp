#include "engine_interaction.h"

#include "src/data_class/camera.h"
#include "src/glframe.h"

Engine_Interaction::Engine_Interaction(QGLWidget *parent, DataBase *data):
    Engine_Abstract(parent), moveCamera_(false), zoomCamera_(false), data_base_(data)
{

}

void Engine_Interaction::keyboardEventHandler(QKeyEvent *e) {
    Camera &camera = this->data_base_->getCamera();

    switch(e->key()) {
        case Qt::Key_Right:
            camera.translateLocal(glm::vec3(1.0, 0.0, 0.0));
            break;
        case Qt::Key_Left:
            camera.translateLocal(glm::vec3(-1.0, 0.0, 0.0));
            break;
        case Qt::Key_Escape:
            break;
    }
}

void Engine_Interaction::mousePressLeftEventHandler() {
    this->moveCamera_ = true;
}

void Engine_Interaction::mousePressRightEventHandler() {
    this->zoomCamera_ = true;
}

void Engine_Interaction::mouseReleaseLeftEventHandler() {
    this->moveCamera_ = false;
}

void Engine_Interaction::mouseReleaseRightEventHandler() {
    this->zoomCamera_ = false;
}

void Engine_Interaction::update() {
    Camera &camera = this->data_base_->getCamera();

    if(this->parent_ != nullptr) {
        QPoint p = this->parent_->mapFromGlobal(this->parent_->cursor().pos());
        int midX = parent_->width()/2;
        int midY = parent_->height()/2;
        float diffX = (p.x() - midX) * 0.0005;
        float diffY = (p.y() - midY) * 0.0005;

        if (this->moveCamera_) {
            camera.rotateAroundUp(diffX);
            camera.rotateAroundRight(diffY);
        }

        if (this->zoomCamera_) {
           glm::vec2 diff(diffX, diffY);

           if(p.x() > midX) {
                camera.zoom(glm::length(diff));
           }
           else {
               camera.zoom(-1.0f * glm::length(diff));
           }
        }
    }
}

