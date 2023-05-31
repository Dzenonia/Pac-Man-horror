#pragma once

#include <QPoint>
#include "level_graph.h"
#include "hero.h"

class Bot : public Hero {
public:
    Bot(const LevelField *graphField, const QPoint &startPosition, int speed = 50);

    QPoint nextPosition();

    void setNewGoal(const QPoint &point);

    const QPoint &getGoal() const;

private:
    LevelGraph graph_;

    QPoint currentGoalPosition_;
};