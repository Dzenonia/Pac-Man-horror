#pragma once

#include <QComboBox>
#include <QEvent>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGridLayout>
#include <QLayout>
#include <QMainWindow>
#include "../Level/level.h"
#include <QGraphicsItem>
#include "../GraphicsOgjects/GraphicsCoin.h"
#include <QMouseEvent>


class LevelScene : public QGraphicsScene {
Q_OBJECT
public:
    LevelScene(QObject *parent = nullptr);

    void generateCoins(const Level &level);

    void mouseMoveEvent(QMouseEvent *event);

private:
    std::vector<std::vector<GraphicsCoin *>> coinObjects_;
};