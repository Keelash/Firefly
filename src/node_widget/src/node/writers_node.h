#ifndef WRITERS_NODE_H
#define WRITERS_NODE_H

#include "node.h"
#include <unordered_map>

namespace nodegraph {

class WritersNode : public I_Node {
public:
    WritersNode(NodeGraph *graph) : I_Node(graph) { }

    virtual void addWriters(unsigned int, I_Node*) final {  }

    unsigned int getInputDataType(unsigned int) const final { return 0; }
    unsigned int getNbInputChannel() const final { return 0; }

    QString getInputName(unsigned int) const final { return QString(); }

protected:
    void setInput(unsigned int, QVariant) final { }
};

}//namespace nodegraph


#endif//WRITERS_NODE_H
