#ifndef ENGINE_ABSTRACT_H
#define ENGINE_ABSTRACT_H

#include "src/data_class/database.h"

class A_Engine_Const {
public:
    A_Engine_Const() {  }
    virtual ~A_Engine_Const() {  }

    virtual void update(const DataBase *data) = 0;
};

class A_Engine {
public:
    A_Engine() {  }
    virtual ~A_Engine() {  }

    virtual void update(DataBase *data) = 0;
};

#endif // ENGINE_ABSTRACT_H

