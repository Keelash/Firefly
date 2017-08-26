#include "dockview.h"

#include <iostream>
#include <QPainter>
#include <QGraphicsSceneMouseEvent>

#include "edgeview.h"

namespace nodegraph {

namespace gui {

DockView::DockView(Dock_Type type, QString name, QGraphicsItem *parent)
    : QGraphicsItem(parent), name_(name), type_(type) {

}

DockView::~DockView() {

}

void DockView::updateEdge() {
    for(int i = 0; i < this->edge_.size(); ++i) {
        this->edge_[i]->update();
    }
}

QRectF DockView::boundingRect() const {
    return QRectF(0., 0., 55., 55.);
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
