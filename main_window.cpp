#include "main_window.h"
#include <QScreen>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent),
                                          showWidget_(new QWidget(this)),
                                          scene_(new Scene(this)),
                                          view_(new View(scene_)),
                                          layout_(new QGridLayout()) {
    qDebug() << screen()->size();
    resize(screen()->size());
    setWindowTitle("PAC-MAN-DUMDUM");
//    mode_->addItem("light");
//    mode_->addItem("polygons");
//    mode_->addItem("static-lights");
//    layout_->addWidget(mode_, 0, 0);
    layout_->addWidget(view_, 0, 0);
    showWidget_->setLayout(layout_);
    view_->setMouseTracking(true);
    setCentralWidget(showWidget_);
    showWidget_->setMouseTracking(true);
}
