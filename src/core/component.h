#ifndef A_COMPONENT_H
#define A_COMPONENT_H

#include <string>

class Entity;

class A_Component {
public:
    A_Component(std::string name, Entity* parent, bool enable = true):
        parent_(parent), componentName_(name), isEnable_(enable)
    {

    }

    void enableComponent() { this->isEnable_ = true; }
    void disableComponent() { this->isEnable_ = false; }
    bool isEnabled() { return this->isEnable_; }

    std::string getName() { return this->componentName_; }

    Entity* getEntity() { return this->parent_; }

private:
    Entity *parent_;

    std::string componentName_;
    bool isEnable_;
};

#endif//A_COMPONENT_H
