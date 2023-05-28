#pragma once
#include <QDebug>
#include <QPointF>

class Ray {
public:
    Ray(const QPointF& begin, const QPointF& end);
    Ray(const QPointF& begin, double angle);

    void setBegin(const QPointF& newBegin);
    void setEnd(const QPointF& end);
    const QPointF& getBegin() const;
    const QPointF& getEnd() const;
    double getAngle() const;
    QPointF getVector() const;
    double size() const;

    Ray rotate(double angle) const;

private:
    static const int MAX_RAY_SIZE;

private:
    QPointF begin_;
    QPointF end_;
    double angle_;
};