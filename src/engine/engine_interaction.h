#ifndef ENGINE_INTERACTION_H
#define ENGINE_INTERACTION_H

#include <QKeyEvent>
#include <QObject>
#include <QCursor>

#include "src/data_class/database.h"
#include "engine_abstract.h"

class Engine_Interaction {
public:
    Engine_Interaction();
    ~Engine_Interaction() {  }

    void mousePressLeftEventHandler();
    void mousePressRightEventHandler();

    void mouseReleaseLeftEventHandler();
    void mouseReleaseRightEventHandler();

    virtual void update(DataBase *data);

private:
    QPoint pos_onLeftPressed;
    QPoint pos_onRightPressed;

    bool moveCamera_;
    bool zoomCamera_;
};

#endif // ENGINE_INTERACTION_H
