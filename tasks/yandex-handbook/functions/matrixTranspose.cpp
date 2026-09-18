#include <vector>

std::vector<std::vector<int>> Transpose(const std::vector<std::vector<int>>& matrix) {
    size_t numberOfRows = matrix.size(), numberOfCols = matrix[0].size();
	std::vector<std::vector<int>> transposed(numberOfCols, std::vector<int>(numberOfRows));

    for (size_t row = 0; row < numberOfRows; ++row) {
        for (size_t col = 0; col < numberOfCols; ++col) {
			transposed[col][row] = matrix[row][col];
        }
    }

	return transposed;
}
