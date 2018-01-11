#ifndef SCENEDATAPANNEL_H
#define SCENEDATAPANNEL_H

#include <QWidget>
#include <QTreeWidget>

#include "src/data_class/database.h"


namespace Ui {
class SceneDataPannel;
}

class SceneDataPannel : public QWidget
{
    Q_OBJECT

public:
    explicit SceneDataPannel(DataBase* database, QWidget *parent = 0);
    ~SceneDataPannel();

    void upadateScene();

private slots:
    void on_scene_Tree_itemActivated(QTreeWidgetItem *item, int column);

private:
    void setModelAsCurrent(Model* current);

    DataBase* database_;
    Model *current_;


    Ui::SceneDataPannel *ui;
};

#endif // SCENEDATAPANNEL_H
