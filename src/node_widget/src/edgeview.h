#ifndef EDGEVIEW_H
#define EDGEVIEW_H

#include <QGraphicsItem>

namespace nodegraph {

namespace gui {

class DockView;

class EdgeView : public QGraphicsItem {
public:
    EdgeView(DockView *input, DockView *output = nullptr);
    ~EdgeView();

    enum { Type = UserType + 3 };
    int type() const override { return Type; }

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    DockView* getInput() {return this->input_; }

    DockView* getOutput() { return this->output_; }
    void setOutput(DockView *output);

    void setEndPoint(QPointF point);

private:
    QPointF end_point_;

    DockView *input_;
    DockView *output_;
};

}//namespace gui

}//namespace nodegraph

#endif//EDGEVIEW_H
