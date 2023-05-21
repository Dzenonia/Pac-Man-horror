#pragma once

#include <QComboBox>
#include <QEvent>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGridLayout>
#include <QLayout>
#include <QMainWindow>


class Scene : public QGraphicsScene {
Q_OBJECT
public:
    Scene(QObject *parent = nullptr);

private:
};