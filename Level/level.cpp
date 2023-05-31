#include "level.h"

Level::Level(const LevelField &field) : field_(field), hero_(&field_, field.freeCells()[0] * 100, 10),
                                        hasPoint_(field_.getMatrix()), levelGraph_(field_) {

    ghosts_.push_back(Bot(&field_, field.freeCells().back() * 100, 10));
    countCoin_ = field_.freeCells().size();
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
    bool dot = hasPoint_[i][j];
    countCoin_ -= !dot;
    hasPoint_[i][j] = 1;
    return !dot;
}


int Level::getCountCoin() const {
    return countCoin_;
}

