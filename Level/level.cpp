#include "level.h"

Level::Level(const LevelField &field) : field_(field), hero_(&field_, QPoint(100, 100), 10),
                                        hasPoint_(field_.getMatrix()) {

}

Hero &Level::getHero() {
    return hero_;
}

const LevelField &Level::getField() const {
    return field_;
}

