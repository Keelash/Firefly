#ifndef RW_NODE_H
#define RW_NODE_H

#include "node.h"

namespace nodegraph {

class RWNode : public I_Node {
    Q_OBJECT
public:
    RWNode();
    virtual ~RWNode();

    virtual void setInput(Connection c);
    virtual unsigned int getNbInputChannel() const = 0;

public slots:
    virtual void updateNode();

protected:
    std::vector<Connection> connection_;
    std::vector<QVariant> input_;
};

}//namespace nodegraph

#endif//RW_NODE_H
