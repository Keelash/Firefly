#ifndef ENGINE_ABSTRACT_H
#define ENGINE_ABSTRACT_H

#include <vector>
#include <iostream>

#include <QObject>
#include <QGLWidget>

class Engine_Abstract {
public:
    Engine_Abstract(QGLWidget *parent): parent_(parent) {  }
    virtual ~Engine_Abstract() {  }

    virtual void update() = 0;

protected:
    QGLWidget *parent_;
};
#endif // ENGINE_ABSTRACT_H

