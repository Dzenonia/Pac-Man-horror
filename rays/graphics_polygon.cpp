#include "graphics_polygon.h"

GraphicsPolygonItem::GraphicsPolygonItem(const Polygon& polygon, QGraphicsItem* parent)
    : QGraphicsPolygonItem(parent) {
    setPolygon(polygon);
}

void GraphicsPolygonItem::setPolygon(const Polygon& polygon) {
    QList<QPointF> list;
    const auto& vertices = polygon.getVertices();
    for (const QPointF& vertex : vertices) {
        list.push_back(vertex);
    }
    QGraphicsPolygonItem::setPolygon(list);
}
