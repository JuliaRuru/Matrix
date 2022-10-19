#ifndef SRC_MATRIX_OOP_H_
#define SRC_MATRIX_OOP_H_

#include <iostream>
#include <cmath>

class MyMatrix {
 public:
    MyMatrix() noexcept;
    MyMatrix(int rows, int cols);
    MyMatrix(const MyMatrix& other);
    MyMatrix(MyMatrix&& other);
    ~MyMatrix();

    //  accessors
    int getRows() const;
    int getCols() const;

    //  mutators
    void setRows(int rows);
    void setCols(int cols);

    //  public methods
    bool eq_matrix(const MyMatrix& other) const;
    void sum_matrix(const MyMatrix& other);
    void sub_matrix(const MyMatrix& other);
    void mul_number(const double num);
    void mul_matrix(const MyMatrix& other);
    MyMatrix transpose() const;
    double determinant() const;
    MyMatrix calc_complements() const;
    MyMatrix inverse_matrix() const;
    void print_matrix();
    static constexpr double EPS { 1e-7 };

    //  operator overloading
    bool operator==(const MyMatrix& other) const;
    MyMatrix& operator=(const MyMatrix& other);
    MyMatrix& operator+=(const MyMatrix& other);
    MyMatrix& operator-=(const MyMatrix& other);
    MyMatrix& operator*=(const MyMatrix& other);
    MyMatrix& operator*=(double num);
    double operator()(int row, int cols) const;
    double& operator()(int row, int cols);

 private:
    int rows_, cols_;            //  rows and columns attributes
    double** matrix_;            //  pointer to the memory where the matrix will be allocated

    void createMatrix(int rows, int cols);
    void deleteMatrix();
    void copyMatrix(const MyMatrix& other);
    MyMatrix minorMatrix(int row, int col) const;
};

namespace My_matrix_cpp {
MyMatrix operator+(const MyMatrix& left, const MyMatrix& right);
MyMatrix operator-(const MyMatrix& left, const MyMatrix& right);
MyMatrix operator*(const MyMatrix& left, const MyMatrix& right);
MyMatrix operator*(const MyMatrix& left, const double num);
MyMatrix operator*(const double num, const MyMatrix& right);
}  //  namespace My_matrix_cpp

#endif  //  SRC_MATRIX_OOP_H_
