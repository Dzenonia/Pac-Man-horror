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

class GraphicsField : public QGraphicsItem {
public:
    GraphicsField(const std::vector<std::vector<bool>> &fieldMatrix, int cellSize);

    QRectF boundingRect() const override;

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

private:
    std::vector<std::vector<bool>> fieldMatrix_;
    int cellSize_;
};
