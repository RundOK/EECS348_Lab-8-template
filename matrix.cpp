#include "matrix.hpp"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <stdexcept>
#include <string>
#include <vector>

// implementation of functions declared in matrix.hpp goes here
// function definitions for a class have their names prefixed with
// the class name and "::"

Matrix::Matrix(std::size_t N) : _N(N), nums(N, std::vector<int>(N, 0)) {}

Matrix::Matrix(std::vector<std::vector<int>> nums) : _N(nums.size()), nums(std::move(nums)) {}

std::vector<Matrix> Matrix::read_from_file(const std::string &filename) {
    std::ifstream file(filename);
    if (!file) {
        throw std::runtime_error("Unable to open file");
    }
    
    std::size_t N;
    file >> N;
    
    std::vector<std::vector<int>> matrix1(N, std::vector<int>(N));
    std::vector<std::vector<int>> matrix2(N, std::vector<int>(N));
    
    for (std::size_t i = 0; i < N; ++i) {
        for (std::size_t j = 0; j < N; ++j) {
            file >> matrix1[i][j];
        }
    }
    
    for (std::size_t i = 0; i < N; ++i) {
        for (std::size_t j = 0; j < N; ++j) {
            file >> matrix2[i][j];
        }
    }
    
    return {Matrix(matrix1), Matrix(matrix2)};
}

Matrix Matrix::operator+(const Matrix &rhs) const {
    if (_N != rhs._N) {
        throw std::invalid_argument("Matrix dimensions must match for addition");
    }
    Matrix result(_N);
    for (std::size_t i = 0; i < _N; ++i) {
        for (std::size_t j = 0; j < _N; ++j) {
            result.nums[i][j] = nums[i][j] + rhs.nums[i][j];
        }
    }
    return result;
}

Matrix Matrix::operator*(const Matrix &rhs) const {
    if (_N != rhs._N) {
        throw std::invalid_argument("Matrix dimensions must match for multiplication");
    }
    Matrix result(_N);
    for (std::size_t i = 0; i < _N; ++i) {
        for (std::size_t j = 0; j < _N; ++j) {
            for (std::size_t k = 0; k < _N; ++k) {
                result.nums[i][j] += nums[i][k] * rhs.nums[k][j];
            }
        }
    }
    return result;
}

void Matrix::set_value(std::size_t i, std::size_t j, int n) {
    if (i >= _N || j >= _N) {
        throw std::out_of_range("Index out of range");
    }
    nums[i][j] = n;
}


int Matrix::get_value(std::size_t i, std::size_t j) const {
    if (i >= _N || j >= _N) {
        throw std::out_of_range("Index out of range");
    }
    return nums[i][j];
}

int Matrix::get_size() const{
    return _N;
}

int Matrix::sum_diagonal_major() const{
    int sum = 0;
    for (std::size_t i = 0; i < _N; ++i) {
        sum += nums[i][i];
    }
    return sum;
}

int Matrix::sum_diagonal_minor() const{
    int sum = 0;
    for (std::size_t i = 0; i < _N; ++i) {
        sum += nums[i][_N - i - 1];
    }
    return sum;
}

void Matrix::swap_rows(std::size_t r1, std::size_t r2){
    if (r1 >= _N || r2 >= _N) {
        throw std::out_of_range("Row index out of range");
    }
    std::swap(nums[r1], nums[r2]);
}

void Matrix::swap_cols(std::size_t c1, std::size_t c2){
    if (c1 >= _N || c2 >= _N) {
        throw std::out_of_range("Column index out of range");
    }
    for (std::size_t i = 0; i < _N; ++i) {
        std::swap(nums[i][c1], nums[i][c2]);
    }
}

void Matrix::print_matrix() const{
    for (const auto &row : nums) {
        for (const auto &elem : row) {
            std::cout << std::setw(5) << elem << " ";
        }
        std::cout << '\n';
    }
    
}
