#pragma once

#include <QPoint>
#include "level_field.h"

class Hero {
public:
    Hero(const LevelField *field, const QPoint &startPosition, int speed = 50);

    QPoint nextPosition();

    void setVec(Path vec);

    Path getVec() const;

    int getSpeed() const;

    QPoint getPos() const;

protected:
    const LevelField *const field_;
    QPoint currentPosition_;
    Path vec_;
    Path nextVec_;
    int speed_;

    QPoint next(const QPoint &position, Path vec) const;
};