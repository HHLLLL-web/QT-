#ifndef RECOMMEND_H
#define RECOMMEND_H
#include <QLayout>
#include <QDialog>
#include <QLabel>
#include <Cloth.h>
#include <QList>
#include <QColor>
namespace Ui {
class recommend;
}

class recommend : public QDialog
{
    Q_OBJECT

public:
    int userID;
    explicit recommend(int id,QWidget *parent = nullptr);
    int temperature;
    QColor color;
    QString type;
    QString season;
    QString style;
    QString weather;
    ~recommend();

private slots:
    void on_color_clicked();

    void on_next_clicked();

    void on_style_currentTextChanged(const QString &arg1);

    void on_temperature_valueChanged(int arg1);

    void on_season_currentTextChanged(const QString &arg1);

    void on_weather_currentTextChanged(const QString &arg1);

    void on_return_2_clicked();

private:
    Ui::recommend *ui;

};

#endif // RECOMMEND_H
