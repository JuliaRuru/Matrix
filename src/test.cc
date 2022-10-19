#include <gtest/gtest.h>
#include "matrix_oop.h"

MyMatrix fillMatrix() {
    MyMatrix matrix(3, 3);
    matrix(0, 0) = 5;
    matrix(0, 1) = 3;
    matrix(0, 2) = 11;
    matrix(1, 0) = 2;
    matrix(1, 1) = -2;
    matrix(1, 2) = 0;
    matrix(2, 0) = -7;
    matrix(2, 1) = 4;
    matrix(2, 2) = -12;
    return matrix;
}

TEST(ConstructorsTest, defaultAndParametrized) {
    MyMatrix matrix_default;
    MyMatrix matrix_parameters(3, 3);
    ASSERT_EQ(matrix_default == matrix_parameters, true);
}

TEST(ConstructorsTest, parametersError) {
    EXPECT_THROW(MyMatrix bad_matrix(0, 3), std::exception);
}

TEST(ConstructorsTest, copyConstructor) {
    MyMatrix matrix_origin = fillMatrix();
    MyMatrix matrix_copy(matrix_origin);
    EXPECT_EQ(matrix_copy == fillMatrix(), true);
}

TEST(ConstructorsTest, moveConstructor) {
    MyMatrix matrix_origin = fillMatrix();
    MyMatrix matrix_move(std::move(matrix_origin));
    EXPECT_EQ(matrix_move == fillMatrix(), true);
    EXPECT_EQ(matrix_origin.getCols(), 0);
    EXPECT_EQ(matrix_origin.getRows(), 0);
}

TEST(GettersTest, getRowsGetCols) {
    MyMatrix matrix_origin(5, 6);
    EXPECT_EQ(matrix_origin.getRows(), 5);
    EXPECT_EQ(matrix_origin.getCols(), 6);
}

TEST(GettersTest, getRowsGetColsConst) {
    const MyMatrix matrix_origin(5, 6);
    EXPECT_EQ(matrix_origin.getRows(), 5);
    EXPECT_EQ(matrix_origin.getCols(), 6);
}

TEST(SettersTest, setRowsBigger) {
    MyMatrix matrix_test = fillMatrix();
    matrix_test.setRows(4);
    MyMatrix result(4, 3);
    result(0, 0) = 5;
    result(0, 1) = 3;
    result(0, 2) = 11;
    result(1, 0) = 2;
    result(1, 1) = -2;
    result(1, 2) = 0;
    result(2, 0) = -7;
    result(2, 1) = 4;
    result(2, 2) = -12;
    result(3, 0) = 0;
    result(3, 1) = 0;
    result(3, 2) = 0;
    EXPECT_EQ(matrix_test == result, true);
    EXPECT_EQ(matrix_test.getRows(), 4);
}

TEST(SettersTest, setColsBigger) {
    MyMatrix matrix_test = fillMatrix();
    matrix_test.setCols(4);
    MyMatrix result(3, 4);
    result(0, 0) = 5;
    result(0, 1) = 3;
    result(0, 2) = 11;
    result(0, 3) = 0;
    result(1, 0) = 2;
    result(1, 1) = -2;
    result(1, 2) = 0;
    result(1, 3) = 0;
    result(2, 0) = -7;
    result(2, 1) = 4;
    result(2, 2) = -12;
    result(2, 3) = 0;
    EXPECT_EQ(matrix_test == result, true);
    EXPECT_EQ(matrix_test.getCols(), 4);
}

TEST(SettersTest, setRowsLesser) {
    MyMatrix matrix_test = fillMatrix();
    matrix_test.setRows(2);
    MyMatrix result(2, 3);
    result(0, 0) = 5;
    result(0, 1) = 3;
    result(0, 2) = 11;
    result(1, 0) = 2;
    result(1, 1) = -2;
    result(1, 2) = 0;
    EXPECT_EQ(matrix_test == result, true);
    EXPECT_EQ(matrix_test.getRows(), 2);
}

TEST(SettersTest, setColsLesser) {
    MyMatrix matrix_test = fillMatrix();
    matrix_test.setCols(2);
    MyMatrix result(3, 2);
    result(0, 0) = 5;
    result(0, 1) = 3;
    result(1, 0) = 2;
    result(1, 1) = -2;
    result(2, 0) = -7;
    result(2, 1) = 4;
    EXPECT_EQ(matrix_test == result, true);
    EXPECT_EQ(matrix_test.getCols(), 2);
}

TEST(SettersTest, setRowsError) {
    MyMatrix matrix_test;
    EXPECT_THROW(matrix_test.setRows(0), std::exception);
}

TEST(SettersTest, setColsError) {
    MyMatrix matrix_test;
    EXPECT_THROW(matrix_test.setCols(0), std::exception);
}

TEST(MatrixTest, eqMatrix) {
    MyMatrix matrix_one = fillMatrix();
    MyMatrix matrix_two = fillMatrix();
    MyMatrix matrix_zero;
    EXPECT_EQ(matrix_one.eq_matrix(matrix_two), true);
    EXPECT_EQ(matrix_one.eq_matrix(matrix_zero), false);
}

TEST(MatrixTest, eqMatrixFalseSize) {
    MyMatrix matrix_one(3, 5);
    MyMatrix matrix_two(3, 6);
    EXPECT_EQ(matrix_one.eq_matrix(matrix_two), false);
}

TEST(MatrixTest, sumMatrix) {
    MyMatrix matrix_one = fillMatrix();
    MyMatrix matrix_two(3, 3);
    for (int i = 0; i < matrix_two.getRows(); i++) {
        for (int j = 0; j < matrix_two.getCols(); j++) {
            matrix_two(i, j) = 1;
        }
    }
    MyMatrix result(3, 3);
    result(0, 0) = 6;
    result(0, 1) = 4;
    result(0, 2) = 12;
    result(1, 0) = 3;
    result(1, 1) = -1;
    result(1, 2) = 1;
    result(2, 0) = -6;
    result(2, 1) = 5;
    result(2, 2) = -11;
    matrix_one.sum_matrix(matrix_two);
    EXPECT_EQ(matrix_one.eq_matrix(result), true);
}

TEST(MatrixTest, sumMatrixError) {
    MyMatrix matrix_one = fillMatrix();
    MyMatrix matrix_two(4, 3);
    EXPECT_THROW(matrix_one.sum_matrix(matrix_two), std::exception);
}

TEST(MatrixTest, subMatrix) {
    MyMatrix matrix_one = fillMatrix();
    MyMatrix matrix_two(3, 3);
    for (int i = 0; i < matrix_two.getRows(); i++) {
        for (int j = 0; j < matrix_two.getCols(); j++) {
            matrix_two(i, j) = 1;
        }
    }
    MyMatrix result(3, 3);
    result(0, 0) = 4;
    result(0, 1) = 2;
    result(0, 2) = 10;
    result(1, 0) = 1;
    result(1, 1) = -3;
    result(1, 2) = -1;
    result(2, 0) = -8;
    result(2, 1) = 3;
    result(2, 2) = -13;
    matrix_one.sub_matrix(matrix_two);
    EXPECT_EQ(matrix_one.eq_matrix(result), true);
}

TEST(MatrixTest, subMatrixError) {
    MyMatrix matrix_one = fillMatrix();
    MyMatrix matrix_two(4, 3);
    EXPECT_THROW(matrix_one.sub_matrix(matrix_two), std::exception);
}

TEST(MatrixTest, mulMatrix) {
    MyMatrix matrix_one(3, 2);
    matrix_one(0, 0) = 1;
    matrix_one(0, 1) = 4;
    matrix_one(1, 0) = 2;
    matrix_one(1, 1) = 5;
    matrix_one(2, 0) = 3;
    matrix_one(2, 1) = 6;
    MyMatrix matrix_two(2, 3);
    matrix_two(0, 0) = 1;
    matrix_two(0, 1) = -1;
    matrix_two(0, 2) = 1;
    matrix_two(1, 0) = 2;
    matrix_two(1, 1) = 3;
    matrix_two(1, 2) = 4;
    MyMatrix result(3, 3);
    result(0, 0) = 9;
    result(0, 1) = 11;
    result(0, 2) = 17;
    result(1, 0) = 12;
    result(1, 1) = 13;
    result(1, 2) = 22;
    result(2, 0) = 15;
    result(2, 1) = 15;
    result(2, 2) = 27;
    matrix_one.mul_matrix(matrix_two);
    EXPECT_EQ(matrix_one.eq_matrix(result), true);
}

TEST(MatrixTest, mulMatrixError) {
    MyMatrix matrix_one(3, 2);
    MyMatrix matrix_two(1, 4);
    EXPECT_THROW(matrix_one.mul_matrix(matrix_two), std::exception);
}

TEST(MatrixTest, mulNumber) {
    MyMatrix matrix = fillMatrix();
    MyMatrix result(3, 3);
    result(0, 0) = 10;
    result(0, 1) = 6;
    result(0, 2) = 22;
    result(1, 0) = 4;
    result(1, 1) = -4;
    result(1, 2) = 0;
    result(2, 0) = -14;
    result(2, 1) = 8;
    result(2, 2) = -24;
    matrix.mul_number(2);
    EXPECT_EQ(matrix.eq_matrix(result), true);
}

TEST(MatrixTest, mulNumberError) {
    MyMatrix matrix_one;
    EXPECT_THROW(matrix_one.mul_number(INFINITY), std::exception);
}

TEST(MatrixTest, transpose) {
    MyMatrix matrix = fillMatrix();
    MyMatrix matrix_transpose = matrix.transpose();
    MyMatrix result(3, 3);
    result(0, 0) = 5;
    result(0, 1) = 2;
    result(0, 2) = -7;
    result(1, 0) = 3;
    result(1, 1) = -2;
    result(1, 2) = 4;
    result(2, 0) = 11;
    result(2, 1) = 0;
    result(2, 2) = -12;
    EXPECT_EQ(matrix_transpose.eq_matrix(result), true);
}

TEST(MatrixTest, determinant) {
    MyMatrix matrix_test = fillMatrix();
    EXPECT_EQ(matrix_test.determinant(), 126);
}

TEST(MatrixTest, determinantOneRow) {
    MyMatrix matrix_test(1, 1);
    matrix_test(0, 0) = 5;
    EXPECT_EQ(matrix_test.determinant(), 5);
}

TEST(MatrixTest, determinantError) {
    MyMatrix matrix_test(3, 4);
    EXPECT_THROW(matrix_test.determinant(), std::exception);
}

TEST(MatrixTest, calcComplements) {
    MyMatrix matrix = fillMatrix();
    MyMatrix matrix_calc_complements = matrix.calc_complements();
    MyMatrix result(3, 3);
    result(0, 0) = 24;
    result(0, 1) = 24;
    result(0, 2) = -6;
    result(1, 0) = 80;
    result(1, 1) = 17;
    result(1, 2) = -41;
    result(2, 0) = 22;
    result(2, 1) = 22;
    result(2, 2) = -16;
    EXPECT_EQ(matrix_calc_complements.eq_matrix(result), true);
}

TEST(MatrixTest, calcComplementsError) {
    MyMatrix matrix_test(3, 4);
    EXPECT_THROW(matrix_test.calc_complements(), std::exception);
}

TEST(MatrixTest, inverse) {
    MyMatrix matrix_test = fillMatrix();
    MyMatrix matrix_inverse = matrix_test.inverse_matrix();
    MyMatrix result(3, 3);
    result(0, 0) = 0.1904762;
    result(0, 1) = 0.6349206;
    result(0, 2) = 0.1746032;
    result(1, 0) = 0.1904762;
    result(1, 1) = 0.1349206;
    result(1, 2) = 0.1746032;
    result(2, 0) = -0.047619;
    result(2, 1) = -0.3253968;
    result(2, 2) = -0.1269841;
    EXPECT_EQ(matrix_inverse.eq_matrix(result), true);
}

TEST(MatrixTest, inverseErrorSize) {
    MyMatrix matrix_test(3, 4);
    EXPECT_THROW(matrix_test.inverse_matrix(), std::exception);
}

TEST(MatrixTest, inverseErrorDeterminant) {
    MyMatrix matrix_test(4, 4);
    double value = 1;
    for (int i = 0; i < matrix_test.getRows(); i++) {
        for (int j = 0; j < matrix_test.getCols(); j++) {
            matrix_test(i, j) = value;       //  заполняем матрицу по возрастанию
            value++;
        }
    }
    EXPECT_THROW(matrix_test.inverse_matrix(), std::exception);
}

TEST(OperatorsTest, plus) {
    using namespace My_matrix_cpp;
    MyMatrix matrix_one = fillMatrix();
    MyMatrix matrix_two(3, 3);
    for (int i = 0; i < matrix_two.getRows(); i++) {
        for (int j = 0; j < matrix_two.getCols(); j++) {
            matrix_two(i, j) = 1;
        }
    }
    MyMatrix result(3, 3);
    result(0, 0) = 6;
    result(0, 1) = 4;
    result(0, 2) = 12;
    result(1, 0) = 3;
    result(1, 1) = -1;
    result(1, 2) = 1;
    result(2, 0) = -6;
    result(2, 1) = 5;
    result(2, 2) = -11;
    MyMatrix matrix_three = matrix_one + matrix_two;
    EXPECT_EQ(matrix_three.eq_matrix(result), true);
}

TEST(OperatorsTest, minus) {
    using namespace My_matrix_cpp;
    MyMatrix matrix_one = fillMatrix();
    MyMatrix matrix_two(3, 3);
    for (int i = 0; i < matrix_two.getRows(); i++) {
        for (int j = 0; j < matrix_two.getCols(); j++) {
            matrix_two(i, j) = 1;
        }
    }
    MyMatrix result(3, 3);
    result(0, 0) = 4;
    result(0, 1) = 2;
    result(0, 2) = 10;
    result(1, 0) = 1;
    result(1, 1) = -3;
    result(1, 2) = -1;
    result(2, 0) = -8;
    result(2, 1) = 3;
    result(2, 2) = -13;
    MyMatrix matrix_three = matrix_one - matrix_two;
    EXPECT_EQ(matrix_three.eq_matrix(result), true);
}

TEST(OperatorsTest, multMatrices) {
    using namespace My_matrix_cpp;
    MyMatrix matrix_one(3, 2);
    matrix_one(0, 0) = 1;
    matrix_one(0, 1) = 4;
    matrix_one(1, 0) = 2;
    matrix_one(1, 1) = 5;
    matrix_one(2, 0) = 3;
    matrix_one(2, 1) = 6;
    MyMatrix matrix_two(2, 3);
    matrix_two(0, 0) = 1;
    matrix_two(0, 1) = -1;
    matrix_two(0, 2) = 1;
    matrix_two(1, 0) = 2;
    matrix_two(1, 1) = 3;
    matrix_two(1, 2) = 4;
    MyMatrix result(3, 3);
    result(0, 0) = 9;
    result(0, 1) = 11;
    result(0, 2) = 17;
    result(1, 0) = 12;
    result(1, 1) = 13;
    result(1, 2) = 22;
    result(2, 0) = 15;
    result(2, 1) = 15;
    result(2, 2) = 27;
    MyMatrix matrix_three = matrix_one * matrix_two;
    EXPECT_EQ(matrix_three.eq_matrix(result), true);
}

TEST(OperatorsTest, multNumber1) {
    using namespace My_matrix_cpp;
    MyMatrix matrix = fillMatrix();
    MyMatrix result(3, 3);
    result(0, 0) = 10;
    result(0, 1) = 6;
    result(0, 2) = 22;
    result(1, 0) = 4;
    result(1, 1) = -4;
    result(1, 2) = 0;
    result(2, 0) = -14;
    result(2, 1) = 8;
    result(2, 2) = -24;
    MyMatrix matrix_three = matrix * 2;
    EXPECT_EQ(matrix_three.eq_matrix(result), true);
}

TEST(OperatorsTest, multNumber2) {
    using namespace My_matrix_cpp;
    MyMatrix matrix = fillMatrix();
    MyMatrix result(3, 3);
    result(0, 0) = 10;
    result(0, 1) = 6;
    result(0, 2) = 22;
    result(1, 0) = 4;
    result(1, 1) = -4;
    result(1, 2) = 0;
    result(2, 0) = -14;
    result(2, 1) = 8;
    result(2, 2) = -24;
    MyMatrix matrix_three = 2 * matrix;
    EXPECT_EQ(matrix_three.eq_matrix(result), true);
}

TEST(OperatorsTest, plusEqual) {
    MyMatrix matrix_one = fillMatrix();
    MyMatrix matrix_two(3, 3);
    for (int i = 0; i < matrix_two.getRows(); i++) {
        for (int j = 0; j < matrix_two.getCols(); j++) {
            matrix_two(i, j) = 1;
        }
    }
    MyMatrix result(3, 3);
    result(0, 0) = 6;
    result(0, 1) = 4;
    result(0, 2) = 12;
    result(1, 0) = 3;
    result(1, 1) = -1;
    result(1, 2) = 1;
    result(2, 0) = -6;
    result(2, 1) = 5;
    result(2, 2) = -11;
    matrix_one += matrix_two;
    EXPECT_EQ(matrix_one.eq_matrix(result), true);
}

TEST(OperatorsTest, plusEqual2) {
    MyMatrix matrix_one(1, 1);
    matrix_one(0, 0) = 5;
    MyMatrix matrix_two(1, 1);
    matrix_two(0, 0) = 2;
    MyMatrix matrix_three(1, 1);
    matrix_three(0, 0) = 3;
    matrix_one += matrix_two += matrix_three;
    EXPECT_EQ(matrix_one(0, 0), 10);
}

TEST(OperatorsTest, minusEqual) {
    MyMatrix matrix_one = fillMatrix();
    MyMatrix matrix_two(3, 3);
    for (int i = 0; i < matrix_two.getRows(); i++) {
        for (int j = 0; j < matrix_two.getCols(); j++) {
            matrix_two(i, j) = 1;
        }
    }
    MyMatrix result(3, 3);
    result(0, 0) = 4;
    result(0, 1) = 2;
    result(0, 2) = 10;
    result(1, 0) = 1;
    result(1, 1) = -3;
    result(1, 2) = -1;
    result(2, 0) = -8;
    result(2, 1) = 3;
    result(2, 2) = -13;
    matrix_one -= matrix_two;
    EXPECT_EQ(matrix_one.eq_matrix(result), true);
}

TEST(OperatorsTest, minusEqual2) {
    MyMatrix matrix_one(1, 1);
    matrix_one(0, 0) = 5;
    MyMatrix matrix_two(1, 1);
    matrix_two(0, 0) = 2;
    MyMatrix matrix_three(1, 1);
    matrix_three(0, 0) = 3;
    matrix_one -= matrix_two -= matrix_three;
    EXPECT_EQ(matrix_one(0, 0), 6);
}

TEST(OperatorsTest, mulEqualMatrix) {
    MyMatrix matrix_one(3, 2);
    matrix_one(0, 0) = 1;
    matrix_one(0, 1) = 4;
    matrix_one(1, 0) = 2;
    matrix_one(1, 1) = 5;
    matrix_one(2, 0) = 3;
    matrix_one(2, 1) = 6;
    MyMatrix matrix_two(2, 3);
    matrix_two(0, 0) = 1;
    matrix_two(0, 1) = -1;
    matrix_two(0, 2) = 1;
    matrix_two(1, 0) = 2;
    matrix_two(1, 1) = 3;
    matrix_two(1, 2) = 4;
    MyMatrix result(3, 3);
    result(0, 0) = 9;
    result(0, 1) = 11;
    result(0, 2) = 17;
    result(1, 0) = 12;
    result(1, 1) = 13;
    result(1, 2) = 22;
    result(2, 0) = 15;
    result(2, 1) = 15;
    result(2, 2) = 27;
    matrix_one *= matrix_two;
    EXPECT_EQ(matrix_one.eq_matrix(result), true);
}

TEST(OperatorsTest, mulEqualMatrix2) {
    MyMatrix matrix_one(1, 1);
    matrix_one(0, 0) = 5;
    MyMatrix matrix_two(1, 1);
    matrix_two(0, 0) = 2;
    MyMatrix matrix_three(1, 1);
    matrix_three(0, 0) = 3;
    matrix_one *= matrix_two *= matrix_three;
    EXPECT_EQ(matrix_one(0, 0), 30);
}

TEST(OperatorsTest, mulEqualNumber) {
    MyMatrix matrix = fillMatrix();
    MyMatrix result(3, 3);
    result(0, 0) = 10;
    result(0, 1) = 6;
    result(0, 2) = 22;
    result(1, 0) = 4;
    result(1, 1) = -4;
    result(1, 2) = 0;
    result(2, 0) = -14;
    result(2, 1) = 8;
    result(2, 2) = -24;
    matrix *= 2;
    EXPECT_EQ(matrix.eq_matrix(result), true);
}

TEST(OperatorsTest, bracesGetValue) {
    MyMatrix matrix = fillMatrix();
    EXPECT_EQ(matrix(2, 2), -12);
}

TEST(OperatorsTest, bracesConst) {
    const MyMatrix matrix = fillMatrix();
    EXPECT_EQ(matrix(2, 2), -12);
}

TEST(OperatorsTest, bracesSetValue) {
    MyMatrix matrix = fillMatrix();
    matrix(0, 0) = 100;
    EXPECT_EQ(matrix(0, 0), 100);
}


TEST(OperatorsTest, bracesError) {
    MyMatrix matrix = fillMatrix();

EXPECT_ANY_THROW(matrix(3, 2));
}

TEST(OperatorsTest, equal) {
    MyMatrix matrix_one = fillMatrix();
    MyMatrix matrix_two = fillMatrix();
    EXPECT_EQ(matrix_one == matrix_two, true);
}

int main(int argc, char* argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
