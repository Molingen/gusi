#include "Vector.h"

Vector::Vector(size_t n) : sz(n), data(new double[sz]()) {}

Vector::Vector(const Vector& other) : sz(other.sz), data(new double[sz]) {
    std::copy(other.data, other.data + sz, data);
}

Vector::Vector(Vector&& other) noexcept : sz(other.sz), data(other.data) {
    other.sz = 0;
    other.data = nullptr;
}

Vector& Vector::operator=(const Vector& other) {
    if (this != &other) {
        Vector temp(other);
        swap(temp);
    }
    return *this;
}

Vector& Vector::operator=(Vector&& other) noexcept {
    if (this != &other) {
        delete[] data;
        sz = other.sz;
        data = other.data;
        other.sz = 0;
        other.data = nullptr;
    }
    return *this;
}

void Vector::resize(size_t n) {
    if (n == sz) return;

    double* new_data = new double[n]();
    size_t copy_size = std::min(sz, n);
    std::copy(data, data + copy_size, new_data);

    delete[] data;
    data = new_data;
    sz = n;
}

void Vector::swap(Vector& other) noexcept {
    std::swap(sz, other.sz);
    std::swap(data, other.data);
}