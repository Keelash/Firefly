#include "dockview.h"

#include <iostream>
#include <QPainter>
#include <QGraphicsSceneMouseEvent>

#include "edgeview.h"

namespace nodegraph {

namespace gui {

DockView::DockView(Dock_Type type, QGraphicsItem *parent)
    : QGraphicsItem(parent), type_(type) {

}

DockView::~DockView() {

}

void DockView::updateEdge() {
    for(int i = 0; i < this->edge_.size(); ++i) {
        this->edge_[i]->update();
    }
}

QRectF DockView::boundingRect() const {
    return QRectF(0., 0., 15., 15.);
}

void DockView::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    painter->setBrush(Qt::black);
    painter->drawRect(0, 0, 10, 10);
}

}//namespace gui

}//namespace nodegraph
