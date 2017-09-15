#ifndef GLFRAME_H
#define GLFRAME_H

#include <QtOpenGL/QGLWidget>
#include <QTimer>
#include <QObject>

#include "data_class/database.h"
#include "node_widget/node_widget.h"
#include "data_class/shader/modulable_shader.h"

#include "graphic_node/dataextractor.h"

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

    DataBase* getDataBase() { return this->database_; }
    nodegraph::NodeGraph* getNodeGraph() { return this->graph_; }

public slots:
    void on_createMeshDataTrig(bool checked);
    void on_createPBRShaderTrig(bool checked);

private:
    QTimer *timer_;

    DataBase *database_;
    nodegraph::NodeGraph* graph_;
    DataExtractor *extractor_;
};

#endif // GLFRAME_H
