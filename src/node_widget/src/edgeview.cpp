#include "edgeview.h"

#include <iostream>
#include <QPainter>

#include "dockview.h"

namespace nodegraph {

namespace gui {

EdgeView::EdgeView(DockView *input, DockView *output)
    : QGraphicsItem(input), input_(input), output_(output), end_point_(0., 0.) {
}

EdgeView::~EdgeView() {

}

void EdgeView::setOutput(DockView *output) {
    this->output_ = output;
}

void EdgeView::setEndPoint(QPointF point) {
    this->end_point_ = point;
}


QRectF EdgeView::boundingRect() const {
    QPointF var = (this->output_)? this->output_->scenePos() : this->end_point_;
    var -= this->input_->scenePos();

    return QRectF(0.0, 0.0, var.x(), var.y());
}

void EdgeView::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    QPointF var = (this->output_)? this->output_->scenePos() : this->end_point_;
    QPen pen(Qt::black, 2, Qt::SolidLine, Qt::SquareCap, Qt::RoundJoin);

    var -= this->input_->scenePos();

    QPainterPath myPath;
    QPointF c1(var.x() / 2.0, 0.0f);
    QPointF c2(var.x() / 2.0, var.y());

    myPath.moveTo(5., 5.);
    myPath.cubicTo(c1, c2, var);

    painter->setRenderHint(QPainter::Antialiasing);
    painter->setBrush(Qt::NoBrush);
    painter->setPen(pen);

    painter->drawPath(myPath);
}


}//namespace gui

}//namespace nodegraph
