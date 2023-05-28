#include "polygon.h"
#include <QLineF>
#include <iostream>

Polygon::Polygon(const std::vector<QPointF>& vertices) : vertices_(vertices) { }

void Polygon::addVertex(const QPointF& vertex) {
    vertices_.push_back(vertex);
}

void Polygon::updateLastVertex(const QPointF& newVertex) {
    if (vertices_.empty()) {
        throw std::out_of_range("Polygon is empty");
    }
    vertices_.back() = newVertex;
}

std::optional<QPointF> Polygon::intersectRay(const Ray& ray) const {
    double a1 = -sin(ray.getAngle());
    double b1 = cos(ray.getAngle());
    const double eps = 1e-8;
    auto isPointOnLine = [&](const QPointF& point, const QPointF& begin, const QPointF& end) {
        double distanceFromP1 = sqrt(Ray(begin, point).size());
        double distanceFromP2 = sqrt(Ray(end, point).size());
        double lineLength = sqrt(Ray(begin, end).size());

        return fabs(distanceFromP1 + distanceFromP2 - lineLength) <= eps;
    };
    auto intersectLine = [&](const QPointF& begin, const QPointF& end) {
        double a2 = -(end.y() - begin.y());
        double b2 = end.x() - begin.x();
        double c2 = (a2 * begin.x() + b2 * begin.y());
        double c1 = (a1 * ray.getBegin().x() + b1 * ray.getBegin().y());
        double det = (a1 * b2 - a2 * b1);
        if (fabs(det) <= eps) {
            return std::optional<QPointF>();
        }

        double x = (c1 * b2 - c2 * b1) / det;
        double y = (a1 * c2 - a2 * c1) / det;
        const QPointF point = QPointF(x, y);

        Q_ASSERT(fabs(a1 * x + b1 * y - c1) <= eps);
        Q_ASSERT(fabs(a2 * x + b2 * x - c2) <= eps);


        if (!isPointOnLine(QPointF(x, y), begin, end)
            || !(
                fabs(cos(ray.getAngle()) - cos(Ray(ray.getBegin(), point).getAngle())) <= eps
                && fabs(sin(ray.getAngle()) - sin(Ray(ray.getBegin(), point).getAngle())) <= eps
            )) {
            return std::optional<QPointF>();
        }
        return std::optional<QPointF>(QPointF(x, y));
    };

    std::optional<QPointF> ans = std::optional<QPointF>();
    for (int i = 0; i < vertices_.size(); ++i) {
        auto point = intersectLine(vertices_[i], vertices_[(i + 1) % vertices_.size()]);
        if (point == std::optional<QPointF>()) {
            continue;
        }
        if (ans == std::optional<QPointF>()) {
            ans = point;
            continue;
        }
        double rxNow = point->x() - ray.getBegin().x();
        double ryNow = point->y() - ray.getBegin().y();

        double rx = ans->x() - ray.getBegin().x();
        double ry = ans->y() - ray.getBegin().y();
        if (rxNow * rxNow + ryNow * ryNow - eps <= rx * rx + ry * ry) {
            ans = point;
        }
    }
    return ans;
}

const std::vector<QPointF>& Polygon::getVertices() const {
    return vertices_;
}

bool Polygon::isEmpty() const {
    return size() == 0;
}

int Polygon::size() const {
    return static_cast<int>(vertices_.size());
}
