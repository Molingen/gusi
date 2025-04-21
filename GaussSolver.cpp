#include "GaussSolver.h"
#include <algorithm>
#include <cmath>

std::vector<Vector> GaussSolver::solve(const Matrix& A, const Vector& b) {
    size_t n = A.getRows();
    size_t m = A.getCols();

    Matrix Ab(n, m + 1);
    for (size_t i = 0; i < n; ++i) {
        for (size_t j = 0; j < m; ++j) {
            Ab(i, j) = A(i, j);
        }
        Ab(i, m) = b[i];
    }

    auto [rank, pivot] = Ab.reduce();

    for (size_t i = rank; i < n; ++i) {
        if (std::abs(Ab(i, m)) > 1e-10) {
            return {};
        }
    }

    Matrix A_reduced(n, m);
    for (size_t i = 0; i < n; ++i) {
        for (size_t j = 0; j < m; ++j) {
            A_reduced(i, j) = Ab(i, j);
        }
    }

    if (rank < m) {
        std::vector<Vector> solutions;

        Vector p_solution(m);
        for (int i = rank - 1; i >= 0; --i) {
            double sum = 0.0;
            for (size_t j = i + 1; j < m; ++j) {
                sum += A_reduced(i, j) * p_solution[j];
            }
            p_solution[pivot[i]] = (Ab(i, m) - sum) / A_reduced(i, i);
        }
        solutions.push_back(p_solution);

        for (size_t free_var = 0; free_var < m; ++free_var) {
            if (std::find(pivot.begin(), pivot.end(), free_var) == pivot.end()) {
                Vector basis(m);
                basis[free_var] = 1;
                for (int i = rank - 1; i >= 0; --i) {
                    double sum = 0.0;
                    for (size_t j = i + 1; j < m; ++j) {
                        sum += A_reduced(i, j) * basis[j];
                    }
                    basis[pivot[i]] = -sum / A_reduced(i, i);
                }
                solutions.push_back(basis);
            }
        }
        return solutions;
    }
    Vector x(m);
    for (int i = rank - 1; i >= 0; --i) {
        double sum = 0.0;
        for (size_t j = i + 1; j < m; ++j) {
            sum += A_reduced(i, j) * x[j];
        }
        x[pivot[i]] = (Ab(i, m) - sum) / A_reduced(i, i);
    }
    return {x};
}