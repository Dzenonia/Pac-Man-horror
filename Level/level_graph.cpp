#include "level_graph.h"
#include <queue>

LevelGraph::LevelGraph(const LevelField &field) : field_(field) {
//    qDebug() << field.width() << " " << field.height() << " HE";
    for (int i = 0; i < field.height(); ++i) {
        for (int j = 0; j < field.width(); ++j) {
            if (field.isWallNotScale(i, j)) {
                continue;
            }
            auto vec = bfs(i, j);
//            qDebug() << i << " " << j;
            for (int i1 = 0; i1 < field.height(); ++i1) {
                for (int j1 = 0; j1 < field.width(); ++j1) {
                    if (field.isWallNotScale(i1, j1)) {
                        continue;
                    }
//                    qDebug() << i << " " << j;
                    next_[{{i1, j1},
                           {i,  j}}] = vec[i1][j1];
//                    qDebug() << i1 << " " << j1 << " " << i << " " << j << " " << int(vec[i1][j1]);
                }
            }
        }
    }
}


std::vector<std::vector<Path>> LevelGraph::bfs(int x, int y) {
    std::vector<std::vector<Path>> pre(field_.height(), std::vector<Path>(field_.width(), Path::none1));
    pre[x][y] = Path::none2;
    std::queue<QPoint> queue;
    queue.push(QPoint(x, y));
    while (!queue.empty()) {
        QPoint vertex = queue.front();
        queue.pop();
        for (int f1: {-1, 1}) {
            for (int f2: {0}) {
                if (field_.isWallNotScale((vertex + QPoint(f1, f2)).x(), (vertex + QPoint(f1, f2)).y()) ||
                    pre[vertex.x() + f1][vertex.y() + f2] != Path::none1) {
                    continue;
                }
                if (f1 == -1) {
                    pre[vertex.x() + f1][vertex.y() + f2] = Path::down;
                } else {
                    pre[vertex.x() + f1][vertex.y() + f2] = Path::up;
                }

                queue.push(vertex + QPoint(f1, f2));
            }
        }


        for (int f1: {0}) {
            for (int f2: {-1, 1}) {
                if (field_.isWallNotScale((vertex + QPoint(f1, f2)).x(), (vertex + QPoint(f1, f2)).y()) ||
                    pre[vertex.x() + f1][vertex.y() + f2] != Path::none1) {
                    continue;
                }
                if (f2 == -1) {
                    pre[vertex.x() + f1][vertex.y() + f2] = Path::right;
                } else {
                    pre[vertex.x() + f1][vertex.y() + f2] = Path::left;
                }
                queue.push(vertex + QPoint(f1, f2));
            }
        }
    }
    return pre;
}

std::vector<std::vector<std::vector<QPoint>>> LevelGraph::getEdges() const {
    std::vector<std::vector<std::vector<QPoint>>> listEdges(field_.height(),
                                                            std::vector<std::vector<QPoint>>(field_.width()));
    for (int i = 0; i < field_.height(); ++i) {
        for (int j = 0; j < field_.width(); ++j) {
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

Path LevelGraph::getNext(const QPoint &from, const QPoint &to) {
    qDebug() << from << " " << to << " POSITIONS" << " " << int(next_[{{from.x(), from.y()},
                                                                       {to.x(),   to.y()}}]);
    return next_[{{from.x(), from.y()},
                  {to.x(),   to.y()}}];
}


