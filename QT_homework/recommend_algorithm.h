#ifndef RECOMMEND_ALGORITHM_H
#define RECOMMEND_ALGORITHM_H

#include <QString>
#include <QColor>
#include <QList>
#include "Cloth.h"
#pragma once

float calculateColorHarmony(const QColor& color1,const QColor& color2);
float calculateMatchScore(const Cloth& item,const QString& occasion,const QString& season,const QString& weather,const int& temperature);
QList<Cloth> recommendOutfit(const int& userID,const QString& occasion,const QString& season,
                             const QString& weather,const int temperature,const QColor& userPreferredColor = QColor());

#endif // RECOMMEND_ALGORITHM_H
