#include "controller.h"
#include "../GraphicsOgjects/Pac-Man.h"
#include "../GraphicsOgjects/GraphicsField.h"

Controller::Controller(View *view, LevelScene *scene)
        : timer_(), view_(view), scene_(scene), level_(LevelField(field, 100)),
          hero_(new GraphicsHero(cellSize_, &level_.getHero())) {
    GraphicsField *graphicsLevel = new GraphicsField(field, cellSize_);
    scene_->addItem(graphicsLevel);
    scene_->addItem(hero_);
    scene_->generateCoins(level_);
    timer_.start(16, this);
}


void Controller::timerEvent(QTimerEvent *event) {
    if (event->timerId() == timer_.timerId()) {
        QPoint pos = level_.getHero().nextPosition();
//        qDebug() << pos;
        hero_->setPos(cellSize_ * QPoint(pos.y(), pos.x()) / 100);
        scene_->update();
    }
    QObject::timerEvent(event);
}

void Controller::keyPress(Path vec) {
    qDebug() << " KEY ============" << int(vec);
    level_.getHero().setVec(vec);

}


