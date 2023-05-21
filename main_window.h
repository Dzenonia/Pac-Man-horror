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

class MainWindow : public QMainWindow {
Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr);

private:
    QWidget* showWidget_;
//    Controller* controller_;
    Scene* scene_;
    View* view_;
    QComboBox* mode_;
    QGridLayout* layout_;

};