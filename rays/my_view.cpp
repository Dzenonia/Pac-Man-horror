#include "my_view.h"
#include <QMouseEvent>

GraphicsView::GraphicsView(GraphicsScene *scene, int countDynamicLights)
        : QGraphicsView(scene),
          mode_(Mode::light),
          scene_(scene),
          polygonsModePoints_(),
          countDynamicLights_(countDynamicLights) {
    setRenderHint(QPainter::Antialiasing, true);
    setRenderHint(QPainter::SmoothPixmapTransform, true);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setInteractive(false);
    setDragMode(QGraphicsView::NoDrag);
//    setSceneRect(0, 0, screen()->size().height(), screen()->size().width());
    setLightMode();
    setUpLights(countDynamicLights);
}

void GraphicsView::setLightMode() {
    setMouseTracking(true);
    setBackgroundBrush(Qt::black);
    mode_ = Mode::light;
    const auto &areas = scene_->getLightAreasItems();
    const auto &lights = scene_->getLightSourceItems();
    for (int i = 0; i < scene_->countLights(); ++i) {
        areas[i]->setVisible(true);
        lights[i]->setVisible(true);
    }
    for (auto point: polygonsModePoints_) {
        point->setVisible(false);
    }
}

void GraphicsView::resizeEvent(QResizeEvent *event) {
    QGraphicsView::resizeEvent(event);
    QSize newSize = event->size();
    setSceneRect(0, 0, newSize.width(), newSize.height());
}

void GraphicsView::mouseMoveEvent(QMouseEvent *event) {
    qDebug() << mapFromGlobal(cursor().pos());
    if (mode_ == Mode::light) {
        emit mouseMoveLights(mapFromGlobal(cursor().pos()));
    }
}

void GraphicsView::mousePressEvent(QMouseEvent *event) {
    switch (mode_) {
        case Mode::light:
            break;
        case Mode::polygons:
            if (event->button() == Qt::LeftButton) {
                pressLeftPolygons(mapFromGlobal(cursor().pos()));
            } else {
                pressRightPolygons();
            }
            break;
        case Mode::staticLight:
            if (event->button() == Qt::LeftButton) {
                emit mousePressLeftStaticLights(mapFromGlobal(cursor().pos()));
            }
            break;
    }
}

void GraphicsView::setMode(const GraphicsView::Mode &mode) {
    switch (mode) {
        case Mode::polygons:
            setPolygonsMode();
            break;
        case Mode::light:
            setLightMode();
            break;
        case Mode::staticLight:
            setStaticLightMode();
            break;
    }
}

void GraphicsView::setPolygonsMode() {
    setBackgroundBrush(Qt::white);
    const auto &areas = scene_->getLightAreasItems();
    const auto &lights = scene_->getLightSourceItems();
    for (int i = 0; i < scene_->countLights(); ++i) {
        areas[i]->setVisible(false);
        lights[i]->setVisible(false);
    }
    for (auto point: polygonsModePoints_) {
        point->setVisible(true);
    }
    mode_ = Mode::polygons;
}

void GraphicsView::setUpLights(int countLights) {

    for (int i = 0; i < countLights; ++i) {
        scene_->addLightArea(QPointF(0, 0));
        GraphicsPolygonItem *polygonItem = scene_->getLightAreasItems().back();
        QGraphicsEllipseItem *lightItem = scene_->getLightSourceItems().back();
        polygonItem->setBrush(QBrush(Qt::white));
        polygonItem->setPen(Qt::NoPen);
        polygonItem->setOpacity(0.5);
        lightItem->setBrush(Qt::red);
        lightItem->setPen(Qt::NoPen);
        lightItem->setZValue(1);
    }
}

GraphicsScene *GraphicsView::scene() const {
    return scene_;
}

void GraphicsView::updateLightArea(int numberArea, const Polygon &polygon, const QPointF &center) {
    if (numberArea >= scene_->countLights()) {
        return;
    }
    scene_->getLightAreasItems()[numberArea]->setPolygon(polygon);
    scene_->getLightSourceItems()[numberArea]->setRect(center.x(), center.y(), 2.5, 2.5);
}

void GraphicsView::updateLightArea(
        int numberArea, const Polygon &polygon, const QPointF &center, const QBrush &brushPolygon
) {
    if (numberArea >= scene_->countLights()) {
        return;
    }
    qDebug() << scene_->countLights() << '\n';
    scene_->getLightAreasItems()[numberArea]->setPolygon(polygon);
    scene_->getLightAreasItems()[numberArea]->setBrush(Qt::white);
    scene_->getLightAreasItems()[numberArea]->setVisible(true);
    scene_->getLightAreasItems()[numberArea]->setZValue(3);
    qDebug() << scene_->getLightAreasItems()[numberArea]->polygon() << " " << brushPolygon;
    scene_->getLightSourceItems()[numberArea]->setRect(center.x(), center.y(), 2.5, 2.5);
}

void GraphicsView::setStaticLightMode() {
    setBackgroundBrush(Qt::white);
    const auto &areas = scene_->getLightAreasItems();
    const auto &lights = scene_->getLightSourceItems();
    for (int i = 0; i < scene_->countLights(); ++i) {
        if (i < countDynamicLights_) {
            areas[i]->setVisible(false);
            lights[i]->setVisible(false);
            continue;
        }
        areas[i]->setVisible(false);
        lights[i]->setVisible(true);
    }
    for (auto point: polygonsModePoints_) {
        point->setVisible(true);
    }
    mode_ = Mode::staticLight;
}

GraphicsView::Mode GraphicsView::getCurrentMode() const {
    return mode_;
}

void GraphicsView::pressLeftPolygons(const QPointF &cursor) {
    QGraphicsEllipseItem *ellipseItem = new QGraphicsEllipseItem(cursor.x(), cursor.y(), 5, 5);
    ellipseItem->setBrush(Qt::black);
    scene_->addItem(ellipseItem);
    polygonsModePoints_.push_back(ellipseItem);
    emit mousePressLeftPolygons(cursor);
}

void GraphicsView::pressRightPolygons() {
    for (auto point: polygonsModePoints_) {
        scene_->removeItem(point);
        delete point;
    }
    polygonsModePoints_.clear();
    emit mousePressRightPolygons();
}
