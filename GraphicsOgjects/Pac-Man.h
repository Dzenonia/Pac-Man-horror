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

class GraphicsHero : public QGraphicsItem {
public:
    GraphicsHero(int size);

    void setPos(const QPointF &pos);

protected:
    QRectF boundingRect() const override {
        return QRectF(0, 0, size_, size_);
    }

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;


private:
    std::vector<QPixmap> animation_;
    QPointF currentPosition_;
    int size_;
};