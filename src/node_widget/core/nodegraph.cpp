#include "nodegraph.h"

#include "node.h"

namespace nodegraph {

NodeGraph::NodeGraph(QObject* parent) :
    QObject(parent)
{

}

NodeGraph::~NodeGraph() {

}

void NodeGraph::addNode(Node* node) {
    this->node_.push_back(node);
}

const std::vector<Node*> NodeGraph::getNodes() const {
    return this->node_;
}

bool NodeGraph::connectNode(Node* node_i, unsigned int input,
                            Node* node_o, unsigned int output) {
    std::vector<Node*>::iterator i, o;

    i = std::find(this->node_.begin(), this->node_.end(), node_i);
    o = std::find(this->node_.begin(), this->node_.end(), node_o);

    if(i == this->node_.end() || o == this->node_.end()
            || node_o->getOutputDataType(output) != node_i->getInputDataType(input))
        return false;

    node_i->setInput(node_o->getOutput(output), input);

}

const std::vector<NodeGraph::Connection> NodeGraph::getConnection() const {

}

}//namespace nodegraph
