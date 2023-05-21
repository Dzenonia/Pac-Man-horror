#include "bot.h"
#include "hero.h"
#include "level_field.h"


class Level {
public:
    Level();

private:
    std::vector<Bot> ghosts_;
    Hero hero_;
    const LevelField *field_;
};