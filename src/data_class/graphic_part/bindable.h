#ifndef BINDABLE_H
#define BINDABLE_H

#include "shader.h"

class Bindable {
public:
    Bindable(int id = 0): id_(id) {  }

    virtual void bind(Shader &shader) = 0;
    int getId() { return this->id_; }

protected:
    int id_;
};

#endif // BINDABLE_H

