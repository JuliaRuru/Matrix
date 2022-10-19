#include "matrix_oop.h"

MyMatrix::MyMatrix() noexcept : MyMatrix(3, 3) {}

MyMatrix::MyMatrix(int rows, int cols) : rows_{ rows }, cols_{ cols } {
    if (rows_ < 1 || cols_ < 1) {
        throw std::invalid_argument("In constructor with parameters: rows or cols < 0\n");
    }
    createMatrix(rows_, cols_);
}

MyMatrix::MyMatrix(const MyMatrix& other) : MyMatrix() {
    if (this == &other) throw std::out_of_range("In copy constructor: error. Incorrect data");
    *this = other;
}

MyMatrix::MyMatrix(MyMatrix&& other) : rows_{ 0 }, cols_{ 0 }, matrix_{ nullptr } {
    std::swap(matrix_, other.matrix_);
    std::swap(rows_, other.rows_);
    std::swap(cols_, other.cols_);
}

MyMatrix::~MyMatrix() {
    deleteMatrix();
}

int MyMatrix::getRows() const {
    return rows_;
}

int MyMatrix::getCols() const {
    return cols_;
}

void MyMatrix::setRows(int rows) {
    if (rows < 1) {
        throw std::invalid_argument("In mutator setRows: rows must be > 0\n");
    }
    MyMatrix temp_matrix(rows, cols_);
    int min_rows = rows_;
    if (rows < rows_) {
        min_rows = rows;
    }
    for (int i = 0; i < min_rows; i++) {
        for (int j = 0; j < cols_; j++) {
            temp_matrix.matrix_[i][j] = matrix_[i][j];
        }
    }
    *this = temp_matrix;
}

void MyMatrix::setCols(int cols) {
    if (cols < 1) {
        throw std::invalid_argument("In mutator setCols: cols must be > 0\n");
    }
    MyMatrix temp_matrix(rows_, cols);
    int min_cols = cols_;
    if (cols < cols_) {
        min_cols = cols;
    }
    for (int i = 0; i < rows_; i++) {
        for (int j = 0; j < min_cols; j++) {
            temp_matrix.matrix_[i][j] = matrix_[i][j];
        }
    }
    *this = temp_matrix;
}

bool MyMatrix::eq_matrix(const MyMatrix& other) const {
    if (rows_ != other.rows_ || cols_ != other.cols_) {
        return false;
    } else {
        for (int i = 0; i < rows_; i++) {
            for (int j = 0; j < cols_; j++) {
                if (fabs(matrix_[i][j] - other.matrix_[i][j]) > EPS) {
                    return false;
                }
            }
        }
    }
    return true;
}

void MyMatrix::sum_matrix(const MyMatrix& other) {
    if (rows_ != other.rows_ || cols_ != other.cols_) {
        throw std::invalid_argument("In method sum_matrix: matrices have a different size\n");
    }
    for (int i = 0; i < rows_; i++) {
        for (int j = 0; j < cols_; j++) {
            matrix_[i][j] += other.matrix_[i][j];
        }
    }
}

void MyMatrix::sub_matrix(const MyMatrix& other) {
    if (rows_ != other.rows_ || cols_ != other.cols_) {
        throw std::invalid_argument("In method sub_matrix: matrices have a different size\n");
    }
    for (int i = 0; i < rows_; i++) {
        for (int j = 0; j < cols_; j++) {
            matrix_[i][j] -= other.matrix_[i][j];
        }
    }
}

void MyMatrix::mul_number(const double num) {
    if (std::isnan(num) || std::isinf(num)) {
        throw std::out_of_range("In method mul_number: incorrect value of number\n");
    }
    for (int i = 0; i < rows_; i++) {
        for (int j = 0; j < cols_; j++) {
            matrix_[i][j] *= num;
        }
    }
}

void MyMatrix::mul_matrix(const MyMatrix& other) {
    if (cols_ != other.rows_) {
        throw std::domain_error("In method mul_matrix: rows of first matrix != cols of second matrix\n");
    }
    MyMatrix matrix_temp(rows_, other.cols_);
    for (int i = 0; i < rows_; i++) {
        for (int j = 0; j < other.cols_; j++) {
            for (int k = 0; k < cols_; k++) {
                matrix_temp.matrix_[i][j] += matrix_[i][k] * other.matrix_[k][j];
            }
        }
    }
    *this = matrix_temp;
}

MyMatrix MyMatrix::transpose() const {
    MyMatrix matrix_result(cols_, rows_);
    for (int i = 0; i < rows_; i++) {
        for (int j = 0; j < cols_; j++) {
            matrix_result.matrix_[j][i] = matrix_[i][j];
        }
    }
    return matrix_result;
}

double MyMatrix::determinant() const {
    if (rows_ != cols_) {
        throw std::domain_error("In method determinant: rows != cols\n");
    }
    double result { 0 };
    if (rows_ == 1) {
        result = matrix_[0][0];
    } else if (rows_ == 2) {
        result = (matrix_[0][0] * matrix_[1][1]) - (matrix_[1][0] * matrix_[0][1]);
    } else {
        for (int i = 0; i < rows_; i++) {
            MyMatrix minor = minorMatrix(0, i);
            result += (i % 2 ? -1 : 1) * matrix_[0][i] * minor.determinant();
        }
    }
    return result;
}

MyMatrix MyMatrix::calc_complements() const {
    if (rows_ != cols_) {
        throw std::invalid_argument("In method calc_complements: rows != cols\n");
    }
    MyMatrix matrix_result(*this);
    for (int i = 0; i < matrix_result.rows_; i++) {
        for (int j = 0; j < matrix_result.cols_; j++) {
            MyMatrix minor = minorMatrix(i, j);
            double det = minor.determinant();
            matrix_result.matrix_[i][j] = pow(-1, i+j) * det;
        }
    }
    return matrix_result;
}

MyMatrix MyMatrix::inverse_matrix() const {
    double det = determinant();
    if (det == 0) {
        throw std::domain_error("In method inverse_matrix: determinant = 0\n");
    }
    MyMatrix matrix_result(rows_, cols_);
    MyMatrix complements = calc_complements();
    MyMatrix trans = complements.transpose();
    for (int i = 0; i < trans.rows_; i++) {
        for (int j = 0; j < trans.cols_; j++) {
            matrix_result.matrix_[i][j] = trans.matrix_[i][j] / det;
        }
    }
    return matrix_result;
}

// operator overloading
namespace My_matrix_cpp {
MyMatrix operator+(const MyMatrix& left, const MyMatrix& right) {
    MyMatrix result(left);
    return result += right;
}

MyMatrix operator-(const MyMatrix& left, const MyMatrix& right) {
    MyMatrix result(left);
    return result -= right;
}

MyMatrix operator*(const MyMatrix& left, const MyMatrix& right) {
    MyMatrix result(left);
    return result *= right;
}

MyMatrix operator*(const MyMatrix& left, const double num) {
    MyMatrix result(left);
    return result *= num;
}

MyMatrix operator*(const double num, const MyMatrix& right) {
    MyMatrix result(right);
    return result *= num;
}
}  //  namespace My_matrix_cpp

bool MyMatrix::operator==(const MyMatrix& other) const {
    return this->eq_matrix(other);
}

MyMatrix& MyMatrix::operator=(const MyMatrix& other) {
    if (this != &other) {
        deleteMatrix();           //  на случай, если матрица2 > матрицы1, чтобы выделить память
        rows_ = other.rows_;
        cols_ = other.cols_;
        createMatrix(rows_, cols_);
        copyMatrix(other);
    }
    return *this;
}

MyMatrix& MyMatrix::operator+=(const MyMatrix& other) {
    sum_matrix(other);
    return *this;
}

MyMatrix& MyMatrix::operator-=(const MyMatrix& other) {
    sub_matrix(other);
    return *this;
}

MyMatrix& MyMatrix::operator*=(double num) {
    mul_number(num);
    return *this;
}

MyMatrix& MyMatrix::operator*=(const MyMatrix& other) {
    mul_matrix(other);
    return *this;
}

double& MyMatrix::operator()(int rows, int cols) {
    if (rows >= rows_ || cols >= cols_ || rows < 0 || cols < 0) {
        throw std::out_of_range("Incorrect input, index is out of range\n");
    }
    return matrix_[rows][cols];
}

double MyMatrix::operator()(int rows, int cols) const {
    if (rows >= rows_ || cols >= cols_ || rows < 0 || cols < 0) {
        throw std::out_of_range("Incorrect input, index is out of range\n");
    }
    return matrix_[rows][cols];
}

//  helpers
void MyMatrix::createMatrix(int rows, int cols) {
    matrix_ = new double* [rows];
    for (int i = 0; i < rows; i++) {
        matrix_[i] = new double[cols]{ 0 };
    }
}

void MyMatrix::deleteMatrix() {
    if (matrix_) {
        for (int i = 0; i < rows_; ++i) {
            delete[] matrix_[i];
        }
        delete[] matrix_;
    }
}

void MyMatrix::copyMatrix(const MyMatrix& other) {
    for (int i = 0; i < rows_; ++i) {
        for (int j = 0; j < cols_; ++j) {
            matrix_[i][j] = other.matrix_[i][j];
        }
    }
}

MyMatrix MyMatrix::minorMatrix(int row, int col) const {
    MyMatrix minor(rows_ - 1, cols_ - 1);
    for (int i = 0; i < minor.rows_; i++) {
        for (int j = 0; j < minor.cols_; j++) {
            if (i >= row && j >= col) {
                minor.matrix_[i][j] = matrix_[i+1][j+1];
            } else if (i >= row) {
                minor.matrix_[i][j] = matrix_[i+1][j];
            } else if (j >= col) {
                minor.matrix_[i][j] = matrix_[i][j+1];
            } else {
                minor.matrix_[i][j] = matrix_[i][j];
            }
        }
    }
    return minor;
}

void MyMatrix::print_matrix() {
    for (int i = 0; i < rows_; i++) {
        for (int j = 0; j < cols_; j++) {
            std::cout << matrix_[i][j] << "\t";
        }
        std::cout << "\n";
    }
    std::cout << "rows = " << rows_ << "\n";
    std::cout << "cols = " << cols_ << "\n";
}
