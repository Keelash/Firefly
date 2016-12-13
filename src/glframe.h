#ifndef GLFRAME_H
#define GLFRAME_H

#include <QtOpenGL/QGLWidget>
#include <QKeyEvent>
#include <QTimer>
#include <string>
#include <vector>

#include "engine/engine_graphic.h"
#include "engine/engine_interaction.h"
#include "src/data_class/database.h"

class GLFrame : public QGLWidget {
    Q_OBJECT
public:
    GLFrame(QWidget* parent = nullptr);
    virtual ~GLFrame();

    virtual void initializeGL();
    virtual void resizeGL(int w, int h);
    virtual void paintGL();

    inline Engine_Graphic* getGraphicEngine() { return this->engine_g; }
    inline Engine_Interaction* getInteractionEngine() { return this->engine_i; }
    inline DataBase* getDatabase() { return this->data_base_; }

    bool setEnvmap(const char *path);
    bool loadFile(std::string path);
    void changeCamera(int mode) { this->data_base_->changeCameraMode((Camera_Mode)mode); }

    void keyPressEvent(QKeyEvent *e);
    void mousePressEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);

private:
    Engine_Graphic *engine_g;
    Engine_Interaction *engine_i;

    DataBase *data_base_;

    QTimer *timer_;
};

#endif //GLFRAME_H
