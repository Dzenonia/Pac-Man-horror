#pragma once
#include "controllerRays.h"
#include "graphics_polygon.h"
#include "my_view.h"
#include <QComboBox>
#include <QEvent>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGridLayout>
#include <QLayout>
#include <QMainWindow>

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    static QBrush basePolygonBrush;
    static QPen basePolygonPen;
    MainWindow();
    ~MainWindow();


private:
    void updateLightArea();
    void updateStaticLight();
    void setUpStyle();
    void setUpLayout();
    void setUpBasePolygons();

private:
    QWidget* showWidget_;
    Controller* controller_;
    GraphicsScene* scene_;
    GraphicsView* view_;
    QComboBox* mode_;
    QGridLayout* layout_;
};
