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
#include <QScreen>

class GraphicsCoin : public QGraphicsItem {
public:
    GraphicsCoin(const QPointF& pos);


protected:

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

    QRectF boundingRect() const override {
        return QRectF(0, 0, 20, 20);
    }

private:
    QPixmap coinPixMap_;
    QPointF pos_;
};