#pragma once

#include "graphics_polygon.h"
#include "polygon.h"
#include <QGraphicsEllipseItem>
#include <QGraphicsScene>

class GraphicsScene : public QGraphicsScene {
    Q_OBJECT

public:
    GraphicsScene(QObject* parent = nullptr);
    void
    addPolygon(const Polygon& polygon, const QBrush& brush = QBrush(), const QPen& pen = QPen());

    const std::vector<GraphicsPolygonItem*>& getLightAreasItems() const;
    const std::vector<QGraphicsEllipseItem*>& getLightSourceItems() const;
    int countLights() const;

    void addLightArea(const QPointF& lightSource, const Polygon& polygon = Polygon());

private:
    std::vector<GraphicsPolygonItem*> currentAreasItems_;
    std::vector<QGraphicsEllipseItem*> currentLightsSourcesItems_;
};