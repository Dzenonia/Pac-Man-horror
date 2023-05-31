#include "level.h"

Level::Level(const LevelField &field) : field_(field), hero_(&field_, QPoint(100, 100), 10),
                                        hasPoint_(field_.getMatrix()), levelGraph_(field_) {

    ghosts_.push_back(Bot(&field_, QPoint(field.height() * 100 - 200, field.width() * 100 - 200), 10));
}

Hero &Level::getHero() {
    return hero_;
}

const LevelField &Level::getField() const {
    return field_;
}

const LevelGraph &Level::getLevelGraph() const {
    return levelGraph_;
}

std::vector<Bot> &Level::getGhosts() {
    return ghosts_;
}

bool Level::eatDot(int i, int j) {
    qDebug() << i << " kkkkk " << j;
    bool dot = hasPoint_[i][j];
    hasPoint_[i][j] = 1;
    return !dot;
}

