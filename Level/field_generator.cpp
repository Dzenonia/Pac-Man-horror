#include "field_generator.h"

#include <iostream>
#include <vector>

void dfs(int x, int y, std::vector<std::vector<bool>> &field) {
    field[x][y] = true;
    if (!field[x - 1][y]) { dfs(x - 1, y, field); }
    if (!field[x + 1][y]) { dfs(x + 1, y, field); }
    if (!field[x][y - 1]) { dfs(x, y - 1, field); }
    if (!field[x][y + 1]) { dfs(x, y + 1, field); }
}

std::vector<std::vector<bool>> generate::generateField(int height, int width) {
    std::vector<std::vector<bool>> field(height, std::vector<bool>(width, true));
    srand(time(NULL));
    std::vector<bool> usedx(height, false);
    std::vector<bool> usedy(width, false);
    const int CNT_SQARE = 5; //количество прямоугольников, больше 5 не особо работает, лучше оставить на 5
    // с размерами можно поиграться для красоты карты
    const int MIN_LENGTH = 7; //Минимальная ширина прямоугольника
    const int MIN_HEIGHT = 7; //Минимальная высотка прямоуг
    for (int cnt = 0; cnt < CNT_SQARE;) {
        //генерация координат прямоугольника между границами всего поля
        int x1 = rand();
        int x2 = rand();
        int y1 = rand();
        int y2 = rand();

        x1 %= height - 2;
        x2 %= height - 2;
        y1 %= width - 2;
        y2 %= width - 2;

        x1++;
        x2++;
        y1++;
        y2++;
        // Проверка на минимальные растояния прямоугольника
        if (abs(x1 - x2) < MIN_HEIGHT || abs(y1 - y2) < MIN_LENGTH) {
            continue;
        }

        //Чтобы не генерировались друг на друге прямоугольники usedx и usedy заполняем и проверяем на совпадение
        bool ok = true;
        for (int i = 0; i < 2; i++) {
            if (usedx[x1 + i] || usedx[x2 + i] || usedy[y1 + i] || usedy[y2 + i]) {
                ok = false;
            }
        }
        if (!ok) { continue; }
        for (int i = 0; i < 2; i++) {
            usedx[x1 + i] = true;
            usedx[x2 + i] = true;
            usedy[y1 + i] = true;
            usedy[y2 + i] = true;
        }
        //заполнение поля
        for (auto x: {x1, x2}) {
            for (int y = std::min(y1, y2); y <= std::max(y1, y2); y++) {
                field[x][y] = false;
            }
        }
        for (auto y: {y1, y2}) {
            for (int x = std::min(x1, x2); x <= std::max(x1, x2); x++) {
                field[x][y] = false;
            }
        }
        cnt++;

    }
    //проверка на связность
    auto temp = field;
    int cnt = 0;
    for (int i = 1; i < height - 1; i++) {
        for (int j = 1; j < width - 1; j++) {
            if (!temp[i][j]) {
                dfs(i, j, temp);
                cnt++;
            }
        }
    }
    //если не связный переделать
    if (cnt > 1) {
        return generateField(height, width);
    }
    return field;
}