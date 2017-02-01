#include "nodeview.h"

#include <QPainter>

#include "src/node_widget/core/node.h"
#include "src/node_widget/gui/dockview.h"

namespace nodegraph {

namespace gui {

NodeView::NodeView(Node *node, QGraphicsItem* parent):
    QGraphicsItem(parent)
{
    this->proxy_ = new QGraphicsProxyWidget(this);
    this->proxy_->setWidget(node);

    this->proxy_->setPos(20., 5.);

    for(unsigned int i = 0; i < node->getNbInputChannel(); ++i) {
        this->input_dock_.push_back(new DockView(this));
    }

    for(unsigned int i = 0; i < node->getNbOutputChannel(); ++i) {
        this->input_dock_.push_back(new DockView(this));
    }

    this->calculateDockPos();
}

NodeView::~NodeView() {
    delete this->proxy_;

    for(unsigned int i = 0; i < this->input_dock_.size(); ++i) {
        delete this->input_dock_[i];
    }

    for(unsigned int i = 0; i < this->output_dock_.size(); ++i) {
        delete this->output_dock_[i];
    }
}

QRectF NodeView::boundingRect() const {
    QRectF bound = this->proxy_->boundingRect();
    int max_dock = std::max(input_dock_.size(), output_dock_.size());
    unsigned int size = std::max(15 * max_dock, 5 + (int)this->proxy_->boundingRect().height());

    bound.setX(0);
    bound.setY(0);
    bound.setWidth(bound.width() + 40.);
    bound.setHeight(size + 5);

    return bound;
}

void NodeView::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    QRectF bound = this->boundingRect();

    painter->setBrush(this->proxy_->widget()->palette().color(QPalette::Background));
    painter->drawRect(5, 0, bound.width() - 5, bound.height());
}

void NodeView::calculateDockPos() {
    int max_dock = std::max(input_dock_.size(), output_dock_.size());
    unsigned int size = std::max(15 * max_dock, (int)this->proxy_->boundingRect().height());

    for(int i = 0; i < input_dock_.size(); ++i) {
        input_dock_[i]->setPos(0, 5 + 15 * i);
    }

    for(int i = 0; i  < output_dock_.size(); ++i) {
        output_dock_[i]->setPos(boundingRect().width() - 5, size - 10 - 15 * i);
    }
}

}//namespace gui

}//namespace nodegraph
