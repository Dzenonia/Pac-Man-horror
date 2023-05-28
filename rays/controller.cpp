#include "controller.h"

Controller::Controller(int count)
    : polygons_(), lightSource_(), dynamicLights_(std::vector<QPointF>(count)) {
    setLightSource(QPointF(50, 50));
}

const std::vector<Polygon>& Controller::getPolygons() const {
    return polygons_;
}

void Controller::addVertexToLastPolygon(const QPointF& newVertex) {
    polygons_.back().addVertex(newVertex);
}

void Controller::updateLastPolygon(const QPointF& newVertex) {
    polygons_.back().updateLastVertex(newVertex);
}

void Controller::setLightSource(const QPointF& light) {
    lightSource_ = light;
    dynamicLights_[countDynamicLights() - 1] = lightSource_;
    if (countDynamicLights() == 1) {
        return;
    }
    const double radLights = 10;
    double ang = 2 * M_PI / (countDynamicLights() - 1);
    double angNow = 0;
    for (int i = 0; i < countDynamicLights() - 1; ++i) {
        dynamicLights_[i] =
            QPointF(light.x() + radLights * cos(angNow), light.y() + radLights * sin(angNow));
        angNow += ang;
    }
}

const QPointF& Controller::getLightSource() const {
    return lightSource_;
}

void Controller::addPolygon(const Polygon& polygon) {
    polygons_.push_back(polygon);
}

const Polygon& Controller::getLastPolygon() {
    return polygons_.back();
}

void Controller::addEmptyPolygon() {
    polygons_.push_back(Polygon());
}

std::vector<std::optional<Ray>> Controller::castRays(const QPointF& lightSource) const {
    const double angle = 0.0001;
    std::vector<std::optional<Ray>> result;
    for (const auto& polygon : polygons_) {
        for (const auto& vertex : polygon.getVertices()) {
            Ray baseRay = Ray(lightSource, vertex);
            result.push_back(baseRay);
            result.push_back(baseRay.rotate(angle));
            result.push_back(baseRay.rotate(-angle));
        }
    }
    return result;
}

void Controller::intersectRays(std::vector<std::optional<Ray>>& rays) const {
    for (auto& ray : rays) {
        for (const auto& polygon : polygons_) {
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

void Controller::removeAdjacentRays(std::vector<std::optional<Ray>>& rays, double dist) const {
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

std::vector<Polygon> Controller::createDynamicLightArea() const {
    return createAreas(dynamicLights_);
}

const std::vector<QPointF>& Controller::getDynamicLights() const {
    return dynamicLights_;
}

void Controller::addStaticLight(const QPointF& center) {
    staticLights_.push_back(center);
}

int Controller::countStaticLights() const {
    return static_cast<int>(staticLights_.size());
}

int Controller::countDynamicLights() const {
    return static_cast<int>(dynamicLights_.size());
}

std::vector<Polygon> Controller::createAreas(const std::vector<QPointF>& sources) const {
    std::vector<Polygon> polygons;
    for (const QPointF& lightSource : sources) {
        const double eps = 1e-8;
        std::vector<std::optional<Ray>> vec = castRays(lightSource);
        intersectRays(vec);
        removeAdjacentRays(vec, 1);
        std::sort(
            vec.begin(), vec.end(),
            [&](const std::optional<Ray>& lhs, const std::optional<Ray>& rhs) {
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
        for (const auto& ray : vec) {
            if (ray == std::nullopt) {
                break;
            }
            result.addVertex(ray->getEnd());
        }
        polygons.push_back(result);
    }
    return polygons;
}

std::vector<Polygon> Controller::createStaticLightArea() const {
    return createAreas(staticLights_);
}

const std::vector<QPointF>& Controller::getStaticLights() const {
    return staticLights_;
}
