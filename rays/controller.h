#pragma once
#include "polygon.h"

class Controller {
public:
    Controller(int countDynamicLights = 1);

    void addVertexToLastPolygon(const QPointF& newVertex);
    void updateLastPolygon(const QPointF& newVertex);
    void setLightSource(const QPointF& light);
    void addPolygon(const Polygon& polygon);
    void addEmptyPolygon();
    void addStaticLight(const QPointF& center);

    const std::vector<Polygon>& getPolygons() const;
    const QPointF& getLightSource() const;
    const Polygon& getLastPolygon();


    std::vector<std::optional<Ray>> castRays(const QPointF& lightSource) const;
    void intersectRays(std::vector<std::optional<Ray>>& rays) const;
    void removeAdjacentRays(std::vector<std::optional<Ray>>& rays, double dist = 1) const;
    std::vector<Polygon> createDynamicLightArea() const;
    std::vector<Polygon> createStaticLightArea() const;
    const std::vector<QPointF>& getDynamicLights() const;
    const std::vector<QPointF>& getStaticLights() const;
    int countStaticLights() const;
    int countDynamicLights() const;

private:
    std::vector<Polygon> polygons_;
    QPointF lightSource_;
    std::vector<QPointF> dynamicLights_;
    std::vector<QPointF> staticLights_;

private:
    std::vector<Polygon> createAreas(const std::vector<QPointF>& sources) const;
};
