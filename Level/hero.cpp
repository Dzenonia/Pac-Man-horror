#include "hero.h"

Hero::Hero(const LevelField *field, const QPoint &startPosition, int speed) : field_(field),
                                                                              currentPosition_(startPosition),
                                                                              vec_(Path::right), speed_(speed),
                                                                              nextVec_(Path::right) {}

QPoint Hero::nextPosition() {
    if (next(currentPosition_, nextVec_) != currentPosition_) {
        vec_ = nextVec_;
        nextVec_ = vec_;
    }
    switch (vec_) {
        case Path::left:
            field_->isWall(currentPosition_ + QPoint(0, -1) * speed_) ? currentPosition_ : currentPosition_ +=
                                                                                                   QPoint(0, -1) *
                                                                                                   speed_;
            break;
        case Path::right:
            field_->isWall(currentPosition_ + QPoint(0, 1) * speed_) ? currentPosition_ : currentPosition_ +=
                                                                                                  QPoint(0, 1) * speed_;
            break;
        case Path::down:
            field_->isWall(currentPosition_ + QPoint(1, 0) * speed_) ? currentPosition_ : currentPosition_ +=
                                                                                                  QPoint(1, 0) * speed_;
            break;
        case Path::up:
            field_->isWall(currentPosition_ + QPoint(-1, 0) * speed_) ? currentPosition_ : currentPosition_ +=
                                                                                                   QPoint(-1, 0) *
                                                                                                   speed_;
            break;
    }
    return currentPosition_;
}


void Hero::setVec(Path vec) {
    QPoint pos = next(currentPosition_, vec);
    if (pos != currentPosition_) {
        vec_ = vec;
        nextVec_ = vec_;
        return;
    }

    nextVec_ = vec;
}

QPoint Hero::next(const QPoint &position, Path vec) const {
    QPoint res = position;
    switch (vec) {
        case Path::left:
            field_->isWall(res + QPoint(0, -1) * speed_) ? res : res +=
                                                                         QPoint(0, -1) *
                                                                         speed_;
            return res;
        case Path::right:
            field_->isWall(res + QPoint(0, 1) * speed_) ? res : res +=
                                                                        QPoint(0, 1) * speed_;
            return res;
        case Path::down:
            field_->isWall(res + QPoint(1, 0) * speed_) ? res : res +=
                                                                        QPoint(1, 0) * speed_;
            return res;
        case Path::up:
            field_->isWall(res + QPoint(-1, 0) * speed_) ? res : res +=
                                                                         QPoint(-1, 0) *
                                                                         speed_;
            return res;
    }
}

