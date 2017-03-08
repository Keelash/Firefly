#include "RW_node.h"

#include <iostream>

namespace nodegraph {

RWNode::RWNode() : I_Node() {

}

RWNode::~RWNode() {

}

void RWNode::setInput(Connection c) {
    if(this->input_.size() < this->getNbInputChannel()) {
        this->input_.resize(this->getNbInputChannel());
        this->connection_.resize(this->getNbInputChannel());
    }

    if(c.input < this->getNbInputChannel()) {
        this->connection_[c.input] = c;
    }
}

void RWNode::updateNode() {
    for (unsigned int i = 0; i < this->getNbInputChannel(); ++i) {
        I_Node* node = this->connection_[i].node;
        unsigned int output = this->connection_[i].output;
        unsigned int input = this->connection_[i].input;

        if (node != nullptr)
            this->input_[input] = node->getOutput(output);
    }
}

}//namespace nodegraph
