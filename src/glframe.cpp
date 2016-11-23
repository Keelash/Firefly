#include "glframe.h"

#include <QGLFormat>
#include <iostream>

#include "data_class/data_maker/procedural_landscape.h"
#include "src/data_class/loader.h"

#include "data_class/camera.h"

GLFrame::GLFrame(QWidget *parent): QGLWidget(parent) {
    QGLFormat glFormat;

    glFormat.setVersion(3, 3);
    glFormat.setProfile(QGLFormat::CoreProfile);
    glFormat.setSampleBuffers(true);
    this->setFormat(glFormat);

    this->setFixedSize(800, 600);
    this->setFocus();

    this->timer_ = new QTimer(this);
    this->connect(this->timer_, SIGNAL(timeout()), this, SLOT(update()));
    this->timer_->start(20);
}

GLFrame::~GLFrame() {
    delete this->timer_;
    delete this->engine_g;
    delete this->engine_i;
    delete this->data_base_;

}

void GLFrame::initializeGL() {
    glm::mat4 *matrix = new glm::mat4(1.0);

    this->data_base_ = new DataBase();
    this->engine_g = new Engine_Graphic(this, this->data_base_);
    this->engine_i = new Engine_Interaction(this, this->data_base_);


    //Voire pour jeter tout cela dans un fichier qui creer une scene de base.
    Camera c = Camera::createBaseCamera(this->height(), this->width());
    this->data_base_->setCamera(c);

    Procedural_Landscape::CreateLandscape(this->data_base_, 128);
    this->data_base_->addLight(glm::vec3(1.0), glm::vec3(1.0, 0.0, 0.0), 0.5f);
    this->data_base_->addLight(glm::vec3(1.0, -1.0, 0.0), glm::vec3(0.0, 1.0, 0.0), 0.75f);
}

void GLFrame::paintGL() {
    this->engine_i->update();
    this->engine_g->update();
}

void GLFrame::resizeGL(int w, int h) {
    this->engine_g->resize(w, h);
    this->data_base_->getCamera().resize(h, w);
}

void GLFrame::keyPressEvent(QKeyEvent *e) {
    this->engine_i->keyboardEventHandler(e);
}

void GLFrame::mousePressEvent(QMouseEvent *e) {

    if(e->button() == Qt::LeftButton) {
        this->engine_i->mousePressLeftEventHandler();
    }
    else {
        this->engine_i->mousePressRightEventHandler();
    }
}

void GLFrame::mouseReleaseEvent(QMouseEvent *e) {
    if(e->button() == Qt::LeftButton) {
        this->engine_i->mouseReleaseLeftEventHandler();
    }
    else {
        this->engine_i->mouseReleaseRightEventHandler();
    }
}

bool GLFrame::setEnvmap(const char* path) {
    this->data_base_->setEnvMap(path);

    return this->data_base_->getEnvMap()->isValid();
}

bool GLFrame::loadFile(std::string path) {
    Loader loader;

    this->data_base_->clear();
    return loader.loadScene(path, this->data_base_);
}


