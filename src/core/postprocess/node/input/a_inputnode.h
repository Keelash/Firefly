#ifndef A_INPUTNODE
#define A_INPUTNODE

#include "src/core/factory.h"
#include "src/node_widget/node_widget.h"
#include "src/data_class/database.h"

class A_InputNode : public nodegraph::WritersNode {
public:
    A_InputNode(DataBase* data = nullptr, nodegraph::NodeGraph *graph = nullptr) :
        nodegraph::WritersNode(graph)
    {
        this->setDataBase(data);
    }

    virtual ~A_InputNode() {  }

    virtual void setDataBase(DataBase* data) {
        this->dataBase_ = data;
    }

protected:
    DataBase* dataBase_;
};

typedef Factory<std::string, A_InputNode>  InputNodeFactory;

#define REGISTER_INPUTNODE_ITEM(klass, name) \
    REGISTER_FACTORY_ITEM(InputNodeFactory, A_InputNode, klass, name)

#endif//A_INPUTNODE
