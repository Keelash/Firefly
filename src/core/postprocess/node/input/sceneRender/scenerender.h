#ifndef SCENERENDER_H
#define SCENERENDER_H

#include <QWidget>

#include "src/node_widget/node_widget.h"
#include "src/core/postprocess/node/input/a_inputnode.h"

namespace Ui {
class SceneRender;
}

class SceneRender : public A_InputNode {
    Q_OBJECT
public:
    //Il faudra vraiment trouver quelque chose de mieux...
    class SceneRenderNodeObserver : public DataBase::DataObserver {
    public:
        SceneRenderNodeObserver(SceneRender *node) {
            node_ = node;
        }

        virtual void update() {
            this->node_->graph_->setNodeToUpdate(this->node_);
        }
    private:
        SceneRender *node_;
    };

    explicit SceneRender(DataBase* dataBase = nullptr, nodegraph::NodeGraph *graph = nullptr);
    ~SceneRender();

    virtual void setDataBase(DataBase* data) {
        if(data != nullptr) {
            data->addProcessedTextureObserver(new SceneRenderNodeObserver(this));
        }

        this->dataBase_ = data;
    }


    unsigned int getOutputDataType(unsigned int output) const;
    unsigned int getNbOutputChannel() const;
    virtual QString getOutputName(unsigned int output) const;

protected:
    const QVariant getOutput(unsigned int output) const;

    void processData() {  }

private :
    Ui::SceneRender *ui;
};

REGISTER_INPUTNODE_ITEM(SceneRender, "SceneRender")

#endif // N_SCENERENDER_H
