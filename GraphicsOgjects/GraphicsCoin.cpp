
#include "GraphicsCoin.h"
#include <QDebug>

GraphicsCoin::GraphicsCoin(const QPointF &pos) : coinPixMap_(":resources/dot.png"), pos_(pos) {

}

void GraphicsCoin::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
//    painter->save();

//    qDebug() << "coinPos " << pos() << " " << coinPixMap_.size();

    painter->drawPixmap(pos_, coinPixMap_);

//    painter->restore();
}
