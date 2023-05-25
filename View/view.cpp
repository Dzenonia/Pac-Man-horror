#include "view.h"

View::View(Scene *scene) : QGraphicsView(scene) {
//    setSceneRect(0, 0, QWidget::width(), QWidget::height());
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
}

void View::mouseMoveEvent(QMouseEvent *event) {

}
