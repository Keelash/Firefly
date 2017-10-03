#ifndef GRAPHICNODE_H
#define GRAPHICNODE_H

#include <QWidget>
#include "src/node_widget/node_widget.h"

class DataBase;

class GraphicNode {
public:
    GraphicNode(DataBase* data): database_(data) {  }
    ~GraphicNode() {  }

protected :
    DataBase *database_;
};

#endif//GRAPHICNODE_H
