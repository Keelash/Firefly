#include "dockview.h"

#include <iostream>
#include <QPainter>
#include <QGraphicsSceneMouseEvent>

#include "edgeview.h"
#include "nodeview.h"

namespace nodegraph {

namespace gui {

DockView::DockView(NodeView *parent, Dock_Type type, unsigned int pos, QString name)
    : QGraphicsItem(parent), name_(name), type_(type), pos_(pos) {

}

DockView::~DockView() {

}

QRectF DockView::boundingRect() const {
    return QRectF(0., 0., 55., 30.);
}

void DockView::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    QFont font = painter->font();

    font.setPointSize(11);
    painter->setFont(font);

    painter->setBrush(Qt::black);
    painter->drawRect(0, 0, 10, 10);

    if(this->type_ == INPUT) {
        painter->drawText(12, -2, 38, 13, Qt::AlignVCenter, this->name_);
    }
    else {
        painter->drawText(-40, -2, 38, 13, Qt::AlignVCenter, this->name_);
    }
}

}//namespace gui

}//namespace nodegraph
