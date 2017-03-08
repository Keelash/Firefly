#ifndef READERS_NODE_H
#define READERS_NODE_H

#include "RW_node.h"

namespace nodegraph {

class ReadersNode : public RWNode {
    Q_OBJECT
public:
    const QVariant getOutput(unsigned int) const { return QVariant(); }
    unsigned int getOutputDataType(unsigned int output) const { return 0; }
    unsigned int getNbOutputChannel() const { return 0; }
};

}//namespace nodegraph

#endif//READERS_NODE_H
