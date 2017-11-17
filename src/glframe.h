#ifndef GLFRAME_H
#define GLFRAME_H

#include <QtOpenGL/QGLWidget>
#include <QTimer>
#include <QElapsedTimer>
#include <QObject>
#include <iostream>

#include "data_class/database.h"
#include "node_widget/node_widget.h"
#include "data_class/shader/modulable_shader.h"

#include "core/render/renderer.h"
#include "core/postprocess/node/input/a_inputnode.h"

#define RESOLUTION_WIDTH 600
#define RESOLUTION_HEIGHT 400

class GLFrame : public QGLWidget {
    Q_OBJECT
public:
    GLFrame(QWidget* parent = nullptr);
    virtual ~GLFrame();

    virtual void initializeGL();
    virtual void resizeGL(int w, int h);
    virtual void paintGL();

    void mousePressEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);

    void addRenderNode(std::string name);

    DataBase* getDataBase() { return this->database_; }
    nodegraph::NodeGraph* getNodeGraph() { return this->graph_; }

public slots:
    void on_createToneMapTrig(bool checked);

private:
    int state_;
    QPoint pos_left, pos_right;

    QTimer *timer_;
    QElapsedTimer *e_timer_;

    DataBase *database_;
    nodegraph::NodeGraph* graph_;
    Renderer *renderer_;
};

#endif // GLFRAME_H
