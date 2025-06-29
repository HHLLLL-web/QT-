#ifndef NEWCLOTHESTHICKNESS_H
#define NEWCLOTHESTHICKNESS_H

#include <QDialog>

namespace Ui {
class newClothesThickness;
}

class newClothesThickness : public QDialog
{
    Q_OBJECT

public:
    explicit newClothesThickness(QWidget *parent = nullptr);
    ~newClothesThickness();

private:
    Ui::newClothesThickness *ui;
};

#endif // NEWCLOTHESTHICKNESS_H
