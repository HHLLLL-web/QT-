#ifndef NEWCLOTHESTYPE_H
#define NEWCLOTHESTYPE_H

#include <QDialog>
#include "Cloth.h"
namespace Ui {
class newClothesType;
}

class newClothesType : public QDialog
{
    Q_OBJECT

public:
    explicit newClothesType(int id, QWidget *parent = nullptr);
    ~newClothesType();
    int userID;
    QString type;
    QString material;
    QString season;
    QString thickness;
    QString style;
    QString pattern;


private slots:
    void on_type_currentTextChanged(const QString &arg1);

    void on_style_currentTextChanged(const QString &arg1);

    void on_material_currentTextChanged(const QString &arg1);

    void on_pattern_currentTextChanged(const QString &arg1);



    void on_season_currentTextChanged(const QString &arg1);

    void on_thickness_currentTextChanged(const QString &arg1);

    void on_next_clicked();

private:
    Ui::newClothesType *ui;
};

#endif // NEWCLOTHESTYPE_H
