#ifndef NODE_H
#define NODE_H

#include <QWidget>
#include <QVariant>
#include <QGraphicsItem>

#include "../nodegraph.h"

namespace nodegraph {

class I_Node : public QWidget {
public:
    typedef std::pair<int, I_Node*> NodeInput;
    typedef std::multimap<int, NodeInput> ReadersMap;

    I_Node(NodeGraph *graph);
    virtual ~I_Node();

    virtual void addWriter(unsigned int input, I_Node* writer);
    virtual bool addReader(unsigned int output, unsigned int readers_input, I_Node* reader);
    const ReadersMap* getReadersMap() const { return &this->readers_; }

    bool isValid() const { return isValid_; }
    void setInvalid() { this->isValid_ = false; }
    void setValid() { this->isValid_ = true; }

    virtual unsigned int getInputDataType(unsigned int input) const = 0;
    virtual unsigned int getNbInputChannel() const = 0;
    virtual QString getInputName(unsigned int input) const = 0;


    virtual QString getOutputName(unsigned int input) const = 0;
    virtual unsigned int getOutputDataType(unsigned int output) const = 0;
    virtual unsigned int getNbOutputChannel() const = 0;

    virtual void updateNode() final;

protected:
    virtual void setInput(unsigned int input, QVariant data) = 0;

    virtual const QVariant getOutput(unsigned int output) const = 0;

    virtual void processData() = 0;

    NodeGraph *graph_;

private:
    std::vector<I_Node*> writers_;
    ReadersMap readers_;
    bool isValid_;
};

}//namespace nodegraph


#endif//NODE_H
