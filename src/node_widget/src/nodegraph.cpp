#include "nodegraph.h"

#include <QGraphicsSceneMouseEvent>
#include <QGraphicsView>

#include "node/node.h"
#include "nodeview.h"
#include "dockview.h"
#include "edgeview.h"

namespace nodegraph {

NodeGraph::NodeGraph(QObject* parent) : QGraphicsScene(parent) {
    this->state_ = 0;
}

NodeGraph::~NodeGraph() {

}

void NodeGraph::addNode(I_Node* node) {
    this->addItem(new gui::NodeView(node));
    this->node_.push_back(node);
}

const std::vector<I_Node*> NodeGraph::getNodes() const {
    return this->node_;
}

bool NodeGraph::connectNode(I_Node* node_o, unsigned int output, I_Node* node_i, unsigned int input) {
    std::vector<I_Node*>::iterator i, o;
    I_Node::Connection c;

    i = std::find(this->node_.begin(), this->node_.end(), node_i);
    o = std::find(this->node_.begin(), this->node_.end(), node_o);

    if(i == this->node_.end() || o == this->node_.end()
            || node_o->getOutputDataType(output) != node_i->getInputDataType(input))
        return false;

    c.node = node_o;
    c.input = input; c.output = output;

    node_i->setInput(c);
    node_i->updateNode();
    connect(node_o, SIGNAL(outputChanged()), node_i, SLOT(updateNode()));

    return true;
}

void NodeGraph::mousePressEvent(QGraphicsSceneMouseEvent *e) {
    QGraphicsScene::mousePressEvent(e);


    QGraphicsItem *i = this->itemAt(e->scenePos(), QTransform());
    gui::DockView *d = qgraphicsitem_cast<gui::DockView*>(i);

    switch(this->state_) {
    case 0 :
        if(d && d->getDockType() == gui::DockView::OUTPUT) {
            this->state_ = 1;

            this->curr_edge_ = new gui::EdgeView(d);
            this->curr_edge_->setEndPoint(e->scenePos());

            this->update();
        }
        break;
    case 1:
        //Nothing to do
        break;
    default :
        break;
    }


}

void NodeGraph::mouseMoveEvent(QGraphicsSceneMouseEvent *e) {
    QGraphicsScene::mouseMoveEvent(e);

    switch(this->state_) {
    case 0 :
        //Nothing to do
        //this->state_ = 0;
        break;
    case 1:
        this->state_ = 1;

        this->curr_edge_->setEndPoint(e->scenePos());

        this->update();
    default:
        break;
    }
}

void NodeGraph::mouseReleaseEvent(QGraphicsSceneMouseEvent *e) {
    QGraphicsScene::mouseReleaseEvent(e);

    QGraphicsItem *i = this->itemAt(e->scenePos(), QTransform());
    gui::DockView *d_o, *d_i = qgraphicsitem_cast<gui::DockView*>(i);
    gui::NodeView *ni, *no;

    switch(this->state_) {
    case 0 :
        //Nothing to do
        //this->state_ = 0;
        break;
    case 1 :
        this->state_ = 0;

        if(d_i && d_i->getDockType() == gui::DockView::INPUT){
            d_o = this->curr_edge_->getInput();
            ni = qgraphicsitem_cast<gui::NodeView*>(d_i->parentItem());
            no = qgraphicsitem_cast<gui::NodeView*>(d_o->parentItem());

            if(ni && no) {
                if (connectNode(no->getNode(), no->getOutputDockPos(d_o),
                                          ni->getNode(), ni->getInputDockPos(d_i))) {

                    this->curr_edge_->setOutput(d_i);
                    d_i->addEdge(this->curr_edge_);
                    d_o->addEdge(this->curr_edge_);
                }
                else {
                    delete this->curr_edge_;
                    this->update();
                }
            }
        }
        else {
            delete this->curr_edge_;
            this->update();
        }
        break;
    default:
        break;
    }
}

}//namespace nodegraph
