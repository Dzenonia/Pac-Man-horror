//#include "main_window.h"
////#include "gtest/gtest.h"
//#include <QApplication>
//#include <QPoint>
//#include <iostream>
//
//int main(int argc, char *argv[]) {
//
//
//    std::vector<std::vector<int>> matrix;
//
//    for (const std::string &row: map) {
//        std::vector<int> matrixRow;
//        for (char ch: row) {
//            if (ch == '#')
//                matrixRow.push_back(1);
//            else
//                matrixRow.push_back(0);
//        }
//        matrix.push_back(matrixRow);
//    }
//
//    // Вывод матрицы
//    for (const std::vector<int> &row: matrix) {
//        int first = 0;
//        for (int cell: row) {
//            if (first) {
//                std::cout << ", ";
//            } else {
//                std::cout << "{";
//                first = 1;
//            }
//            std::cout << cell;
//        }
//        std::cout << "},";
//        std::cout << std::endl;
//    }
//    //    ::testing::InitGoogleTest(&argc, argv);
//    //    return RUN_ALL_TESTS();
//    QApplication app(argc, argv);
//    MainWindow window;
//    window.show();
//    return QApplication::exec();
//}
//
//
//

#include <QApplication>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsTextItem>
#include <QMessageBox>
#include <QFont>
#include <QPushButton>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    // Создаем сцену
    QGraphicsScene scene;
    scene.setSceneRect(0, 0, 300, 200);

    // Создаем вид
    QGraphicsView view(&scene);
    view.setWindowTitle("Меню");
    view.setFixedSize(320, 240);

    // Создаем стиль для кнопок без заднего фона
    QString buttonStyle = "QPushButton {"
                          "    background-color: transparent;"
                          "    border: none;"
                          "}";

    // Создаем кнопки
    QPushButton startButton("Начать игру");
    QPushButton settingsButton("Настройки");
    QPushButton exitButton("Выход");

    // Применяем стиль к кнопкам
    startButton.setStyleSheet(buttonStyle);
    settingsButton.setStyleSheet(buttonStyle);
    exitButton.setStyleSheet(buttonStyle);

    // Изменяем шрифт текста на кнопках
    QFont buttonFont("Arial", 12, QFont::Bold);
    startButton.setFont(buttonFont);
    settingsButton.setFont(buttonFont);
    exitButton.setFont(buttonFont);

    // Размещаем кнопки на сцене
    QGraphicsProxyWidget *startButtonProxy = scene.addWidget(&startButton);
    QGraphicsProxyWidget *settingsButtonProxy = scene.addWidget(&settingsButton);
    QGraphicsProxyWidget *exitButtonProxy = scene.addWidget(&exitButton);

    // Устанавливаем позиции кнопок
    startButtonProxy->setPos(50, 50);
    settingsButtonProxy->setPos(50, 90);
    exitButtonProxy->setPos(50, 130);

    // Подключаем сигналы и слоты для кнопок
    QObject::connect(&startButton, &QPushButton::clicked, [&]() {
        QMessageBox::information(nullptr, "Информация", "Игра началась!");
    });

    QObject::connect(&settingsButton, &QPushButton::clicked, [&]() {
        QMessageBox::information(nullptr, "Настройки", "Настройки открыты!");
    });

    QObject::connect(&exitButton, &QPushButton::clicked, [&]() {
        QApplication::quit();
    });

    // Отображаем вид
    view.show();

    // Запускаем главный цикл приложения
    return app.exec();
}




