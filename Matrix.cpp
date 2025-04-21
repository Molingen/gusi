#include "Matrix.h"

Matrix::Matrix(const std::vector<std::vector<double>>& input) {
    if (input.empty()) {
        rows = 0;
        cols = 0;
        return;
    }

    rows = input.size();
    cols = input[0].size();

    for (const auto& row : input) {
        if (row.size() != cols) {
            throw std::invalid_argument("All rows must have the same length");
        }
    }

    vec = input;
}

Matrix::Matrix(size_t r, size_t c)
    : rows(r), cols(c), vec(r, std::vector<double>(c)) {
    if (r == 0 || c == 0) {
        throw std::invalid_argument("Matrix dimensions can`t be zero");
    }
    for (auto& row : vec) {
        std::fill(row.begin(), row.end(), 0.0);
    }
}

std::pair<size_t, std::vector<int>> Matrix::reduce() {
    size_t n = rows;
    size_t m = cols;
    std::vector pivot(m, -1);

    size_t rank = 0;
    for (size_t i = 0; i < std::min(n, m); ++i) {
        size_t maxRow = i;
        double maxVal = std::abs(vec[i][i]);

        for (size_t k = i + 1; k < n; ++k) {
            double currentVal = std::abs(vec[k][i]);
            if (currentVal > maxVal) {
                maxVal = currentVal;
                maxRow = k;
            }
        }

        if (maxVal < 1e-10) {
            continue;
        }

        if (maxRow != i) {
            std::swap(vec[i], vec[maxRow]);
        }

        pivot[i] = i;
        rank++;

        for (size_t k = i + 1; k < n; ++k) {
            const double scal = vec[k][i] / vec[i][i];
            for (size_t j = i; j < m; ++j) {
                vec[k][j] -= scal * vec[i][j];
            }
        }
    }
    return {rank, pivot};
}