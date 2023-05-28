#pragma once

#include <QComboBox>
#include <QEvent>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGridLayout>
#include <QLayout>
#include <QMainWindow>
#include "scene.h"
#include <QResizeEvent>


class View : public QGraphicsView {
Q_OBJECT
public:
    View(LevelScene *scene = nullptr);


protected:

    void resizeEvent(QResizeEvent *event) override {
        QGraphicsView::resizeEvent(event);
        scene()->setSceneRect(QRectF(QPoint(0, 0), QPoint(event->size().width(), event->size().height())));
//        fitInView(scene()->sceneRect(), Qt::KeepAspectRatio);
    }

private:
};