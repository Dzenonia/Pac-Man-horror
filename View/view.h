#pragma once

#include <QComboBox>
#include <QEvent>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGridLayout>
#include <QLayout>
#include <QMainWindow>
#include "scene.h"


class View : public QGraphicsView {
Q_OBJECT
public:
    View(Scene *scene = nullptr);

private:
};