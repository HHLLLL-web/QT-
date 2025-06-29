#ifndef NEWCLOTHESTOP_H
#define NEWCLOTHESTOP_H

#include <QDialog>

namespace Ui {
class newClothesTop;
}

class newClothesTop : public QDialog
{
    Q_OBJECT

public:
    explicit newClothesTop(QWidget *parent = nullptr);
    ~newClothesTop();

private:
    Ui::newClothesTop *ui;
};

#endif // NEWCLOTHESTOP_H
