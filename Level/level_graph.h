#pragma once

#include "level_field.h"

class LevelGraph {
public:
    LevelGraph(const LevelField &field);

    std::vector<std::vector<int>> bfs(int x, int y);

    std::vector<std::vector<std::vector<QPoint>>> getEdges() const;

    std::vector<QPoint> getVertexEdges(int x, int y) const;


private:
    const LevelField &field_;
};