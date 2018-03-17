#ifndef ENTITY_H
#define ENTITY_H

#include <atomic>
#include <map>
#include <string>

#include "src/core/component.h"

class Entity {
public:
    Entity(std::string name) : name_(name) {  }
    ~Entity() {  }

    template<class CompD>
    void addComponent(CompD *component) {
        static_assert(
                    std::is_convertible<CompD, Component>,
                    "Cannot convert to Component type"
                    );

        this->componentMap_[this->getTypeId<Comp>] = component;
    }

    template<class T>
    T getComponent() {
        return this->componentMap_[typeid(T).hash_code()];
    }

private:
    template <class Key>
    inline static int getTypeId() {
      static const int id = LastTypeId++;

      return id;
    }

    static std::atomic_int LastTypeId;

    std::map<std::atomic_int, Component*> componentMap_;
    std::string name_;
};

std::atomic_int Entity::LastTypeId(0);

#endif//ENTITY_H
