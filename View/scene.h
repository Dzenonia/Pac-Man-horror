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
#include "../rays/my_scene.h"


class LevelScene : public GraphicsScene {
Q_OBJECT
public:
    LevelScene(QObject *parent = nullptr);

    void generateCoins(const Level &level);

    void mouseMoveEvent(QMouseEvent *event);

    void eatCoin(int i, int j);

private:
    std::vector<std::vector<GraphicsCoin *>> coinObjects_;
};