#include "dockview.h"

#include <iostream>
#include <QPainter>
#include <QGraphicsSceneMouseEvent>

namespace nodegraph {

namespace gui {

DockView::DockView(QGraphicsItem *parent) : QGraphicsItem(parent) {

}

DockView::~DockView() {

}

QRectF DockView::boundingRect() const {
    return QRectF(0., 0., 15., 15.);
}

void DockView::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    painter->setBrush(Qt::black);
    painter->drawRect(0, 0, 10, 10);
}

void DockView::mousePressEvent(QGraphicsSceneMouseEvent *event) {

}

void DockView::mouseReleaseEvent(QGraphicsSceneMouseEvent *event) {

}

}//namespace gui

}//namespace nodegraph
