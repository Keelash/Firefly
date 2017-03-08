#ifndef GET_MODEL_H
#define GET_MODEL_H

#include "src/graphic_node/getters.h"

namespace Ui {
class Get_Model;
}

class DataBase;

class Get_Model : public Getters {
    Q_OBJECT

public:
    explicit Get_Model(DataBase* data);
    ~Get_Model();

    const QVariant getOutput(unsigned int output) const;
    unsigned int getOutputDataType(unsigned int output) const;
    unsigned int getNbOutputChannel() const;

public slots:
    virtual void updateNode() {  }

private slots:
    void on_comboBox_currentIndexChanged(int index);

private:
    QString createNewModel(int index);

    DataBase* database_;
    Ui::Get_Model *ui;

    QVariant output_;
};

#endif // GET_MODEL_H
