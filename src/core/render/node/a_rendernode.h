#ifndef A_RENDERNODE
#define A_RENDERNODE

#include "src/core/factory.h"
#include "src/node_widget/node_widget.h"
#include "src/core/render/renderer.h"

class Renderer;

class A_RenderNode : public nodegraph::WritersNode {
public:
    A_RenderNode(Renderer* renderer = nullptr, nodegraph::NodeGraph *graph = nullptr) :
        nodegraph::WritersNode(graph)
    {
        this->setRenderer(renderer);
    }

    virtual ~A_RenderNode() {  }

    void setRenderer(Renderer* renderer) {
        if(renderer != nullptr) {
            renderer->addNode(this);
        }

        this->renderer_ = renderer;
    }

    void update() {
        this->graph_->setNodeToUpdate(this);
    }

protected:
    Renderer* renderer_;
};

typedef Factory<std::string, A_RenderNode>  RenderNodeFactory;

#define REGISTER_RENDERNODE_ITEM(klass, name) \
    REGISTER_FACTORY_ITEM(RenderNodeFactory, A_RenderNode, klass, name)

#endif//A_RENDERNODE
