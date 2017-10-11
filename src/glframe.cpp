#include "glframe.h"

#include <QMouseEvent>
#include <iostream>

#include "data_class/framebuffer.h"

#include "node_widget/node_widget.h"
#include "src/graphic_node/output/graphicoutput.h"
#include "src/graphic_node/getter/meshdata.h"
#include "src/graphic_node/shader/pbrshader.h"

GLFrame::GLFrame(QWidget* parent): QGLWidget(parent){
    QGLFormat format;

    this->graph_ = new nodegraph::NodeGraph(this);
    this->database_ = new DataBase(glm::ivec2(1280, 720), glm::ivec2(this->size().width(), this->size().height()));

    format.setVersion(3, 3);
    format.setProfile(QGLFormat::CoreProfile);
    format.setSampleBuffers(true);
    this->setFormat(format);

    this->setFocus();

    this->timer_ = new QTimer(this);
    this->connect(this->timer_, SIGNAL(timeout()), this, SLOT(update()));
    this->timer_->start(20);

    this->e_timer_ = new QElapsedTimer();
    this->e_timer_->start();
}

GLFrame::~GLFrame() {
    delete this->graph_;
    delete this->extractor_;
    delete this->database_;
}

void GLFrame::initializeGL() {
    ScreenFramebuffer screen;

    screen.bind();
    screen.setViewport(0, 0, RESOLUTION_WIDTH, RESOLUTION_HEIGHT);
    screen.clear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    this->graph_->addNode(new GraphicOutput(this->database_, this->graph_));
    this->extractor_ = new DataExtractor(1280, 720);
    this->database_->addLight(glm::vec3(0.0f), 6000.0f, 0.5f);
}

void GLFrame::resizeGL(int w, int h) {
    ScreenFramebuffer screen;

    screen.bind();
    screen.setViewport(0, 0, w, h);
    screen.clear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    this->database_->windowRes_ = glm::ivec2(w, h);
}

void GLFrame::paintGL() {
    if(database_->hasInstance()) {
        Camera c = *this->database_->getCamera();
        QPoint mouse_pos = QCursor::pos();
        float time = (float)(this->e_timer_->elapsed()) / 1000.0f;

        if (this->state_ == 1) {
            float diffX = (mouse_pos.x() - this->pos_left.x()) * 0.0005;
            float diffY = (mouse_pos.y() - this->pos_left.y()) * 0.0005;

            c.rotateAroundUp(diffX);
            c.rotateAroundRight(diffY);
        }

        if (this->state_ == 2) {
            float diffX = (mouse_pos.x() - this->pos_right.x()) * 0.005;
            float diffY = (mouse_pos.y() - this->pos_right.y()) * 0.005;

            glm::vec2 diff(diffX, diffY);

            if (diffX > 0.0f) {
                c.zoom(glm::length(diff));
            }
            else {
                c.zoom(-1.0f * glm::length(diff));
            }
        }

        this->database_->setCamera(c);
        this->extractor_->extractData(time, this->database_);

        this->graph_->updateGraph();
    }
}

void GLFrame::mousePressEvent(QMouseEvent *e) {
    if(e->button() == Qt::LeftButton) {
        pos_left = QCursor::pos();
        this->state_ = 1;
    }
    else {
        pos_right = QCursor::pos();
        this->state_ = 2;
    }
}

void GLFrame::mouseReleaseEvent(QMouseEvent *e) {
        this->state_ = 0;
}

void GLFrame::on_createMeshDataTrig(bool checked) {
    this->graph_->addNode(new MeshData(this->database_, this->graph_));
}

void GLFrame::on_createPBRShaderTrig(bool checked) {
    this->graph_->addNode(new PBRShader(this->database_, this->graph_));
}
