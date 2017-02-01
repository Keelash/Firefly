#ifndef DOCKVIEW_H
#define DOCKVIEW_H

#include <vector>
#include <QGraphicsItem>

namespace nodegraph {

namespace gui {

class Edge;

class DockView : public QGraphicsItem {
public:
    DockView(QGraphicsItem *parent = 0);
    virtual ~DockView();

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
};

}//namespace gui

}//namespace nodegraph

#endif//DOCKVIEW_H
