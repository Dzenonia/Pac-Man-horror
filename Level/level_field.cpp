#include "level_field.h"
#include <QDebug>

LevelField::LevelField(int width, int height) : field_(width, std::vector<bool>(height, 1)) {}

LevelField::LevelField(const std::vector<std::vector<bool>> &field, int scale) : field_(field), scale_(scale) {}

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

bool LevelField::isWallNotScale(int x, int y) const {
    if (x < 0 || x >= field_.size() || y < 0 || y >= field_[0].size()) {
        return true;
    }
    return field_[x][y];
}

bool LevelField::isWall(int x, int y) const {
    if ((x % scale_) != 0 && (y % scale_) != 0) {
        return true;
    }
//    x += scale_ - 1;
//    y += scale_ - 1;
    int x1 = (x + scale_ - 1) / scale_;
    int y1 = (y + scale_ - 1) / scale_;
    x /= scale_;
    y /= scale_;

    if (x < 0 || x >= field_.size() || y < 0 || y >= field_[0].size()) {
        return true;
    }
    return field_[x][y] || field_[x1][y1];
}

bool LevelField::isWall(const QPoint &position) const {
    return isWall(position.x(), position.y());
}

LevelField::LevelField() : field_() {

}

int LevelField::height() const {
    return static_cast<int>(field_.size());
}

int LevelField::width() const {
    return static_cast<int>(field_[0].size());
}

void LevelField::setScale(int scale) {
    scale_ = scale;
}

std::vector<Polygon> LevelField::getPolygons(double cellSize) const {
    std::vector<Polygon> res;
    for (int i = 0; i < height(); ++i) {
        for (int j = 0; j < width(); ++j) {
            if (!field_[i][j]) {
                continue;
            }
            Polygon newPolygon({QPointF(j * cellSize, i * cellSize), QPointF(j * cellSize + cellSize, i * cellSize),
                                QPointF(j * cellSize + cellSize, i * cellSize),
                                QPointF(j * cellSize + cellSize, i * cellSize + cellSize)});
            res.push_back(newPolygon);
        }
    }
    return res;
}

std::vector<Polygon> LevelField::nearPolygons(double cellSize, int x, int y) const {
    std::vector<Polygon> res;
    for (int i = x - maxStep; i <= x + maxStep; ++i) {
        for (int j = y - maxStep; j <= y + maxStep; ++j) {
            if (i <= 0 || i >= field_.size() || j <= 0 || j >= field_[0].size() || !isWallNotScale(i, j)) {
                continue;
            }
            Polygon newPolygon({QPointF(j * cellSize, i * cellSize), QPointF(j * cellSize + cellSize, i * cellSize),
                                QPointF(j * cellSize + cellSize, i * cellSize + cellSize),
                                QPointF(j * cellSize, i * cellSize + cellSize)});
            res.push_back(newPolygon);
        }
    }
    return res;
}
