#include "GraphicsGhost.h"

void GraphicsGhost::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    painter->save();
    if (currentVec_ != hero_->getVec()) {
        currentVec_ = hero_->getVec();
        pos_ = 0;
        sg_ = 1;
    } else {
        if (pos_ >= 1) {
            sg_ = -1;
        }
        if (pos_ <= 0) {
            sg_ = 1;
        }
        pos_ += sg_;
    }
    switch (currentVec_) {

        case Path::left:
            painter->drawPixmap(currentPosition_, animationL_[pos_]);
            break;
        case Path::right:
            painter->drawPixmap(currentPosition_, animationR_[pos_]);
            break;
        case Path::down:
            painter->drawPixmap(currentPosition_, animationD_[pos_]);
            break;
        case Path::up:
            painter->drawPixmap(currentPosition_, animationU_[pos_]);
            break;
    }
    painter->restore();
//    painter->save();
//
//
//    painter->setBrush(Qt::yellow);
//    painter->setPen(Qt::NoPen);
//    painter->drawEllipse(currentPosition_ + QPointF(size_ / 2, size_ / 2), size_ / 2, size_ / 2);
//
//    painter->restore();
}

GraphicsGhost::GraphicsGhost(int size, const Hero *hero) : size_(size), currentPosition_(size * (hero->getPos() / 100)),
                                                           hero_(hero),
                                                           currentVec_(hero->getVec()), pos_(0), sg_(1) {

    animationR_.push_back(QPixmap(":resources/redright1.png"));
    animationR_.push_back(QPixmap(":resources/redright2.png"));

    animationL_.push_back(QPixmap(":resources/redleft1.png"));
    animationL_.push_back(QPixmap(":resources/redleft2.png"));

    animationU_.push_back(QPixmap(":resources/redup1.png"));
    animationU_.push_back(QPixmap(":resources/redup2.png"));

    animationD_.push_back(QPixmap(":resources/reddown1.png"));
    animationD_.push_back(QPixmap(":resources/reddown2.png"));
}

void GraphicsGhost::setPos(const QPointF &pos) {
    currentPosition_ = pos;
}
