#pragma once
#include <iostream>
#include <vector>

class Matrix {
public:
    Matrix() : rows(0), cols(0) {}
    explicit Matrix(const std::vector<std::vector<double>> &input);
    Matrix(size_t r, size_t c);

    void print() const {
        for (const auto& row : vec) {
            for (const double val : row) {
                std::cout << val << ' ';
            }
            std::cout << std::endl;
        }
    }

    double& operator()(size_t r, size_t c) { return vec[r][c]; }
    const double& operator()(size_t r, size_t c) const { return vec[r][c]; }
    size_t getRows() const { return rows; }
    size_t getCols() const { return cols; }
    const std::vector<std::vector<double>> &getVec() const { return vec; }

private:
    size_t rows;
    size_t cols;
    std::vector<std::vector<double>> vec;
};