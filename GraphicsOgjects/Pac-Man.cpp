#include "Pac-Man.h"

void GraphicsHero::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    painter->save();


    painter->setBrush(Qt::yellow);
    painter->setPen(Qt::NoPen);
    painter->drawEllipse(currentPosition_ + QPointF(size_ / 2, size_ / 2), size_ / 2, size_ / 2);

    painter->restore();
}

GraphicsHero::GraphicsHero(int size) : size_(size), currentPosition_(size, size) {

}

void GraphicsHero::setPos(const QPointF &pos) {
    currentPosition_ = pos;
    qDebug() << " !!!!!!!!!!!!!!!!!! " << currentPosition_;

}
