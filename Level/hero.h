#pragma once

#include <QPoint>
#include "level_field.h"

class Hero {
public:
    Hero(LevelField *field, const QPoint &startPosition);




private:
    const LevelField *const field_;
    QPoint currentPosition_;

};