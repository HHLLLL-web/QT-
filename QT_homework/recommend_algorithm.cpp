#include <QColor>
#include <QList>
#include <QSet>
#include <QPair>
#include <QtMath>
#include <QString>
#include <QSettings>
#include <algorithm>
#include "Cloth.h"
#include "recommend_algorithm.h"

//计算当前衣服颜色与用户偏好颜色的差异
float calculateColorHarmony(const QColor& color1,const QColor& color2){
    float hueDiff = qAbs(color1.hueF() - color2.hueF());
    if(hueDiff > 0.5f)
        hueDiff = 1.0f - hueDiff;
    float satDiff = qAbs(color1.saturationF() - color2.saturationF());//计算饱和度差异
    float valueDiff = qAbs(color1.valueF() - color2.valueF());//计算明度差异
    float harmonyScore = hueDiff * 0.6f + satDiff * 0.2f + valueDiff *0.2f;
    return 1.0f - harmonyScore;
}

float calculateMatchScore(const Cloth& item,const QString& occasion,const QString& season,const QString& weather,const int& temperature){
    float score = 0.0;
    if(occasion == "正式"){
        if(item.style() == "正式")//衣服风格的影响
            score += 0.8f;
        else if(item.style() == "商务")
            score += 0.6f;
        if(item.pattern() == "纯色" || item.pattern() == "条纹")//衣服图案
            score += 0.1f;
        else
            score -= 0.1f;
        if(item.getQColor().valueF() < 0.3f)
            score += 0.3f;
        else if(item.getQColor().saturationF() < 0.2f)
            score += 0.1f;
    }
    else if(occasion == "商务"){
        if(item.style() == "正式")
            score += 0.6f;
        else if(item.style() == "商务")
            score += 0.8f;
        if(item.pattern() == "纯色" || item.pattern() == "条纹")
            score += 0.1f;
        else
            score -= 0.1f;
        if(item.getQColor().valueF() < 0.3f)
            score += 0.3f;
        else if(item.getQColor().saturationF() < 0.2f)
            score += 0.1f;
    }
    else if(occasion == "休闲"){
        if(item.style() == "休闲" || item.style() == "运动")
            score += 0.8f;
        if(item.getQColor().saturationF() > 0.5f)
            score += 0.3f;
    }
    else if(occasion == "运动"){
        if(item.style() == "运动")
            score += 0.8f;
        if(item.getQColor().saturationF() > 0.7f)
            score += 0.3f;
    }
    else{
        if(item.style() == "美观")
            score += 0.8f;
        if(item.pattern() == "纯色" || item.pattern() == "印花")
            score += 0.1f;
        if(item.getQColor().saturationF() > 0.7f)
            score += 0.3f;
    }

    if(item.season() == season)
        score += 0.5f;
    if(season == "春"){//春季适合柔和的色调
        if(item.getQColor().hueF() >= 0.05f && item.getQColor().hueF() <= 0.2f && item.getQColor().saturationF() <= 0.7f)
            score += 0.2f;
    }
    else if(season == "夏"){//夏季适合明亮清爽的色调
        if((item.getQColor().hueF() <= 0.4f || item.getQColor().hueF() >= 0.55f) && item.getQColor().valueF() > 0.7f)
            score += 0.2f;
    }
    else if(season == "秋"){//秋季适合暖色调
        if(item.getQColor().hueF() >= 0.05f && item.getQColor().hueF() <= 0.15f)
            score += 0.2f;
    }
    else{//冬季适合深色和冷色调
        if((item.getQColor().hueF() <= 0.4f || item.getQColor().hueF() >= 0.55f) && item.getQColor().valueF() <= 0.7f)
            score += 0.2f;
    }

    if(weather == "下雨"){
        if(item.material() == "化纤" || item.material() == "羊毛")
            score += 0.1f;
        else if(item.material() == "麻")
            score += 0.3f;
    }
    else if(weather == "下雪"){
        if(item.thickness() == "厚")
            score += 0.6f;
        if(item.material() == "棉" || item.material() == "羊毛")
            score += 0.2f;
    }
    else if(weather == "大风"){
        if(item.thickness() == "中" || item.thickness() == "厚")
            score += 0.1f;
    }

    if(temperature < 5){
        if(item.thickness() == "厚")
            score += 0.8f;
        else
            score -= 2.0f;
        if(item.material() == "棉" ||item.material() == "麻" || item.material() == "羊毛")
            score += 0.5f;
    }
    else if(temperature < 15){
        if(item.thickness() == "厚")
            score += 0.5f;
        else
            score -= 1.0f;
        if(item.material() == "棉" ||item.material() == "麻" || item.material() == "羊毛")
            score += 0.2f;
    }
    else if(temperature < 28){
        if(item.thickness() == "中")
            score += 0.5f;
        else
            score -= 0.5f;
    }
    else{
        if(item.thickness() == "薄")
            score += 0.6f;
        else if(item.thickness() == "厚")
            score -= 2.0f;
        if(item.material() == "丝绸" || item.material() == "麻")
            score += 0.3f;
    }
    if(item.type() == Cloth::Dress && temperature >= 22 && temperature <= 36)
        score += 2.0f;
    return score;
}
QList<Cloth> recommendOutfit(const int& userID,const QString& occasion,const QString& season,
                             const QString& weather,const int temperature,const QColor& userPreferredColor){
    QList<Cloth> wardrobe = Cloth::getUserClothes(userID);

    QList<QPair<Cloth,float>> scoredItems;
    for(const auto& item : wardrobe){
        float score = calculateMatchScore(item,occasion,season,weather,temperature);
        scoredItems.append(qMakePair(item,score));
    }
    if(userPreferredColor.isValid()){
        for(auto& pair : scoredItems){
            float colorScore = calculateColorHarmony(pair.first.getQColor(),userPreferredColor);
            pair.second += colorScore*0.3f;
        }
    }
    std::sort(scoredItems.begin(),scoredItems.end(),
         [](const QPair<Cloth,float>&a,const QPair<Cloth,float>& b){
        return a.second > b.second;
    });
    QList<Cloth> recommendedOutfit;
    QSet<Cloth::Type> typesAdded;
    bool flag1 = true;
    bool flag2 = true;
    for(const auto& pair : scoredItems){
        const Cloth& item = pair.first;
        if(!typesAdded.contains(item.type())){
            if(flag1 && item.type() == Cloth::Dress){
                typesAdded.insert(item.type());
                recommendedOutfit.append(item);
                flag2 = false;
            }
            if(flag2 && (item.type() == Cloth::Top || item.type() == Cloth::Under)){
                typesAdded.insert(item.type());
                recommendedOutfit.append(item);
                flag1 = false;
            }
            if(item.type() == Cloth::Shoes){
                typesAdded.insert(item.type());
                recommendedOutfit.append(item);
            }
        }
        if(((typesAdded.contains(Cloth::Top) && typesAdded.contains(Cloth::Under))||typesAdded.contains(Cloth::Dress))&&typesAdded.contains(Cloth::Shoes))
            break;
    }
    return recommendedOutfit;
}
