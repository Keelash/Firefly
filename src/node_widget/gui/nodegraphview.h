#ifndef NODEGRAPHVIEW
#define NODEGRAPHVIEW

#include <QGraphicsView>

namespace nodegraph {

class NodeGraph;

namespace gui {

class NodeGraphView : protected QGraphicsView {
    Q_OBJECT
public:
    NodeGraphView(QWidget *parent = 0);
    virtual ~NodeGraphView();

    void setGraph(NodeGraph* graph);

private:
    NodeGraph* graph_;
};

}//namepsace gui

}//namespace nodegraph

#endif//NODEGRAPHVIEW
