#ifndef NEWCLOTHESPIC_H
#define NEWCLOTHESPIC_H

#include <QDialog>
#include "Cloth.h"
namespace Ui {
class newClothesPic;
}

class newClothesPic : public QDialog
{
    Q_OBJECT

public:
    explicit newClothesPic(int id, QWidget *parent = nullptr);
    ~newClothesPic();
    int userID;

private slots:
    void on_color_clicked();

    void on_picture_clicked();

    void on_next_clicked();

private:
    Ui::newClothesPic *ui;
};

#endif // NEWCLOTHESPIC_H
