#include "level_graph.h"
#include <queue>

LevelGraph::LevelGraph(const LevelField &field) : field_(field) {}

std::vector<std::vector<int>> LevelGraph::bfs(int x, int y) {
    std::vector<std::vector<int>> distance(field_.width(), std::vector<int>(field_.height(), -1));
    distance[x][y] = 0;
    std::queue<QPoint> queue;
    queue.push(QPoint(x, y));
    while (!queue.empty()) {
        QPoint vertex = queue.front();
        queue.pop();
        for (int f1: {-1, 1}) {
            for (int f2: {-1, 1}) {
                if (field_.isWall(vertex + QPoint(f1, f2)) || distance[vertex.x() + f1][vertex.y() + f2] == -1) {
                    continue;
                }
                distance[vertex.x() + f1][vertex.y() + f2] = distance[vertex.x()][vertex.y()] + 1;
                queue.push(vertex + QPoint(f1, f2));
            }
        }
    }
    return distance;
}

std::vector<std::vector<std::vector<QPoint>>> LevelGraph::getEdges() const {
    std::vector<std::vector<std::vector<QPoint>>> listEdges(field_.width(),
                                                            std::vector<std::vector<QPoint>>(field_.height()));
    for (int i = 0; i < field_.width(); ++i) {
        for (int j = 0; j < field_.height(); ++j) {
            listEdges[i][j] = getVertexEdges(i, j);
        }
    }
}

std::vector<QPoint> LevelGraph::getVertexEdges(int x, int y) const {
    std::vector<QPoint> result;
    for (int f1: {-1, 1}) {
        for (int f2: {-1, 1}) {
            if (!field_.isWall(QPoint(x, y) + QPoint(f1, f2))) {
                result.push_back(QPoint(x, y) + QPoint(f1, f2));
            }
        }
    }
    return result;
}


