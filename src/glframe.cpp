#include "glframe.h"

#include "data_class/model.h"
#include "data_class/framebuffer.h"

#include "src/graphic_node/output/graphicoutput.h"

GLFrame::GLFrame(QWidget* parent): QGLWidget(parent){
    QGLFormat format;

    format.setVersion(3, 3);
    format.setProfile(QGLFormat::CoreProfile);
    format.setSampleBuffers(true);
    this->setFormat(format);

    this->setFixedSize(600, 400);
    this->setFocus();

    this->timer_ = new QTimer(this);
    this->connect(this->timer_, SIGNAL(timeout()), this, SLOT(update()));
    this->timer_->start(20);
}

GLFrame::~GLFrame() {

}

void GLFrame::initializeGL() {
    //ScreenFramebuffer screen;

    //screen.bind();
    //screen.setViewport(0, 0, 600, 400);
    //screen.clear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    this->graph_->addNode(new GraphicOutput(this->graph_));
}

void GLFrame::resizeGL(int w, int h) {

}

void GLFrame::paintGL() {
    if(data_ && graph_) {
        Camera c = *this->data_->getCamera();

        c.rotateAroundUp(0.005);
        this->data_->setCamera(c);

        this->graph_->updateGraph();
    }
}

