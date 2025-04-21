#pragma once
#include <vector>
#include "Vector.h"
#include "Matrix.h"

class GaussSolver {
public:
	GaussSolver() = default;
	std::vector<Vector> solve(const Matrix& A, const Vector& b);

private:
	std::vector<Vector> res;
};