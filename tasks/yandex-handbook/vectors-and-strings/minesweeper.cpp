#include <iostream>
#include <vector>

int main() {
    int numberOfRows, numberOfCols, mineAmount;
    std::cin >> numberOfRows >> numberOfCols >> mineAmount;

    std::vector<std::vector<char>> field(numberOfRows, std::vector<char>(numberOfCols, '0'));

    for (int i = 0; i < mineAmount; ++i) {
        int row, col;
        std::cin >> row >> col;
        field[row - 1][col - 1] = '*';
    }

    for (int i = 0; i < numberOfRows; ++i) {
        for (int j = 0; j < numberOfCols; ++j) {
            if (field[i][j] == '*') {
                std::cout << "* ";
            } else {
                int count = 0;
                for (int di = -1; di <= 1; ++di) {
                    for (int dj = -1; dj <= 1; ++dj) {
                        if (di == 0 && dj == 0) {
                            continue;
                        }
                        int ni = i + di;
                        int nj = j + dj;
                        if (ni >= 0 && ni < numberOfRows && nj >= 0 && nj < numberOfCols &&
                            field[ni][nj] == '*') {
                            ++count;
                        }
                    }
                }
                std::cout << count << " ";
            }
        }
        std::cout << '\n';
    }

    return 0;
}