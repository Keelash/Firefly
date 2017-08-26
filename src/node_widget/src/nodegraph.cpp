#include "nodegraph.h"

#include <QGraphicsSceneMouseEvent>
#include <QGraphicsView>

#include <iostream>

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
    this->nodes_.push_back(node);
}

void NodeGraph::updateNode(I_Node* node) {
    std::vector<I_Node*>::iterator it_n;

    it_n = std::find(this->nodes_.begin(), this->nodes_.end(), node);

    if(it_n != this->nodes_.end()) {
        std::stack<I_Node*> s;
        s.push(node);

        while(s.size() != 0) {
            I_Node* curr = s.top();s.pop();
            const I_Node::ReadersMap *rm = curr->getReadersMap();

            for(auto it = rm->begin(); it != rm->end(); ++it) {
                s.push(it->second.second);
            }

            curr->setInvalid();
        }

        s.push(node);
        while(s.size() != 0) {
            I_Node* curr = s.top(); s.pop();
            const I_Node::ReadersMap *rm = curr->getReadersMap();

            for(auto it = rm->begin(); it != rm->end(); ++it) {
                s.push(it->second.second);
            }

            curr->updateNode();
        }
    }
}

void NodeGraph::setNodeToUpdate(I_Node* node) {
    std::vector<I_Node*>::iterator it_n;

    it_n = std::find(this->nodes_.begin(), this->nodes_.end(), node);

    if(it_n != this->nodes_.end()) {
        std::stack<I_Node*> s;
        s.push(node);

        while(s.size() != 0) {
            I_Node* curr = s.top();s.pop();
            const I_Node::ReadersMap *rm = curr->getReadersMap();

            for(auto it = rm->begin(); it != rm->end(); ++it) {
                s.push(it->second.second);
            }

            curr->setInvalid();
        }

        this->updateStack_.push(node);
    }
}

void NodeGraph::updateGraph() {
    while(this->updateStack_.size() != 0) {
        I_Node* curr = this->updateStack_.top(); this->updateStack_.pop();
        const I_Node::ReadersMap *rm = curr->getReadersMap();

        for(auto it = rm->begin(); it != rm->end(); ++it) {
            this->updateStack_.push(it->second.second);
        }
        curr->updateNode();
    }
}

const std::vector<I_Node*> NodeGraph::getNodes() const {
    return this->nodes_;
}

bool NodeGraph::connectNode(I_Node* node_o, unsigned int output, I_Node* node_i, unsigned int input) {
    std::vector<I_Node*>::iterator i, o;

    i = std::find(this->nodes_.begin(), this->nodes_.end(), node_i);
    o = std::find(this->nodes_.begin(), this->nodes_.end(), node_o);

    if(!(i == this->nodes_.end() || o == this->nodes_.end()) &&
                        node_o->addReader(output, input, node_i))
    {
        node_i->addWriter(input, node_o);
        this->setNodeToUpdate(node_o);
        this->updateGraph();

        return true;
    }

    return false;
}

void NodeGraph::drawBackground(QPainter *painter, const QRectF &rect) {
    QPen pen;
    int gridSize = 20;

    pen.setColor(Qt::lightGray);
    painter->setPen(pen);

    qreal left = int(rect.left()) - (int(rect.left()) % gridSize);
    qreal top = int(rect.top()) - (int(rect.top()) % gridSize);
    QVector<QLineF> lines;

    for (qreal x = left; x < rect.right(); x += gridSize){
        lines.append(QLineF(x, rect.top(), x, rect.bottom()));
    }

    for (qreal y = top; y < rect.bottom(); y += gridSize){
        lines.append(QLineF(rect.left(), y, rect.right(), y));
    }

    painter->drawLines(lines.data(), lines.size());
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
