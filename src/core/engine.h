#ifndef A_ENGINE_H
#define A_ENGINE_H

#include <vector>

#include <src/core/component.h>

class Asset;
class EntityManager;

class A_Engine {
public:
    A_Engine(EntityManager *manager) : manager_(manager) {  }

    virtual void handleAssetLoading(Asset &asset) = 0;

    virtual void preupdate() = 0;
    virtual void update() = 0;
    virtual void postupdate() = 0;

private:
    EntityManager *manager_;
};

#endif//A_ENGINE_H
