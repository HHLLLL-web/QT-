#ifndef CLOTH_H
#define CLOTH_H

#include <QString>
#include <QColor>
#include <QSettings>
#include <QDebug>
#include <QDate>

class Cloth
{
public:
    enum Type {
        Top,
        Under,
        Dress,
        Shoes,
        Accessory
    };

    Cloth();
    Cloth(const QString &name, Type type, const QString &style,          //type 是自定义类型 为衣服的“类型” 如 上衣
          const QString &pattern, const QString &material,
          const QString &thickness, const QString &season,
          const QString &position, const QString &color,                 //color保存为QString :  rgb(255,0,0)  形式
          const QString &path);                                          //path为衣服图片在本地的路径 读出后可以无需转换直接传入pixmap

    void saveToSettings(QSettings &settings, int id) const;
    static Cloth loadFromSettings(QSettings &settings);
    static bool deleteCloth(int userId, const Cloth& targetCloth);//删除衣物
    static void addDailyOutfit(int userId, const QList<Cloth>& outfit);
    static QList<QList<Cloth>> getDailyOutfits(int userId, const QDate& date);
    static QList<Cloth> getUserClothes(int userId);


    // Getters
    QString name() const;
    Type type() const;
    QString style() const;
    QString pattern() const;
    QString material() const;
    QString thickness() const;
    QString season() const;
    QString position() const;
    QString color() const;
    QString path() const;
    QColor getQColor() const;

    // Setters
    void setName(const QString &name);
    void setType(Type type);
    void setStyle(const QString &style);
    void setPattern(const QString &pattern);
    void setMaterial(const QString &material);
    void setThickness(const QString &thickness);
    void setSeason(const QString &season);
    void setPosition(const QString &position);
    void setColor(const QString &position);
    void setPath(const QString &position);

    //保存当前一个属性到数据中  -- 对应ui的分多次存储数据
    static void saveSingleFeature(int userId, QString featureType, QString oneFeature) ;//featureType必须和属性名对应,全小写


private:
    QString m_name;
    Type m_type;
    QString m_style;
    QString m_pattern;
    QString m_material;
    QString m_thickness;
    QString m_season;
    QString m_position;
    QString m_color;
    QString m_path;
};


#endif // CLOTH_H
