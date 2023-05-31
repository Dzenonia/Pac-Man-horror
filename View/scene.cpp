#include "scene.h"

LevelScene::LevelScene(QObject *parent) : GraphicsScene(parent) {

}

void LevelScene::generateCoins(const Level &level) {
    coinObjects_.resize(level.getField().height(),
                        std::vector<GraphicsCoin *>(
                                level.getField().width(),
                                nullptr));
    qDebug() << level.getField().getMatrix().size();
    for (int i = 0; i < level.getField().height(); ++i) {
        for (int j = 0; j < level.getField().width(); ++j) {
            if (!level.getField().getMatrix()[i][j]) {
                qDebug() << 20 * j << " " << 20 * i;
                coinObjects_[i][j] = new GraphicsCoin(QPointF(20 * j, 20 * i));
                coinObjects_[i][j]->setZValue(2);
//                coinObjects_[i][j]->setPos(20 * i, 20 * j);
                addItem(coinObjects_[i][j]);
            }
        }
    }
}

void LevelScene::mouseMoveEvent(QMouseEvent *event) {
    qDebug() << event->pos();
}

void LevelScene::eatCoin(int i, int j) {
    if (coinObjects_[i][j] == nullptr) {
        return;
    }
    delete coinObjects_[i][j];
    coinObjects_[i][j] = nullptr;
}
