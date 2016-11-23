#ifndef ENGINE_INTERACTION_H
#define ENGINE_INTERACTION_H

#include <QKeyEvent>
#include <QObject>
#include <QCursor>

#include "src/data_class/database.h"
#include "engine_abstract.h"

class Engine_Interaction : public Engine_Abstract {
public:
    Engine_Interaction(QGLWidget *parent, DataBase *data);
    ~Engine_Interaction() {  }

    void keyboardEventHandler(QKeyEvent *e);

    void mousePressLeftEventHandler();
    void mousePressRightEventHandler();

    void mouseReleaseLeftEventHandler();
    void mouseReleaseRightEventHandler();

    virtual void update();

private:
    DataBase* data_base_;

    bool moveCamera_;
    bool zoomCamera_;
};

#endif // ENGINE_INTERACTION_H
