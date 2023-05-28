#pragma once
#include "bot.h"
#include "hero.h"
#include "level_field.h"


class Level {
public:
    Level(const LevelField &field);

    Hero &getHero();

    const LevelField &getField() const;

private:
    LevelField field_;
    std::vector<Bot> ghosts_;
    Hero hero_;
    std::vector<std::vector<bool>> hasPoint_;
};