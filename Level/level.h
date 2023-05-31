#pragma once

#include "bot.h"
#include "hero.h"
#include "level_field.h"
#include "level_graph.h"


class Level {
public:
    Level(const LevelField &field);

    Hero &getHero();

    std::vector<Bot> &getGhosts();

    const LevelField &getField() const;

    const LevelGraph &getLevelGraph() const;

    bool eatDot(int i, int j);

private:
    LevelField field_;
    std::vector<Bot> ghosts_;
    Hero hero_;
    std::vector<std::vector<bool>> hasPoint_;
    LevelGraph levelGraph_;
};