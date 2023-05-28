#include "my_scene.h"

void GraphicsScene::addPolygon(const Polygon& polygon, const QBrush& brush, const QPen& pen) {
    GraphicsPolygonItem* newPolygonItem = new GraphicsPolygonItem(polygon);
    newPolygonItem->setBrush(brush);
    newPolygonItem->setPen(pen);
    addItem(newPolygonItem);
}

GraphicsScene::GraphicsScene(QObject* parent)
    : QGraphicsScene(parent), currentLightsSourcesItems_(), currentAreasItems_() { }

void GraphicsScene::addLightArea(const QPointF& lightSource, const Polygon& polygon) {
    GraphicsPolygonItem* newPolygonItem = new GraphicsPolygonItem(polygon);
    QGraphicsEllipseItem* newLightSource =
        new QGraphicsEllipseItem(lightSource.x(), lightSource.y(), 5, 5);
    newPolygonItem->setPen(Qt::NoPen);
    newPolygonItem->setOpacity(1);
    newLightSource->setBrush(QBrush(Qt::blue));
    newLightSource->setPen(Qt::NoPen);
    addItem(newPolygonItem);
    addItem(newLightSource);
    currentAreasItems_.push_back(newPolygonItem);
    currentLightsSourcesItems_.push_back(newLightSource);
}

const std::vector<QGraphicsEllipseItem*>& GraphicsScene::getLightSourceItems() const {
    return currentLightsSourcesItems_;
}

const std::vector<GraphicsPolygonItem*>& GraphicsScene::getLightAreasItems() const {
    return currentAreasItems_;
}

int GraphicsScene::countLights() const {
    return static_cast<int>(currentAreasItems_.size());
}

// int GraphicsScene::countStaticLights() const {
//     return static_cast<int>(staticLights_.size());
// }
