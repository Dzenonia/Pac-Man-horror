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
public:
    MainWindow(QWidget *parent = nullptr);

    void keyPressEvent(QKeyEvent *event) override;

private:
    QWidget *showWidget_;
//    Controller* controller_;
    LevelScene *scene_;
    View *view_;
    QComboBox *mode_;
    QGridLayout *layout_;
    Controller *controller_;
};