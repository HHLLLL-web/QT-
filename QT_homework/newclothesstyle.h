#ifndef NEWCLOTHESSTYLE_H
#define NEWCLOTHESSTYLE_H

#include <QDialog>

namespace Ui {
class newClothesStyle;
}

class newClothesStyle : public QDialog
{
    Q_OBJECT

public:
    explicit newClothesStyle(QWidget *parent = nullptr);
    ~newClothesStyle();

private:
    Ui::newClothesStyle *ui;
};

#endif // NEWCLOTHESSTYLE_H
