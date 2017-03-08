#ifndef OUTPUT_H
#define OUTPUT_H

#include "src/graphic_node/readers.h"
#include "src/data_class/shader/shader.h"
#include "src/data_class/database.h"

namespace Ui {
class Output;
}

class Output : public Readers {
    Q_OBJECT
public:
    explicit Output();
    ~Output();

    virtual void setInput(Connection c);
    virtual unsigned int getInputDataType(unsigned int input) const;
    virtual unsigned int getNbInputChannel() const;

public slots:
    virtual void updateNode();

private:
    Ui::Output *ui;

    Connection input_;
    Shader* shader_;
};

#endif // OUTPUT_H
