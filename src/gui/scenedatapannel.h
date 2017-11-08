#ifndef SCENEDATAPANNEL_H
#define SCENEDATAPANNEL_H

#include <QWidget>
#include <QTreeWidget>

#include "src/data_class/database.h"
#include "src/core/geometry/loopsubdivision.h"

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

    void on_subdivision_spinBox_valueChanged(int arg1);

    void on_add_subdiv_pushButton_clicked();

private:
    DataBase* database_;
    Model *current_;


    Ui::SceneDataPannel *ui;
};

#endif // SCENEDATAPANNEL_H
