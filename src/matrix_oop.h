#ifndef SRC_MATRIX_OOP_H
#define SRC_MATRIX_OOP_H

#include <cmath>
#include <stdexcept>

class Matrix {
 public:
  Matrix();
  Matrix(int rows, int cols);
  Matrix(const Matrix &other);
  Matrix(Matrix &&other);
  ~Matrix();

  int GetRows() const;
  int GetCols() const;
  void SetRows(int new_rows_count);
  void SetCols(int new_cols_count);

  double &operator()(int row, int col);
  const double &operator()(int row, int col) const;
  bool operator==(const Matrix &other) const;
  Matrix operator+(const Matrix &other) const;
  Matrix operator-(const Matrix &other) const;
  Matrix &operator=(const Matrix &other);
  Matrix operator*(const double num) const;
  Matrix operator*(const Matrix &other) const;
  Matrix &operator+=(const Matrix &other);
  Matrix &operator-=(const Matrix &other);
  Matrix &operator*=(const Matrix &other);
  Matrix &operator*=(const double num);

  bool EqMatrix(const Matrix &other) const;
  void SumMatrix(const Matrix &other);
  void SubMatrix(const Matrix &other);
  void MulNumber(const double num);
  void MulMatrix(const Matrix &other);
  Matrix Transpose() const;
  double Determinant() const;
  Matrix CalcComplements() const;
  Matrix InverseMatrix() const;

 private:
  Matrix FindMinor(int rows, int columns) const;
  void SumAndSubOperations(const Matrix &other, char type);
  int rows_, cols_;
  double **matrix_;
};

#endif  // SRC_MATRIX_OOP_H