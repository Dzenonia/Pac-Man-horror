#include "level.h"

Level::Level(const LevelField &field) : field_(field), hero_(&field_, QPoint(100, 100), 5) {

}

Hero &Level::getHero() {
    return hero_;
}

