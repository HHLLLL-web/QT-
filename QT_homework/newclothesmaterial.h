#ifndef NEWCLOTHESMATERIAL_H
#define NEWCLOTHESMATERIAL_H

#include <QDialog>

namespace Ui {
class newClothesMaterial;
}

class newClothesMaterial : public QDialog
{
    Q_OBJECT

public:
    explicit newClothesMaterial(QWidget *parent = nullptr);
    ~newClothesMaterial();

private:
    Ui::newClothesMaterial *ui;
};

#endif // NEWCLOTHESMATERIAL_H
