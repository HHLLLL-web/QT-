#ifndef NEWCLOTHESUNDER_H
#define NEWCLOTHESUNDER_H

#include <QDialog>

namespace Ui {
class newClothesUnder;
}

class newClothesUnder : public QDialog
{
    Q_OBJECT

public:
    explicit newClothesUnder(QWidget *parent = nullptr);
    ~newClothesUnder();

private:
    Ui::newClothesUnder *ui;
};

#endif // NEWCLOTHESUNDER_H
