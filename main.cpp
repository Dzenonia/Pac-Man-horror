#include "main_window.h"
//#include "gtest/gtest.h"
#include <QApplication>
#include <QPoint>

int main(int argc, char* argv[]) {
    //    ::testing::InitGoogleTest(&argc, argv);
    //    return RUN_ALL_TESTS();
    QApplication app(argc, argv);
    MainWindow window;
    window.show();

    QPoint point;
    return QApplication::exec();
}
