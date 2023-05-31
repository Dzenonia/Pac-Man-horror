#include "view.h"

ViewLevel::ViewLevel(LevelScene *scene) : GraphicsView(scene, 1) {
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setRenderHint(QPainter::Antialiasing);
    setRenderHint(QPainter::SmoothPixmapTransform);


//    fitInView(mapRect, Qt::KeepAspectRatio);

    QTransform transform = this->transform();
//    transform.scale(1.55, 1.55);
//    transform.translate(1000, 1000);
//    translate(1000, 1000);
//    scroll(1000, 1000);
}

