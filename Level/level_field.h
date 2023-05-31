#pragma once

#include <vector>
#include <QPoint>
#include "../rays/polygon.h"

// 1 -- wall
// 0 -- free cell

class LevelField {
public:
    LevelField();

    LevelField(int width, int height);

    LevelField(const std::vector<std::vector<bool>> &field, int scale);

    const std::vector<std::vector<bool>> &getMatrix() const;

    void setMatrix(const std::vector<std::vector<bool>> &field);

    std::vector<QPoint> freeCells() const;

    std::vector<QPoint> wallCells() const;

    int height() const;

    int width() const;

    void setScale(int scale);

    bool isWall(int x, int y) const;

    bool isWall(const QPoint &position) const;

    bool isWallNotScale(int i, int j) const;

    std::vector<Polygon> getPolygons(double cellSize) const;

    std::vector<Polygon> nearPolygons(double cellSize, int x, int y) const;

private:
    std::vector<std::vector<bool>> field_;
    int scale_ = 1;
    int maxStep = 1;
};

enum class Path {
    none1,
    none2,
    left,
    right,
    down,
    up
};