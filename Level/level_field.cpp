#include "level_field.h"

LevelField::LevelField(int width, int height) : field_(width, std::vector<bool>(height, 1)) {}

LevelField::LevelField(const std::vector<std::vector<bool>> &field) : field_(field) {}

const std::vector<std::vector<bool>> &LevelField::getMatrix() const {
    return field_;
}

void LevelField::setMatrix(const std::vector<std::vector<bool>> &field) {
    field_ = field;
}

std::vector<QPoint> LevelField::freeCells() const {
    std::vector<QPoint> result;
    for (int i = 0; i < field_.size(); ++i) {
        for (int j = 0; j < field_[i].size(); ++j) {
            if (!field_[i][j]) {
                result.push_back(QPoint(i, j));
            }
        }
    }
    return result;
}

std::vector<QPoint> LevelField::wallCells() const {
    std::vector<QPoint> result;
    for (int i = 0; i < field_.size(); ++i) {
        for (int j = 0; j < field_[i].size(); ++j) {
            if (field_[i][j]) {
                result.push_back(QPoint(i, j));
            }
        }
    }
    return result;
}

bool LevelField::isWall(int x, int y) const {
    if (x < 0 || x >= field_.size() || y < 0 || y >= field_[0].size()) {
        return true;
    }
    return field_[x][y];
}

bool LevelField::isWall(const QPoint &position) const {
    return isWall(position.x(), position.y());
}

LevelField::LevelField() : field_() {}

int LevelField::height() const {
    return static_cast<int>(field_.size());
}

int LevelField::width() const {
    return static_cast<int>(field_[0].size());
}
