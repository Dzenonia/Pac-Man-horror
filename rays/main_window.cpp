#include "main_window.h"
#include <QApplication>
#include <QBrush>
#include <QDebug>
#include <QScreen>
#include <iostream>

QBrush MainWindow::basePolygonBrush = QBrush();
QPen MainWindow::basePolygonPen = QPen();

MainWindow::MainWindow()
    : QMainWindow(nullptr),
      showWidget_(new QWidget(this)),
      scene_(new GraphicsScene(this)),
      view_(new GraphicsView(scene_, 6)),
      controller_(new Controller(6)),
      mode_(new QComboBox(this)),
      layout_(new QGridLayout()) {
    setUpStyle();
    setUpLayout();
    setUpBasePolygons();

    connect(view_, &GraphicsView::mousePressLeftPolygons, this, [&](const QPointF& point) {
        mode_->setEnabled(false);
        controller_->addVertexToLastPolygon(point);
    });
    connect(view_, &GraphicsView::mousePressRightPolygons, this, [&]() {
        if (controller_->getLastPolygon().isEmpty()) {
            return;
        }
        mode_->setEnabled(true);
        scene_->addPolygon(controller_->getLastPolygon(), basePolygonBrush, QPen(Qt::black));
        controller_->addEmptyPolygon();
    });
    connect(mode_, &QComboBox::currentTextChanged, this, [&]() {
        if (mode_->currentText() == "polygons") {
            view_->setMode(GraphicsView::Mode::polygons);
            return;
        }
        if (mode_->currentText() == "light") {
            view_->setMode(GraphicsView::Mode::light);
            updateStaticLight();
            return;
        }
        if (mode_->currentText() == "static-lights") {
            view_->setMode(GraphicsView::Mode::staticLight);
            return;
        }
    });

    connect(view_, &GraphicsView::mouseMoveLights, this, [&](const QPointF& light) {
        controller_->setLightSource(light);
        updateLightArea();
    });

    connect(view_, &GraphicsView::mousePressLeftStaticLights, this, [&](const QPointF& cursor) {
        controller_->addStaticLight(cursor);
        scene_->addLightArea(cursor);
    });


    qDebug() << "Main was build";
}

MainWindow::~MainWindow() {
    delete controller_;
    delete scene_;
    delete mode_;
    delete layout_;
}

void MainWindow::setUpStyle() {
    basePolygonBrush.setStyle(Qt::NoBrush);
    basePolygonPen.setColor(Qt::red);
}

void MainWindow::setUpLayout() {
    qDebug() << screen()->size();
    resize(screen()->size());
    setWindowTitle("Raytracing");
    mode_->addItem("light");
    mode_->addItem("polygons");
    mode_->addItem("static-lights");
    layout_->addWidget(mode_, 0, 0);
    layout_->addWidget(view_, 1, 0);
    showWidget_->setLayout(layout_);
    view_->setMouseTracking(true);
    setCentralWidget(showWidget_);
    showWidget_->setMouseTracking(true);
}

void MainWindow::setUpBasePolygons() {
    controller_->addPolygon(Polygon(std::vector<QPointF>(
        {QPointF(200, 200), QPointF(200, 400), QPointF(400, 400), QPointF(400, 200)}
    )));
    scene_->addPolygon(controller_->getLastPolygon(), basePolygonBrush, QPen(Qt::black));
    controller_->addPolygon(Polygon(std::vector<QPointF>(
        {QPointF(0, 0), QPointF(0, screen()->size().height() - 50),
         QPointF(screen()->size().width() - 20, screen()->size().height() - 50),
         QPointF(screen()->size().width() - 20, 0)}
    )));
    controller_->addEmptyPolygon();
}

void MainWindow::updateLightArea() {
    const auto& areas = controller_->createDynamicLightArea();
    const auto& lights = controller_->getDynamicLights();
    for (int i = 0; i < controller_->countDynamicLights(); ++i) {
        QRadialGradient gradient(lights[i], (width() + height()) / 4);
        gradient.setColorAt(0, Qt::white);
        gradient.setColorAt(1, QColor(0, 0, 0, 0));
        view_->updateLightArea(i, areas[i], lights[i], QBrush(gradient));
        //        qDebug() << lights[i] << " " << areas[i].getVertices();
    }
}

void MainWindow::updateStaticLight() {
    const auto& areas = controller_->createStaticLightArea();
    const auto& lights = controller_->getStaticLights();
    for (int i = 0; i < controller_->countStaticLights(); ++i) {
        QRadialGradient gradient(lights[i], (width() + height()) / 8);
        gradient.setColorAt(0, Qt::red);
        gradient.setColorAt(1, QColor(0, 0, 0, 0));
        view_->updateLightArea(
            i + controller_->countDynamicLights(), areas[i], lights[i], QBrush(gradient)
        );
        //        qDebug() << lights[i] << " " << areas[i].getVertices();
    }
}

