#include "controller.h"
#include "../GraphicsOgjects/Pac-Man.h"
#include "../GraphicsOgjects/GraphicsField.h"
#include <QDialog>
#include <QLabel>
#include <QApplication>
#include "../Level/field_generator.h"
#include <QPushButton>


ControllerLevel::ControllerLevel(ViewLevel *view, LevelScene *scene)
        : timer_(), view_(view), scene_(scene), level_(LevelField(generate::generateField(34, 28), 100)),
          hero_(new GraphicsHero(cellSize_, &level_.getHero())), rays_(level_.getField().getPolygons(cellSize_), 2),
          score_(new QGraphicsTextItem("0")),
          ghost_(new GraphicsGhost(cellSize_, &level_.getGhosts()[0])), countIter_(0) {
    level_.getGhosts()[0].setNewGoal(level_.getHero().getPos());
    setUpScore();
    setUpScene();
    timer_.start(16, this);
}


void ControllerLevel::timerEvent(QTimerEvent *event) {
    if (event->timerId() != timer_.timerId()) {
        QObject::timerEvent(event);
        return;
    }
    if (level_.getCountCoin() == 0) {
        theEnd();
    }
    ++countIter_;
    countIter_ %= 400;
    QPoint pos = level_.getHero().nextPosition();
    hero_->setPos(cellSize_ * QPoint(pos.y(), pos.x()) / 100);


    if ((pos.y()) % 100 == 0 && (pos.x()) % 100 == 0 &&
        level_.eatDot((pos.x()) / 100, (pos.y()) / 100)) {
        recheckScore(10);
        scene_->eatCoin((pos.x()) / 100, (pos.y()) / 100);
    }
    if (level_.getHero().getPos().x() % 100 == 0 && level_.getHero().getPos().y() % 100 == 0) {
        level_.getGhosts()[0].setNewGoal(level_.getHero().getPos());
    }

    QPoint posGhost = level_.getGhosts()[0].nextPosition();
    ghost_->setPos(cellSize_ * QPoint(posGhost.y(), posGhost.x()) / 100);

    if ((level_.getHero().getPos() == level_.getGhosts()[0].getPos())) {
        theEnd();
    }
    scene_->update();
    QObject::timerEvent(event);
}

void ControllerLevel::keyPress(Path vec) {
    level_.getHero().setVec(vec);

}

void ControllerLevel::recheckScore(ll val) {
    score_->setPlainText(QString::number(score_->toPlainText().toLongLong() + val));

}

void ControllerLevel::setUpScore() {
    score_->setPos(-100, 0);
    scene_->addItem(score_);
    score_->setDefaultTextColor(Qt::red);
    QFont font = score_->font();
    font.setPointSize(20);
    score_->setFont(font);
}

void ControllerLevel::setUpScene() {
    GraphicsField *graphicsLevel = new GraphicsField(level_.getField().getMatrix(), cellSize_);
    scene_->addItem(graphicsLevel);
    scene_->addItem(hero_);
    scene_->generateCoins(level_);
    scene_->addItem(ghost_);
    ghost_->setZValue(3);
    scene_->eatCoin(level_.getHero().getPos().x() / 100, level_.getHero().getPos().y() / 100);
    view_->setSceneRect(0, 100, QWidget::width(), QWidget::height());
    double scale = screen()->size().height() * 1.0 / (cellSize_ * level_.getField().getMatrix().size());
    view_->setTransform(QTransform::fromScale(scale, scale));


}

void ControllerLevel::theEnd() {
    timer_.stop();
    QDialog dialog;
    QVBoxLayout layout(&dialog);
    dialog.setWindowTitle("Конец!");

    QLabel label(QString("Ваш счет: ") + score_->toPlainText());
    layout.addWidget(&label);

    dialog.exec();
    QApplication::quit();
}




