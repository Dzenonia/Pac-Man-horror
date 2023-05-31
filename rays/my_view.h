#pragma once
#include "my_scene.h"
#include <QCursor>
#include <QGraphicsEllipseItem>
#include <QGraphicsView>


class GraphicsView : public QGraphicsView {
    Q_OBJECT

public:
    enum class Mode { light, polygons, staticLight };

public:
    GraphicsView(GraphicsScene* scene, int countDynamicLights = 0);


    void setLightMode();
    void setPolygonsMode();
    void setStaticLightMode();
    void setMode(const Mode& mode);
    void updateLightArea(int numberArea, const Polygon& polygon, const QPointF& center);
    void updateLightArea(
        int numberArea, const Polygon& polygon, const QPointF& center, const QBrush& brushPolygon
    );

    Mode getCurrentMode() const;
    GraphicsScene* scene() const;


protected:
    void resizeEvent(QResizeEvent* event) override;

    void mouseMoveEvent(QMouseEvent* event) override;

    void mousePressEvent(QMouseEvent* event) override;


public:
signals:
    void mousePressLeftPolygons(const QPointF& vertex);
    void mousePressRightPolygons();
    void mouseMoveLights(const QPointF& cursor);
    void mousePressLeftStaticLights(const QPointF& cursor);


private:
    Mode mode_;
    GraphicsScene* scene_;
    std::vector<QGraphicsEllipseItem*> polygonsModePoints_;
    int countDynamicLights_;


    void setUpLights(int countLights);
    void pressLeftPolygons(const QPointF& cursor);
    void pressRightPolygons();
};