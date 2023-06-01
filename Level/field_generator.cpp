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
    std::vector<bool> useDx(height, false);
    std::vector<bool> useDy(width, false);
    const int CNT_SQARE = 5;

    const int MIN_LENGTH = 7;
    const int MIN_HEIGHT = 7;
    for (int cnt = 0; cnt < CNT_SQARE;) {

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
        if (abs(x1 - x2) < MIN_HEIGHT || abs(y1 - y2) < MIN_LENGTH) {
            continue;
        }

        bool ok = true;
        for (int i = 0; i < 2; i++) {
            if (useDx[x1 + i] || useDx[x2 + i] || useDy[y1 + i] || useDy[y2 + i]) {
                ok = false;
            }
        }
        if (!ok) { continue; }
        for (int i = 0; i < 2; i++) {
            useDx[x1 + i] = true;
            useDx[x2 + i] = true;
            useDy[y1 + i] = true;
            useDy[y2 + i] = true;
        }

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
    if (cnt > 1) {
        return generateField(height, width);
    }
    return field;
}