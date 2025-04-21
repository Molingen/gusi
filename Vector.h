#pragma once
#include <iostream>

class Vector {
public:
    Vector(size_t n);
    Vector(const Vector& other);
    Vector(Vector&& other) noexcept;
    ~Vector() { delete[] data; }

    Vector& operator=(const Vector& other);
    Vector& operator=(Vector&& other) noexcept;

    double& operator [](size_t index) { return data[index]; }
    const double& operator[](size_t index) const { return data[index]; }

    void print() const {
        for (size_t i = 0; i < sz; ++i) {
            std::cout << data[i] << " ";
        }
        std::cout << std::endl;
    }

    size_t size() const { return sz; }
    void resize(size_t n);
    void swap(Vector& other) noexcept;

private:
    size_t sz = 0;
    double* data = nullptr;
};