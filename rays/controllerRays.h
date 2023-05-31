#pragma once

#include "polygon.h"
#include "../Level/level_field.h"
#include <hash_map>
#include <QHash>
#include <QPointF>

class ControllerRays {
public:
    ControllerRays(const std::vector<Polygon> &polygons = {}, int countDynamicLights = 1);

    void setPolygons(const std::vector<Polygon> &polygons);

    void addVertexToLastPolygon(const QPointF &newVertex);

    void updateLastPolygon(const QPointF &newVertex);

    void setLightSource(const QPointF &light);

    void addPolygon(const Polygon &polygon);

    void addEmptyPolygon();

    void addStaticLight(const QPointF &center);

    const std::vector<Polygon> &getPolygons() const;

    const QPointF &getLightSource() const;

    const Polygon &getLastPolygon();


    std::vector<std::optional<Ray>> castRays(const QPointF &lightSource) const;

    void intersectRays(std::vector<std::optional<Ray>> &rays) const;

    void removeAdjacentRays(std::vector<std::optional<Ray>> &rays, double dist = 1) const;

    std::vector<Polygon> createDynamicLightArea() const;

    std::vector<Polygon> createStaticLightArea() const;

    const std::vector<QPointF> &getDynamicLights() const;

    const std::vector<QPointF> &getStaticLights() const;

    int countStaticLights() const;

    int countDynamicLights() const;

    void prec(const LevelField &field, int dis, double cellSize);

    const std::vector<Polygon> getPrecPolygons(const QPoint& point) const;

private:
    std::vector<Polygon> polygons_;
    QPointF lightSource_;
    std::vector<QPointF> dynamicLights_;
    std::vector<QPointF> staticLights_;

    QHash<QPoint, std::vector<Polygon>> hashAreas_;

private:
    std::vector<Polygon> createAreas(const std::vector<QPointF> &sources) const;
};
