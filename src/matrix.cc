#include "matrix_oop.h"

Matrix::Matrix() : Matrix(3, 3) {}

Matrix::Matrix(int rows, int cols) : rows_(rows), cols_(cols) {
  if (rows_ < 1 || cols_ < 1) {
    throw std::invalid_argument("error");
  }
  matrix_ = new double*[rows_];
  for (int i = 0; i < rows_; ++i) {
    matrix_[i] = new double[cols_]();
  }
}

Matrix::Matrix(const Matrix& other)
    : rows_(0), cols_(0), matrix_(nullptr) {
  *this = other;
}

Matrix::Matrix(Matrix&& other)
    : rows_(other.rows_), cols_(other.cols_), matrix_(other.matrix_) {
  other.rows_ = 0;
  other.cols_ = 0;
  other.matrix_ = nullptr;
}

Matrix::~Matrix() {
  for (int i = 0; i < rows_; ++i) {
    delete[] matrix_[i];
  }
  delete[] matrix_;
}

int Matrix::GetRows() const { return rows_; }
int Matrix::GetCols() const { return cols_; }

void Matrix::SetRows(int new_rows_count) {
  if (new_rows_count <= 0) {
    throw std::invalid_argument("error");
  }
  Matrix tmp(new_rows_count, cols_);
  for (int i = 0; i < (rows_ < new_rows_count ? rows_ : new_rows_count); ++i) {
    for (int j = 0; j < cols_; ++j) {
      tmp.matrix_[i][j] = this->matrix_[i][j];
    }
  }
  *this = std::move(tmp);
}

void Matrix::SetCols(int new_cols_count) {
  if (new_cols_count <= 0) {
    throw std::invalid_argument("error");
  }
  Matrix tmp(rows_, new_cols_count);
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < (cols_ < new_cols_count ? cols_ : new_cols_count);
         ++j) {
      tmp.matrix_[i][j] = this->matrix_[i][j];
    }
  }
  *this = std::move(tmp);
}

bool Matrix::EqMatrix(const Matrix& other) const {
  if (rows_ != other.rows_ || cols_ != other.cols_) {
    return false;
  }
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      if (fabs(matrix_[i][j] - other.matrix_[i][j]) > 1e-7) return false;
    }
  }
  return true;
}

bool Matrix::operator==(const Matrix& other) const {
  return this->EqMatrix(other);
}

double& Matrix::operator()(int row, int col) {
  if (row < 0 || col < 0 || row >= rows_ || col >= cols_) {
    throw std::invalid_argument("error");
  }
  return matrix_[row][col];
}

const double& Matrix::operator()(int row, int col) const {
  if (row < 0 || col < 0 || row >= rows_ || col >= cols_) {
    throw std::invalid_argument("error");
  }
  return matrix_[row][col];
}

Matrix Matrix::operator+(const Matrix& other) const {
  Matrix tmp(*this);
  tmp.SumMatrix(other);
  return tmp;
}

Matrix Matrix::operator-(const Matrix& other) const {
  Matrix tmp(*this);
  tmp.SubMatrix(other);
  return tmp;
}

Matrix& Matrix::operator=(const Matrix& other) {
  if (this != &other) {
    for (int i = 0; i < rows_; ++i) {
      delete[] matrix_[i];
    }
    delete[] matrix_;
    rows_ = other.rows_;
    cols_ = other.cols_;
    matrix_ = new double*[rows_];
    for (int i = 0; i < rows_; ++i) {
      matrix_[i] = new double[cols_];
      for (int j = 0; j < cols_; ++j) {
        matrix_[i][j] = other.matrix_[i][j];
      }
    }
  }
  return *this;
}

Matrix Matrix::operator*(const double num) const {
  Matrix tmp(*this);
  tmp.MulNumber(num);
  return tmp;
}

Matrix Matrix::operator*(const Matrix& other) const {
  Matrix tmp(*this);
  tmp.MulMatrix(other);
  return tmp;
}

Matrix& Matrix::operator+=(const Matrix& other) {
  SumMatrix(other);
  return *this;
}

Matrix& Matrix::operator-=(const Matrix& other) {
  SubMatrix(other);
  return *this;
}

Matrix& Matrix::operator*=(const Matrix& other) {
  MulMatrix(other);
  return *this;
}

Matrix& Matrix::operator*=(const double num) {
  MulNumber(num);
  return *this;
}

void Matrix::SumMatrix(const Matrix& other) {
  SumAndSubOperations(other, '+');
}

void Matrix::SubMatrix(const Matrix& other) {
  SumAndSubOperations(other, '-');
}

void Matrix::MulNumber(const double num) {
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      matrix_[i][j] *= num;
    }
  }
}

void Matrix::MulMatrix(const Matrix& other) {
  if (cols_ != other.rows_) {
    throw std::invalid_argument("error");
  }
  Matrix tmp(rows_, other.cols_);
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < other.cols_; ++j) {
      for (int k = 0; k < cols_; ++k) {
        tmp.matrix_[i][j] += matrix_[i][k] * other.matrix_[k][j];
      }
    }
  }
  *this = tmp;
}

Matrix Matrix::Transpose() const {
  Matrix tmp(cols_, rows_);
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      tmp.matrix_[j][i] = matrix_[i][j];
    }
  }
  return tmp;
}

double Matrix::Determinant() const {
  double result = 0.0;
  if (rows_ != cols_) {
    throw std::invalid_argument("error");
  }
  if (rows_ == 1) {
    result = matrix_[0][0];
  } else if (rows_ == 2) {
    result = (matrix_[0][0] * matrix_[1][1]) - (matrix_[1][0] * matrix_[0][1]);
  } else {
    double det;
    int sign = 1;
    for (int i = 0; i < rows_; ++i) {
      Matrix tmp(FindMinor(i, 0));
      det = tmp.Determinant();
      result = result + sign * matrix_[i][0] * det;
      sign = -sign;
    }
  }
  return result;
}

Matrix Matrix::CalcComplements() const {
  Matrix result(rows_, cols_);
  if (rows_ != cols_) {
    throw std::invalid_argument("error");
  }
  if (rows_ > 1 && cols_ > 1) {
    for (int i = 0; i < rows_; ++i) {
      for (int j = 0; j < cols_; ++j) {
       result.matrix_[i][j] = pow(-1, i + j) * FindMinor(i, j).Determinant();
      }
    }
  } else {
    result.matrix_[0][0] = 1;
  }
  return result;
}

Matrix Matrix::InverseMatrix() const {
  Matrix temp(*this);
  double det = temp.Determinant();
  if (rows_ != cols_ || det == 0) {
    throw std::invalid_argument("error");
  }
  Matrix CalcComp(rows_, cols_);
  Matrix TempTranspose(rows_, cols_);
  Matrix Result(rows_, cols_);
  CalcComp = temp.CalcComplements();
  TempTranspose = CalcComp.Transpose();
  Result = TempTranspose * (1.0 / det);
  return Result;
}

// extension

void Matrix::SumAndSubOperations(const Matrix& other, char type) {
  if (rows_ != other.rows_ || cols_ != other.cols_) {
    throw std::invalid_argument("length error");
  }
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      if (type == '+') {
        matrix_[i][j] += other.matrix_[i][j];
      } else if (type == '-') {
        matrix_[i][j] -= other.matrix_[i][j];
      }
    }
  }
}

Matrix Matrix::FindMinor(int rows, int columns) const {
  Matrix tmp(rows_ - 1, cols_ - 1);
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      int rws = i, clms = j;
      if (i == rows) {
        continue;
      } else if (i > rows) {
        rws--;
      }
      if (j == columns) {
        continue;
      } else if (j > columns) {
        clms--;
      }
      tmp.matrix_[rws][clms] = matrix_[i][j];
    }
  }
  return tmp;
}
