#pragma once

#include <QComboBox>
#include <QEvent>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGridLayout>
#include <QLayout>
#include <QMainWindow>
#include "View/view.h"
#include "Controller/controller.h"
#include <QKeyEvent>

class MainWindow : public QMainWindow {
Q_OBJECT
    enum class scene {
        level,
        menu,
    };
public:
    MainWindow(QWidget *parent = nullptr);

    void keyPressEvent(QKeyEvent *event) override;

private:
    QWidget *showWidget_;
//    ControllerRays* controller_;
    LevelScene *scene_;
    ViewLevel *view_;
    QComboBox *mode_;
    QGridLayout *layout_;
    ControllerLevel *controller_;
};