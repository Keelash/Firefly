#ifndef READERS_NODE_H
#define READERS_NODE_H

#include "node.h"

namespace nodegraph {

class ReadersNode : public I_Node {
public:
    ReadersNode(NodeGraph *graph = nullptr) : I_Node(graph) {  }

    bool addReader(unsigned int, unsigned int, I_Node*) final {  }

    unsigned int getOutputDataType(unsigned int output) const final { return 0; }
    unsigned int getNbOutputChannel() const final { return 0; }

    QString getOutputName(unsigned int input) const final { return QString(); }

protected:
    const QVariant getOutput(unsigned int) const final { return QVariant(); }
};

}//namespace nodegraph

#endif//READERS_NODE_H
