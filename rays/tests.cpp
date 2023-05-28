#include "polygon.h"
#include "gtest/gtest.h"

TEST(polygon, intersect_test1) {
    Polygon polygon(std::vector<QPointF>({QPointF(0, 0), QPointF(10, 0)}));

    Ray ray(QPointF(5, 5), QPointF(5, -5));
    EXPECT_EQ(polygon.intersectRay(ray), QPointF(5, 0));
}

TEST(polygon, intersect_test2) {
    Polygon polygon(std::vector<QPointF>({QPointF(0, 1), QPointF(1, 0)}));

    Ray ray(QPointF(0, 0), QPointF(2, 2));
    EXPECT_EQ(polygon.intersectRay(ray), QPointF(0.5, 0.5));
}

TEST(polygon, intersect_test3) {
    Polygon polygon(std::vector<QPointF>({QPointF(0, 1), QPointF(1, 0)}));

    Ray ray(QPointF(0.5, -1), QPointF(0.5, 0));
    EXPECT_EQ(polygon.intersectRay(ray), QPointF(0.5, 0.5));
}

TEST(polygon, intersect_test4) {
    Polygon polygon(std::vector<QPointF>({QPointF(0, 1), QPointF(1, 0)}));

    Ray ray(QPointF(0.5, 10), QPointF(0.5, 20));
    EXPECT_EQ(polygon.intersectRay(ray), std::optional<QPointF>());
}

TEST(polygon, intersect_test5) {
    Polygon polygon(std::vector<QPointF>({QPointF(0, 1), QPointF(1, 0)}));

    Ray ray(QPointF(0, 0), QPointF(-0.2, 1));
    EXPECT_EQ(polygon.intersectRay(ray), std::optional<QPointF>());
}

TEST(polygon, intersect_test6) {
    Polygon polygon(std::vector<QPointF>({QPointF(0, 1), QPointF(1, 0)}));

    Ray ray(QPointF(368, 367), QPointF(0, 650));
    EXPECT_EQ(polygon.intersectRay(ray), std::optional<QPointF>());
}