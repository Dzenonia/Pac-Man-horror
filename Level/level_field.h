#pragma once

#include <vector>
#include <QPoint>

// 1 -- wall
// 0 -- free cell

class LevelField {
public:
    LevelField();

    LevelField(int width, int height);

    LevelField(const std::vector<std::vector<bool>> &field);

    const std::vector<std::vector<bool>> &getMatrix() const;

    void setMatrix(const std::vector<std::vector<bool>> &field);

    std::vector<QPoint> freeCells() const;

    std::vector<QPoint> wallCells() const;

    int height() const;

    int width() const;

    bool isWall(int x, int y) const;

    bool isWall(const QPoint &position) const;

private:
    std::vector<std::vector<bool>> field_;
};

enum class Path {
    left,
    right,
    down,
    up
};