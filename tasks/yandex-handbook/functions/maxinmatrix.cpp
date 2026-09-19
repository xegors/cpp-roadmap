#include <iostream>
#include <vector>

std::pair<size_t, size_t> MatrixArgMax(const std::vector<std::vector<int>>& matrix) {
    int numberOfRows, numberOfCols;
    numberOfRows = matrix.size();
    numberOfCols = matrix[0].size();

    std::pair<int, int> res = {0, 0};

    for (int row = 0; row < numberOfRows; ++row) {
        for (int col = 0; col < numberOfCols; ++col) {
            if (matrix[row][col] > matrix[res.first][res.second])
                res = {row, col};
        }
    }

    return res;
}