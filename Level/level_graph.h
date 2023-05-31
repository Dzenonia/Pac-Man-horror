#pragma once

#include "level_field.h"

class LevelGraph {
public:
    LevelGraph(const LevelField &field);

    std::vector<std::vector<Path>> bfs(int x, int y);

    std::vector<std::vector<std::vector<QPoint>>> getEdges() const;

    std::vector<QPoint> getVertexEdges(int x, int y) const;

    Path getNext(const QPoint &from, const QPoint &to);


private:
    const LevelField &field_;

    std::map<std::pair<std::pair<int, int>, std::pair<int, int>>, Path> next_;
};