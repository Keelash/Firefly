#ifndef DOCKVIEW_H
#define DOCKVIEW_H

#include <vector>
#include <QGraphicsItem>

namespace nodegraph {

namespace gui {

class EdgeView;
class NodeView;

class DockView : public QGraphicsItem {
public:
    typedef enum Dock_Type_e { INPUT, OUTPUT } Dock_Type;
    enum { Type = UserType + 1 };

    DockView(NodeView *parent, Dock_Type type, unsigned int pos, QString name = "");
    virtual ~DockView();

    Dock_Type getDockType() const { return this->type_; }
    unsigned int getDockPos() const { return this->pos_; }

    int type() const override { return Type; }
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

private:
    unsigned int pos_;

    Dock_Type type_;
    QString name_;
};

}//namespace gui

}//namespace nodegraph

#endif//DOCKVIEW_H
