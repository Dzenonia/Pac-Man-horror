#include "bot.h"

Bot::Bot(const LevelField *graphField, const QPoint &startPosition, int speed) : Hero(graphField, startPosition,
                                                                                      speed), graph_(*graphField) {
    setVec(Path::left);
}

QPoint Bot::nextPosition() {
    if (currentPosition_.x() % 100 == 0 && currentPosition_.y() % 100 == 0) {
        Path vec = graph_.getNext(currentPosition_ / 100, currentGoalPosition_ / 100);
        setVec(vec);

    }
    return Hero::nextPosition();
}

void Bot::setNewGoal(const QPoint &point) {
    currentGoalPosition_ = point;
}

const QPoint &Bot::getGoal() const {
    return currentGoalPosition_;
}
