#include "controllerRays.h"

ControllerRays::ControllerRays(const std::vector<Polygon> &polygons, int count)
        : polygons_(polygons), lightSource_(), dynamicLights_(std::vector<QPointF>(count)) {
    setLightSource(QPointF(50, 50));
}

const std::vector<Polygon> &ControllerRays::getPolygons() const {
    return polygons_;
}

void ControllerRays::addVertexToLastPolygon(const QPointF &newVertex) {
    polygons_.back().addVertex(newVertex);
}

void ControllerRays::updateLastPolygon(const QPointF &newVertex) {
    polygons_.back().updateLastVertex(newVertex);
}

void ControllerRays::setLightSource(const QPointF &light) {
    lightSource_ = light;
    dynamicLights_[countDynamicLights() - 1] = lightSource_;
    if (countDynamicLights() == 1) {
        return;
    }
    const double radLights = 2;
    double ang = 2 * M_PI / (countDynamicLights() - 1);
    double angNow = 0;
    for (int i = 0; i < countDynamicLights() - 1; ++i) {
        dynamicLights_[i] =
                QPointF(light.x() + radLights * cos(angNow), light.y() + radLights * sin(angNow));
        angNow += ang;
    }
}

const QPointF &ControllerRays::getLightSource() const {
    return lightSource_;
}

void ControllerRays::addPolygon(const Polygon &polygon) {
    polygons_.push_back(polygon);
}

const Polygon &ControllerRays::getLastPolygon() {
    return polygons_.back();
}

void ControllerRays::addEmptyPolygon() {
    polygons_.push_back(Polygon());
}

std::vector<std::optional<Ray>> ControllerRays::castRays(const QPointF &lightSource) const {
    const double angle = 0.0001;
    std::vector<std::optional<Ray>> result;
    for (const auto &polygon: polygons_) {
        for (const auto &vertex: polygon.getVertices()) {
            Ray baseRay = Ray(lightSource, vertex);
            result.push_back(baseRay);
            result.push_back(baseRay.rotate(angle));
            result.push_back(baseRay.rotate(-angle));
        }
    }
    return result;
}

void ControllerRays::intersectRays(std::vector<std::optional<Ray>> &rays) const {
    for (auto &ray: rays) {
        for (const auto &polygon: polygons_) {
            auto point = polygon.intersectRay(ray.value());
            if (point == std::nullopt) {
                continue;
            }
            const double eps = 1e-8;
            double dx = point->x() - ray->getBegin().x();
            double dy = point->y() - ray->getBegin().y();
            if (dx * dx + dy * dy - eps <= ray->size()) {
                ray->setEnd(point.value());
            }
        }
    }
}

void ControllerRays::removeAdjacentRays(std::vector<std::optional<Ray>> &rays, double dist) const {
    const double eps = 1e-8;
    for (int i = 0; i < rays.size(); ++i) {
        for (int j = i + 1; j < rays.size(); ++j) {
            if (rays[i] == std::nullopt || rays[j] == std::nullopt) {
                continue;
            }
            double dx = rays[i]->getEnd().x() - rays[j]->getEnd().x();
            double dy = rays[i]->getEnd().y() - rays[j]->getEnd().y();
            if (dx * dx + dy * dy - eps <= dist * dist) {
                rays[j] = std::nullopt;
            }
        }
    }
}

std::vector<Polygon> ControllerRays::createDynamicLightArea() const {
    return createAreas(dynamicLights_);
}

const std::vector<QPointF> &ControllerRays::getDynamicLights() const {
    return dynamicLights_;
}

void ControllerRays::addStaticLight(const QPointF &center) {
    staticLights_.push_back(center);
}

int ControllerRays::countStaticLights() const {
    return static_cast<int>(staticLights_.size());
}

int ControllerRays::countDynamicLights() const {
    return static_cast<int>(dynamicLights_.size());
}

std::vector<Polygon> ControllerRays::createAreas(const std::vector<QPointF> &sources) const {
    std::vector<Polygon> polygons;
    for (const QPointF &lightSource: sources) {
        const double eps = 1e-8;
        std::vector<std::optional<Ray>> vec = castRays(lightSource);
        intersectRays(vec);
        removeAdjacentRays(vec, 1);
        std::sort(
                vec.begin(), vec.end(),
                [&](const std::optional<Ray> &lhs, const std::optional<Ray> &rhs) {
                    if (lhs == std::nullopt) {
                        return false;
                    }
                    if (rhs == std::nullopt) {
                        return true;
                    }
                    return lhs->getAngle() - eps <= rhs->getAngle();
                }
        );
        Polygon result;
        for (const auto &ray: vec) {
            if (ray == std::nullopt) {
                break;
            }
            result.addVertex(ray->getEnd());
        }
        polygons.push_back(result);
    }
    return polygons;
}

std::vector<Polygon> ControllerRays::createStaticLightArea() const {
    return createAreas(staticLights_);
}

const std::vector<QPointF> &ControllerRays::getStaticLights() const {
    return staticLights_;
}

void ControllerRays::prec(const LevelField &field, int dis, double cellSize) {
    const auto &matrix = field.getMatrix();
    for (int i = 0; i < matrix.size(); ++i) {
        for (int j = 0; j < matrix[i].size(); ++j) {
            if (matrix[i][j]) {
                continue;
            }
            setPolygons(field.nearPolygons(cellSize, i, j));
            addPolygon(Polygon({QPointF(std::max(0.0, cellSize * j - cellSize), std::max(0.0, cellSize * i - cellSize)),
                                QPointF(std::max(0.0, cellSize * j - cellSize), std::min(matrix.size() * cellSize * 1.0,
                                                                                         cellSize * i +
                                                                                         cellSize)),
                                QPointF(std::min(matrix[0].size() * cellSize * 1.0, cellSize * j + cellSize),
                                        std::min(matrix.size() * cellSize * 1.0,
                                                 cellSize * i +
                                                 cellSize)),
                                QPointF(std::min(matrix[0].size() * cellSize * 1.0, cellSize * j + cellSize),
                                        std::max(0.0,
                                                 cellSize * i -
                                                 cellSize))}));

            QPoint off = QPoint(5, 5);
            qDebug() << polygons_.size();
            for (int p = 0; p <= 100; p += dis) {
                QPoint point = QPoint(cellSize * j + (p * cellSize) / 100, cellSize * i) + off;
                setLightSource(point);
                hashAreas_[point] = createDynamicLightArea();
            }

            for (int p = 0; p <= 100; p += dis) {
                QPoint point = QPoint(cellSize * j, cellSize * i + (p * cellSize) / 100) + off;
                setLightSource(point);
                hashAreas_[point] = createDynamicLightArea();
            }

            for (int p = 0; p <= 100; p += dis) {
                QPoint point = QPoint(cellSize * j, cellSize * i - (p * cellSize) / 100) + off;
                setLightSource(point);
                hashAreas_[point] = createDynamicLightArea();
            }

            for (int p = 0; p <= 100; p += dis) {
                QPoint point = QPoint(cellSize * j - (p * cellSize) / 100, cellSize * i) + off;
                setLightSource(point);
                hashAreas_[point] = createDynamicLightArea();
            }
        }
    }
}

void ControllerRays::setPolygons(const std::vector<Polygon> &polygons) {
    polygons_ = polygons;
}

const std::vector<Polygon> ControllerRays::getPrecPolygons(const QPoint &point) const {
    return hashAreas_[point];
}
