#ifndef WRITERS_NODE_H
#define WRITERS_NODE_H

#include "RW_node.h"

namespace nodegraph {

class WritersNode : public I_Node {
    Q_OBJECT
public:
    void setInput(Connection c) {  }
    unsigned int getInputDataType(unsigned int) const { return 0; }
    unsigned int getNbInputChannel() const { return 0; }
};

}//namespace nodegraph


#endif//WRITERS_NODE_H
