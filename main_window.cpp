#include "main_window.h"
#include <QScreen>
#include <QTimer>
#include "GraphicsOgjects/GraphicsField.h"
#include "GraphicsOgjects/Pac-Man.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent),
                                          showWidget_(new QWidget(this)),
                                          scene_(new LevelScene(this)),
                                          view_(new ViewLevel(scene_)),
                                          layout_(new QGridLayout()),
                                          controller_(new ControllerLevel(view_, scene_)) {
    qDebug() << screen()->size();
//    resize(screen()->size());
    setWindowTitle("PAC-MAN-DUMDUM");
    showFullScreen();
    layout_->addWidget(view_, 0, 0);
    showWidget_->setLayout(layout_);
    view_->setMouseTracking(true);
    setCentralWidget(showWidget_);
    showWidget_->setMouseTracking(true);

}

void MainWindow::keyPressEvent(QKeyEvent *event) {
    qDebug() << event->text() << " " << Qt::Key_Down;
    switch (event->key()) {
        case Qt::Key_S:
            controller_->keyPress(Path::down);
            break;
        case Qt::Key_W:
            controller_->keyPress(Path::up);
            break;
        case Qt::Key_A:
            controller_->keyPress(Path::left);
            break;
        case Qt::Key_D:
            controller_->keyPress(Path::right);
            break;
        case Qt::Key_Escape:
            exit(0);
            break;
    }
}
