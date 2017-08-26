#ifndef GLFRAME_H
#define GLFRAME_H

#include <QtOpenGL/QGLWidget>
#include <QTimer>
#include <QObject>

#include "data_class/database.h"
#include "node_widget/node_widget.h"
#include "data_class/shader/modulable_shader.h"

class GLFrame : public QGLWidget {
    Q_OBJECT
public:
    GLFrame(QWidget* parent = nullptr);
    virtual ~GLFrame();

    void setDataBase(DataBase* data) { this->data_ = data; }
    void setNodeGraph(nodegraph::NodeGraph* graph) { this->graph_ = graph; }

    virtual void initializeGL();
    virtual void resizeGL(int w, int h);
    virtual void paintGL();

private:
    QTimer *timer_;

    DataBase* data_;
    nodegraph::NodeGraph* graph_;
};

#endif // GLFRAME_H
