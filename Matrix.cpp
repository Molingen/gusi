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