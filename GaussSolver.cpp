#include "GaussSolver.h"

#include <algorithm>
#include <cmath>

std::vector<Vector> GaussSolver::solve(const Matrix& A, const Vector& b) {
    size_t n = A.getRows();
    size_t m = A.getCols();

    Matrix A_copy = A;
    Vector b_copy = b;

    std::vector<int> pivot(m, -1);
    std::vector<int> col_permutation(m);
    for (int i = 0; i < m; ++i) {
        col_permutation[i] = i;
    }

    int rank = 0;
    for (int i = 0; i < std::min(n, m); i++) {
        double maxEl = 0.0;
        int maxRow = i, maxCol = i;
        for (int k = i; k < n; k++) {
            for (int l = i; l < m; l++) {
                if (std::abs(A_copy(k, l)) > maxEl) {
                    maxEl = std::abs(A_copy(k, l));
                    maxRow = k;
                    maxCol = l;
                }
            }
        }

        if (maxEl == 0) {
            break;
        }

        if (maxRow != i) {
            for (int k = 0; k < m; k++) {
                std::swap(A_copy(i, k), A_copy(maxRow, k));
            }
            std::swap(b_copy[i], b_copy[maxRow]);
        }
        if (maxCol != i) {
            for (int k = 0; k < n; k++) {
                std::swap(A_copy(k, i), A_copy(k, maxCol));
            }
            std::swap(col_permutation[i], col_permutation[maxCol]);
            std::swap(pivot[i], pivot[maxCol]);
        }

        pivot[i] = i;
        rank++;

        for (int k = i + 1; k < n; k++) {
            double c = -A_copy(k, i) / A_copy(i, i);
            for (int j = i; j < m; j++) {
                A_copy(k, j) += c * A_copy(i, j);
            }
            b_copy[k] += c * b_copy[i];
        }
    }

    for (int i = rank; i < n; i++) {
        if (fabs(b_copy[i]) > 1e-10) {
            return {};
        }
    }

    if (rank < m) {
        std::vector<Vector> solutions;
        Vector particular_solution(m);
        for (int i = rank - 1; i >= 0; i--) {
            double sum = 0.0;
            for (int j = i + 1; j < m; j++) {
                sum += A_copy(i, j) * particular_solution[j];
            }
            particular_solution[pivot[i]] = (b_copy[i] - sum) / A_copy(i, i);
        }

        Vector permuted_particular_solution(m);
        for (int i = 0; i < m; ++i) {
            permuted_particular_solution[col_permutation[i]] =
                particular_solution[i];
        }
        solutions.push_back(permuted_particular_solution);

        for (int free_var = 0; free_var < m; free_var++) {
            if (std::find(pivot.begin(), pivot.end(), free_var) ==
                pivot.end()) {
                Vector basis(m);
                basis[free_var] = 1;
                for (int i = rank - 1; i >= 0; i--) {
                    double sum = 0.0;
                    for (int j = i + 1; j < m; j++) {
                        sum += A_copy(i, j) * basis[j];
                    }
                    basis[pivot[i]] = (0 - sum) / A_copy(i, i);
                }

                Vector permuted_basis(m);
                for (int i = 0; i < m; ++i) {
                    permuted_basis[col_permutation[i]] = basis[i];
                }
                solutions.push_back(permuted_basis);
            }
        }

        return solutions;
    } else {
        Vector x(m);
        for (int i = m - 1; i >= 0; i--) {
            double sum = 0.0;
            for (int j = i + 1; j < m; j++) {
                sum += A_copy(i, j) * x[j];
            }
            x[pivot[i]] = (b_copy[i] - sum) / A_copy(i, i);
        }

        Vector result(m);
        for (int i = 0; i < m; ++i) {
            result[col_permutation[i]] = x[i];
        }

        return {result};
    }
}

