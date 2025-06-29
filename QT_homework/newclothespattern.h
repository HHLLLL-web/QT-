#ifndef NEWCLOTHESPATTERN_H
#define NEWCLOTHESPATTERN_H

#include <QDialog>

namespace Ui {
class newClothesPattern;
}

class newClothesPattern : public QDialog
{
    Q_OBJECT

public:
    explicit newClothesPattern(QWidget *parent = nullptr);
    ~newClothesPattern();

private:
    Ui::newClothesPattern *ui;
};

#endif // NEWCLOTHESPATTERN_H
