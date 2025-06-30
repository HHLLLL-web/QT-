#include "Cloth.h"

Cloth::Cloth() : m_type(Top) {}

Cloth::Cloth(const QString &name, Type type, const QString &style,
             const QString &pattern, const QString &material,
             const QString &thickness, const QString &season,
             const QString &position, const QString &color,
             const QString &path) :
    m_name(name),
    m_type(type),
    m_style(style),
    m_pattern(pattern),
    m_material(material),
    m_thickness(thickness),
    m_season(season),
    m_position(position),
    m_color(color),
    m_path(path)

{}

void Cloth::saveToSettings(QSettings &settings, int id) const
{
    // settings.beginGroup(QString("cloth_%1").arg(id));      调整了结构
    settings.setValue("name", m_name);
    settings.setValue("type", m_type);
    settings.setValue("style", m_style);
    settings.setValue("pattern", m_pattern);
    settings.setValue("material", m_material);
    settings.setValue("thickness", m_thickness);
    settings.setValue("season", m_season);
    settings.setValue("position", m_position);
    settings.setValue("color", m_color);
    settings.setValue("path", m_path);

    // settings.endGroup();
}

Cloth Cloth::loadFromSettings(QSettings &settings)
{
    Cloth cloth;
    // settings.beginGroup(QString("cloth_%1").arg(id));
    cloth.m_name = settings.value("name").toString();
    cloth.m_type = static_cast<Type>(settings.value("type").toInt());
    cloth.m_style = settings.value("style").toString();
    cloth.m_pattern = settings.value("pattern").toString();
    cloth.m_material = settings.value("material").toString();
    cloth.m_thickness = settings.value("thickness").toString();
    cloth.m_season = settings.value("season").toString();
    cloth.m_position = settings.value("position").toString();
    cloth.m_color = settings.value("color").toString();
    cloth.m_path = settings.value("path").toString();

    // settings.endGroup();
    return cloth;
}

// Getters implementation
QString Cloth::name() const { return m_name; }
Cloth::Type Cloth::type() const { return m_type; }
QString Cloth::style() const { return m_style; }
QString Cloth::pattern() const { return m_pattern; }
QString Cloth::material() const { return m_material; }
QString Cloth::thickness() const { return m_thickness; }
QString Cloth::season() const { return m_season; }
QString Cloth::position() const { return m_position; }
QString Cloth::color() const { return m_color; }
QString Cloth::path() const { return m_path; }
QColor Cloth::getQColor() const {
    QString rgbstr = m_color;
    QString innerstr = rgbstr.mid(4,rgbstr.length()-5);
    QStringList parts = innerstr.split(",");
    int r = parts[0].trimmed().toInt();
    int g = parts[1].trimmed().toInt();
    int b = parts[2].trimmed().toInt();
    QColor c(r,g,b);
    return c;
}


// Setters implementation
void Cloth::setName(const QString &name) { m_name = name; }
void Cloth::setType(Type type) { m_type = type; }
void Cloth::setStyle(const QString &style) { m_style = style; }
void Cloth::setPattern(const QString &pattern) { m_pattern = pattern; }
void Cloth::setMaterial(const QString &material) { m_material = material; }
void Cloth::setThickness(const QString &thickness) { m_thickness = thickness; }
void Cloth::setSeason(const QString &season) { m_season = season; }
void Cloth::setPosition(const QString &position) { m_position = position; }
void Cloth::setColor(const QString &color) { m_color = color; }
void Cloth::setPath(const QString &path) { m_path = path; }

void Cloth::saveSingleFeature(int userId, QString featureType, QString oneFeature)
{
    QSettings settings("magicCloset", "UserContent");
    settings.beginGroup(QString("id_%1").arg(userId));

    // 获取当前最大索引（需实际读取数组内容）
    int newIndex = 0;
    int arraySize = settings.beginReadArray("clothes"); // 获取数组实际大小
    while (newIndex < arraySize) {
        settings.setArrayIndex(newIndex);
        if (!settings.contains(featureType)) {
            break; // 找到缺失位置，退出
        }
        newIndex++;
    }
    settings.endArray();

    // 如果遍历完所有元素仍未找到缺失位置，则 newIndex == arraySize

    // 写入新数据到新索引
    settings.beginWriteArray("clothes");
    settings.setArrayIndex(newIndex);  // 关键：使用找到的空索引
    settings.setValue(featureType, oneFeature);
    settings.endArray();

    settings.endGroup();
}

bool Cloth::deleteCloth(int userId, const Cloth& targetCloth)
{
    QSettings settings("magicCloset", "UserContent");
    settings.beginGroup(QString("id_%1").arg(userId));

    //获取当前衣物数组
    int size = settings.beginReadArray("clothes");
    if (size == 0) {
        settings.endArray();
        settings.endGroup();
        return false;
    }

    //查找匹配的衣物    //根据衣服的name type color查找，基本唯一
    int targetIndex = -1;
    for (int i = 0; i < size; ++i) {
        settings.setArrayIndex(i);
        Cloth current = loadFromSettings(settings);
        if (current.name() == targetCloth.name() &&
            current.type() == targetCloth.type() &&
            current.color() == targetCloth.color()) {
            targetIndex = i;
            break;
        }
    }

    //如果没找到直接返回
    if (targetIndex == -1) {
        settings.endArray();
        settings.endGroup();
        return false;
    }

    //删除并重建数组结构
    settings.endArray();

    QList<Cloth> remainingClothes;
    settings.beginReadArray("clothes");
    for (int i = 0; i < size; ++i) {
        if (i != targetIndex) {
            settings.setArrayIndex(i);
            remainingClothes.append(loadFromSettings(settings));
        }
    }
    settings.endArray();

    //重新写入
    settings.remove("clothes");

    settings.beginWriteArray("clothes");
    for (int i = 0; i < remainingClothes.size(); ++i) {
        settings.setArrayIndex(i);
        remainingClothes[i].saveToSettings(settings, i);
    }
    settings.endArray();

    //调整新数组大小
    settings.beginReadArray("clothes");
    settings.setValue("size",size-1);
    settings.endArray();

    settings.endGroup();
    return true;
}
void Cloth::addDailyOutfit(int userId, const QList<Cloth>& outfit)
{
    QSettings settings("magicCloset", "UserContent");
    QString basePath = QString("id_%1/history/%2")
                           .arg(userId)
                           .arg(QDate::currentDate().toString("yyyy-MM-dd"));

    //获取当天记录总数
    settings.beginGroup(basePath);
    int dailyCount = settings.value("size", 0).toInt();

    //创建新记录目录
    QString recordPath = QString("%1").arg(dailyCount);
    settings.beginGroup(recordPath);

    //存储衣物数量
    settings.setValue("size", outfit.size());

    //存储每件衣物数据
    for (int i = 0; i < outfit.size(); ++i) {
        settings.beginGroup(QString::number(i));
        Cloth cloth=outfit[i];
        cloth.saveToSettings(settings,userId);
        settings.endGroup();
    }

    settings.endGroup();

    //更新当天记录总数
    settings.setValue("/size", dailyCount + 1);
    settings.endGroup();
}

QList<QList<Cloth>> Cloth::getDailyOutfits(int userId, const QDate& date)            //单日内的穿搭记录顺序编号
{                                                                                    //单次穿搭中的衣物顺序编号
    QList<QList<Cloth>> result;                                                      //以上是两层QList的索引分别的含义
    QSettings settings("magicCloset", "UserContent");                                //举例：result[0][0] → 当天第1次穿搭的第1件衣服
        //     result[0][1] → 当天第1次穿搭的第2件衣服
    QString basePath = QString("id_%1/history/%2")
                           .arg(userId)
                           .arg(date.toString("yyyy-MM-dd"));

    settings.beginGroup(basePath);
    int totalRecords = settings.value("size", 0).toInt();

    //读取当天所有记录
    for (int i = 0; i < totalRecords; ++i) {
        QString recordPath = QString("%1").arg(i);
        settings.beginGroup(recordPath);

        int clothCount = settings.value("size", 0).toInt();
        QList<Cloth> outfit;

        //读取每件衣物
        for (int j = 0; j < clothCount; ++j) {
            settings.beginGroup(QString::number(j));
            outfit.append(loadFromSettings(settings));
            settings.endGroup();
        }

        result.append(outfit);
        settings.endGroup();
    }

    settings.endGroup();
    return result;
}
QList<Cloth> Cloth::getUserClothes(int userId)
{
    QList<Cloth>result;
    QSettings settings("magicCloset", "UserContent");
    settings.beginGroup(QString("id_%1").arg(userId));

    //获取当前衣物数组
    int size = settings.beginReadArray("clothes");
    if (size == 0) {
        settings.endArray();
        settings.endGroup();
        qDebug()<<"用户衣服数量为空！";
        return QList<Cloth>();
    }

    for (int i = 0; i < size; ++i) {
        settings.setArrayIndex(i);
        Cloth current = loadFromSettings(settings);
        result.append(current);
    }
    settings.endArray();
    settings.endGroup();
    return result;
}


