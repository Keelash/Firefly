#include "nodeview.h"

#include <QGraphicsScene>
#include <QPainter>
#include <QLayout>

#include <iostream>

#include "node/node.h"
#include "dockview.h"
#include "edgeview.h"

namespace nodegraph {

namespace gui {

NodeView::NodeView(I_Node *node): QGraphicsItem(nullptr) {
    this->proxy_ = new QGraphicsProxyWidget(this);
    this->proxy_->setWidget(node);

    this->setFlag(QGraphicsItem::ItemIsMovable, true);
    this->setFlag(QGraphicsItem::ItemIsSelectable, true);
    this->setFlag(QGraphicsItem::ItemSendsGeometryChanges, true);

    this->input_edge_.resize(node->getNbInputChannel());
    this->output_edge_.resize(node->getNbOutputChannel());

    for(unsigned int i = 0; i < node->getNbInputChannel(); ++i) {
        this->input_dock_.push_back(new DockView(this, DockView::INPUT, i,
                                                 node->getInputName(i)));
        this->input_edge_[i] = nullptr;
    }

    for(unsigned int i = 0; i < node->getNbOutputChannel(); ++i) {
        this->output_dock_.push_back(new DockView(this, DockView::OUTPUT, i,
                                                  node->getOutputName(i)));
    }

    if(node->getNbInputChannel() != 0) {
        DockView *d = this->input_dock_[0];

        this->proxy_->setPos(d->boundingRect().right() + node->layout()->spacing(),
                             node->layout()->spacing());
    }
    else
        this->proxy_->setPos(node->layout()->spacing(), node->layout()->spacing());

    this->calculateDockPos();
}

NodeView::~NodeView() {
    delete this->proxy_;

    for(unsigned int i = 0; i < this->input_dock_.size(); ++i) {
        delete this->input_dock_[i];
        //if(this->input_edge_[i]) delete this->input_edge_[i];
    }

    for(unsigned int i = 0; i < this->output_dock_.size(); ++i)
        delete this->output_dock_[i];
}

QRectF NodeView::boundingRect() const {
    QRectF bound = this->proxy_->boundingRect();
    int max_dock = std::max(input_dock_.size(), output_dock_.size());
    unsigned int size = std::max(5 + 30 * max_dock, 5 + (int)this->proxy_->boundingRect().height());

    bound.setX(0);
    bound.setY(0);
    bound.setWidth(bound.width() + 80.);
    bound.setHeight(size + 5);

    return bound;
}

void NodeView::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    QRectF bound = this->boundingRect();

    painter->setBrush(this->proxy_->widget()->palette().color(QPalette::Background));
    painter->drawRect(5, 0, bound.width(), bound.height());
}

void NodeView::calculateDockPos() {
    int max_dock = std::max(input_dock_.size(), output_dock_.size());

    for(int i = 0; i < input_dock_.size(); ++i) {
        input_dock_[i]->setPos(0, 5. + input_dock_[i]->boundingRect().height() * i);
    }

    if(output_dock_.size() != 0) {
        QRectF r = output_dock_[0]->boundingRect();
        unsigned int size =
                (int)std::max(r.height() * max_dock, this->proxy_->boundingRect().height());

        for(int i = 0; i  < output_dock_.size(); ++i) {
            unsigned int pos = output_dock_.size() - 1 - i;
            output_dock_[pos]->setPos(boundingRect().right(), size - 5. - r.height() * i);
        }
    }
}


I_Node* NodeView::getNode() {
    return (I_Node*)this->proxy_->widget();
}

unsigned int NodeView::getInputDockPos(DockView* dock) {
    std::vector<DockView*>::iterator it;
    it = std::find(this->input_dock_.begin(), this->input_dock_.end(), dock);

    return std::distance(this->input_dock_.begin(), it);
}

unsigned int NodeView::getOutputDockPos(DockView* dock) {
    std::vector<DockView*>::iterator it;
    it = std::find(this->output_dock_.begin(), this->output_dock_.end(), dock);

    return std::distance(this->output_dock_.begin(), it);
}

void NodeView::addInputEdge(unsigned int input, EdgeView *edge) {
    if(this->input_edge_[input] != nullptr)
        delete this->input_edge_[input];

    this->input_edge_[input] = edge;
}

EdgeView* NodeView::getInputEdge(unsigned int input) {
    return this->input_edge_[input];
}

void NodeView::delInputEdge(unsigned int input) {
    delete this->input_edge_[input];
    this->input_edge_[input] = nullptr;
}

void NodeView::addOutputEdge(unsigned int output, EdgeView* edge) {
    this->output_edge_[output].push_back(edge);
}

std::vector<EdgeView*> NodeView::getOutputEdge(unsigned int output) {
    return this->output_edge_[output];
}

void NodeView::delOutputEdge(unsigned int output, EdgeView* edge) {
    auto it = std::find(this->output_edge_[output].begin(), this->output_edge_[output].end(), edge);

    if(it != this->output_edge_[output].end()) {
        this->output_edge_[output].erase(it);
    }
}

QVariant NodeView::itemChange(GraphicsItemChange change, const QVariant &value) {
    if (change == ItemPositionChange)
        this->scene()->update();

    return QGraphicsItem::itemChange(change, value);
}

}//namespace gui

}//namespace nodegraph
