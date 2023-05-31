#include "Pac-Man.h"

void GraphicsHero::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    painter->save();
    if (currentVec_ != hero_->getVec()) {
        currentVec_ = hero_->getVec();
        pos_ = 0;
        sg_ = 1;
    } else {
        if (pos_ >= 5) {
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
}

GraphicsHero::GraphicsHero(int size, const Hero *hero) : size_(size), currentPosition_(size * hero->getPos() / 100),
                                                         hero_(hero),
                                                         currentVec_(Path::right), pos_(0), sg_(1) {
    animationR_.push_back(QPixmap(":resources/a1.png"));
    animationR_.push_back(QPixmap(":resources/a2.png"));
    animationR_.push_back(QPixmap(":resources/a3.png"));
    animationR_.push_back(QPixmap(":resources/a4.png"));
    animationR_.push_back(QPixmap(":resources/a5.png"));
    animationR_.push_back(QPixmap(":resources/a6.png"));

    animationU_.push_back(QPixmap(":resources/a1.png"));
    animationU_.push_back(QPixmap(":resources/b2.png"));
    animationU_.push_back(QPixmap(":resources/b3.png"));
    animationU_.push_back(QPixmap(":resources/b4.png"));
    animationU_.push_back(QPixmap(":resources/b5.png"));
    animationU_.push_back(QPixmap(":resources/b6.png"));

    animationL_.push_back(QPixmap(":resources/a1.png"));
    animationL_.push_back(QPixmap(":resources/c2.png"));
    animationL_.push_back(QPixmap(":resources/c3.png"));
    animationL_.push_back(QPixmap(":resources/c4.png"));
    animationL_.push_back(QPixmap(":resources/c5.png"));
    animationL_.push_back(QPixmap(":resources/c6.png"));

    animationD_.push_back(QPixmap(":resources/a1.png"));
    animationD_.push_back(QPixmap(":resources/d2.png"));
    animationD_.push_back(QPixmap(":resources/d3.png"));
    animationD_.push_back(QPixmap(":resources/d4.png"));
    animationD_.push_back(QPixmap(":resources/d5.png"));
    animationD_.push_back(QPixmap(":resources/d6.png"));
}

void GraphicsHero::setPos(const QPointF &pos) {
    currentPosition_ = pos;
}
