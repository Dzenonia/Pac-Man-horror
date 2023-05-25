#include "bot.h"
#include "hero.h"
#include "level_field.h"


class Level {
public:
    Level(const LevelField &field);

    Hero &getHero();

private:
    LevelField field_;
    std::vector<Bot> ghosts_;
    Hero hero_;
};