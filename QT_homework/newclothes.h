#ifndef NEWCLOTHES_H
#define NEWCLOTHES_H

#include <QDialog>
#include "Cloth.h"
namespace Ui {
class newClothes;
}

class newClothes : public QDialog
{
    Q_OBJECT

public:
    explicit newClothes(int id, QWidget *parent = nullptr);
    ~newClothes();
    int userID;


private slots:
    void on_next_clicked();

private:
    Ui::newClothes *ui;
};

#endif // NEWCLOTHES_H
