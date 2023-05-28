#pragma once

#include <QComboBox>
#include <QEvent>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGridLayout>
#include <QLayout>
#include <QMainWindow>
#include <QGraphicsItem>


#include <QGraphicsItem>
#include <QPainter>
#include <QResizeEvent>
#include <QPaintEvent>
#include "../Level/hero.h"

class GraphicsHero : public QGraphicsItem {
public:
    GraphicsHero(int size, const Hero *hero);

    void setPos(const QPointF &pos);

protected:
    QRectF boundingRect() const override {
        return QRectF(0, 0, size_, size_);
    }

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;


private:
    std::vector<QPixmap> animationU_;
    std::vector<QPixmap> animationD_;
    std::vector<QPixmap> animationL_;
    std::vector<QPixmap> animationR_;
    QPointF currentPosition_;
    int size_;
    Path currentVec_;
    int pos_;
    int sg_;
    const Hero *hero_;
};