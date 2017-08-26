#include "node.h"

#include <iostream>

namespace nodegraph {

I_Node::I_Node(NodeGraph *graph) : QWidget(nullptr), graph_(graph) {
    this->setValid();
}

I_Node::~I_Node() {

}

void I_Node::addWriter(unsigned int input, I_Node* writer) {
    if(this->writers_.size() < this->getNbInputChannel())
        this->writers_.resize(this->getNbInputChannel());

    this->writers_[input] = writer;
}

bool I_Node::addReader(unsigned int output, unsigned int readers_input, I_Node* reader) {
    NodeInput ni(readers_input, reader);
    std::pair<int, NodeInput> p(output, ni);

    if(reader->getInputDataType(readers_input) == this->getOutputDataType(output)) {
        this->readers_.insert(p);
        return true;
    }

    return false;
}

void I_Node::updateNode() {
    for(int i = 0; i < this->getNbInputChannel(); ++i) {
        if(this->writers_.size() != 0 && (this->writers_[i] && !this->writers_[i]->isValid()))
            return;
    }

    this->processData();

    for(int i = 0; i < this->getNbOutputChannel(); ++i) {
        if(this->readers_.count(i) != 0) {
            auto range = this->readers_.equal_range(i);
            ReadersMap::iterator it;

            for(it = range.first; it != range.second; ++it) {
                it->second.second->setInput(it->second.first, this->getOutput(i));
            }
        }
    }

    this->setValid();
}

}//namespace nodegraph
