#ifndef SCENERENDER_H
#define SCENERENDER_H

#include <QWidget>

#include "src/node_widget/node_widget.h"
#include "src/core/render/node/a_rendernode.h"
#include "src/core/render/renderer.h"

namespace Ui {
class SceneRender;
}

class SceneRender : public A_RenderNode {
    Q_OBJECT
public:
    explicit SceneRender(Renderer* renderer = nullptr, nodegraph::NodeGraph *graph = nullptr);
    ~SceneRender();

    unsigned int getOutputDataType(unsigned int output) const;
    unsigned int getNbOutputChannel() const;
    virtual QString getOutputName(unsigned int output) const;

protected:
    const QVariant getOutput(unsigned int output) const;

    void processData() {  }

private :
    Ui::SceneRender *ui;
};

REGISTER_RENDERNODE_ITEM(SceneRender, "SceneRender")

#endif // N_SCENERENDER_H
