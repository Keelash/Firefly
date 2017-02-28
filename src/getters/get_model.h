#ifndef GET_MODEL_H
#define GET_MODEL_H

#include <QWidget>

#include "getters.h"

namespace Ui {
class Get_Model;
}

class Get_Model : public Getters {
    Q_OBJECT

public:
    explicit Get_Model();
    ~Get_Model();

    const QVariant* getOutput(unsigned int output) const;
    QVariant::Type getOutputDataType(unsigned int output) const;
    unsigned int getNbOutputChannel() const;

public slots:
    virtual void updateNode() {  }

private:
    Ui::Get_Model *ui;
};

#endif // GET_MODEL_H
