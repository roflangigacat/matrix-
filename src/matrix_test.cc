#include <gtest/gtest.h>

#include "matrix_oop.h"

TEST(Matrix, DefaultCreation) {
  Matrix test;
  ASSERT_EQ(test.GetRows(), 3);
  ASSERT_EQ(test.GetCols(), 3);
  for (int i = 0; i < test.GetRows(); ++i) {
    for (int j = 0; j < test.GetCols(); ++j) {
      ASSERT_EQ(test(i, j), 0.0);
    }
  }
}

TEST(Matrix, DefaultCopy) {
  Matrix a(2, 2);
  Matrix b(2, 2);
  a(0, 0) = 3;
  a(0, 1) = 8;
  a(1, 0) = 1;
  a(1, 1) = 8;
  b(0, 0) = 12;
  b(0, 1) = 16;
  b(1, 0) = 3;
  b(1, 1) = 1;
  a = b;
  Matrix c(a);
  bool result = c.EqMatrix(a);
  ASSERT_EQ(result, 1);
  for (int i = 0; i < b.GetRows(); ++i) {
    for (int j = 0; j < b.GetCols(); ++j) {
      ASSERT_DOUBLE_EQ(a(i, j), b(i, j));
    }
  }
}

TEST(Matrix, Errors) {
  ASSERT_ANY_THROW(Matrix(-1, 1));
  ASSERT_ANY_THROW(Matrix(0, 0));
  Matrix a(3, 2);
  Matrix b;
  a(0, 0) = 1;
  a(0, 1) = 2;
  a(1, 0) = 3;
  a(1, 1) = 4;
  a(2, 0) = 5;
  a(2, 1) = 6;
  b(0, 0) = 9;
  b(0, 1) = 8;
  b(0, 2) = 7;
  b(1, 0) = 6;
  b(1, 1) = 5;
  b(1, 2) = 4;
  b(2, 0) = 3;
  b(2, 1) = 2;
  b(2, 2) = 1;
  ASSERT_ANY_THROW(a.MulMatrix(Matrix(-1, 1)));
  ASSERT_ANY_THROW(a.SumMatrix(b));
  ASSERT_ANY_THROW(a + b);
  ASSERT_ANY_THROW(a.SubMatrix(b));
  ASSERT_ANY_THROW(a - b);
}

TEST(Matrix, EqMatrix1) {
  Matrix b;
  Matrix a;
  Matrix c(2, 2);
  Matrix d;
  b(0, 0) = 9;
  b(0, 1) = 8;
  b(0, 2) = 7;
  b(1, 0) = 6;
  b(1, 1) = 5;
  b(1, 2) = 4;
  b(2, 0) = 3;
  b(2, 1) = 2;
  b(2, 2) = 1;
  a(0, 0) = 36;
  a(0, 1) = 32;
  a(0, 2) = 28;
  a(1, 0) = 24;
  a(1, 1) = 20;
  a(1, 2) = 16;
  a(2, 0) = 12;
  a(2, 1) = 8;
  a(2, 2) = 4;
  c(0, 0) = 1;
  c(0, 1) = 2;
  c(1, 0) = 3;
  c(1, 1) = 4;
  d(0, 0) = 9;
  d(0, 1) = 8;
  d(0, 2) = 7;
  d(1, 0) = 6;
  d(1, 1) = 5;
  d(1, 2) = 4;
  d(2, 0) = 3;
  d(2, 1) = 2;
  d(2, 2) = 1;
  bool result = b.EqMatrix(a);
  bool result2 = b.EqMatrix(c);
  bool result3 = b.EqMatrix(d);
  ASSERT_EQ(result3, 1);
  ASSERT_EQ(result, 0);
  ASSERT_EQ(result2, 0);
}

TEST(Matrix, EqMatrix2) {
  Matrix a;
  Matrix b(1, 3);
  Matrix c(3, 1);
  Matrix d(1, 1);
  bool result = a.EqMatrix(c);
  bool result1 = a.EqMatrix(b);
  bool result3 = a.EqMatrix(d);
  bool result4 = b.EqMatrix(c);
  ASSERT_EQ(result, 0);
  ASSERT_EQ(result1, 0);
  ASSERT_EQ(result3, 0);
  ASSERT_EQ(result4, 0);
}

TEST(Matrix, MulNumber) {
  Matrix b;
  Matrix result;
  b(0, 0) = 9;
  b(0, 1) = 8;
  b(0, 2) = 7;
  b(1, 0) = 6;
  b(1, 1) = 5;
  b(1, 2) = 4;
  b(2, 0) = 3;
  b(2, 1) = 2;
  b(2, 2) = 1;
  result(0, 0) = 36;
  result(0, 1) = 32;
  result(0, 2) = 28;
  result(1, 0) = 24;
  result(1, 1) = 20;
  result(1, 2) = 16;
  result(2, 0) = 12;
  result(2, 1) = 8;
  result(2, 2) = 4;
  b.MulNumber(4);
  for (int i = 0; i < b.GetRows(); ++i) {
    for (int j = 0; j < b.GetCols(); ++j) {
      ASSERT_DOUBLE_EQ(b(i, j), result(i, j));
    }
  }
}

TEST(Matrix, MulNumber1) {
  Matrix b;
  Matrix result;
  b(0, 0) = 9;
  b(0, 1) = 8;
  b(0, 2) = 7;
  b(1, 0) = 6;
  b(1, 1) = 5;
  b(1, 2) = 4;
  b(2, 0) = 3;
  b(2, 1) = 2;
  b(2, 2) = 1;
  result(0, 0) = 36;
  result(0, 1) = 32;
  result(0, 2) = 28;
  result(1, 0) = 24;
  result(1, 1) = 20;
  result(1, 2) = 16;
  result(2, 0) = 12;
  result(2, 1) = 8;
  result(2, 2) = 4;
  b = b * 4;
  for (int i = 0; i < b.GetRows(); ++i) {
    for (int j = 0; j < b.GetCols(); ++j) {
      ASSERT_DOUBLE_EQ(b(i, j), result(i, j));
    }
  }
}

TEST(Matrix, SumMatrix) {
  Matrix a;
  Matrix b;
  Matrix c(3, 2);
  Matrix ResultSum;
  Matrix d;
  Matrix e;
  Matrix f, g;
  b(0, 0) = 9;
  b(0, 1) = 8;
  b(0, 2) = 7;
  b(1, 0) = 6;
  b(1, 1) = 5;
  b(1, 2) = 4;
  b(2, 0) = 3;
  b(2, 1) = 2;
  b(2, 2) = 1;
  a(0, 0) = 36;
  a(0, 1) = 32;
  a(0, 2) = 28;
  a(1, 0) = 24;
  a(1, 1) = 20;
  a(1, 2) = 16;
  a(2, 0) = 12;
  a(2, 1) = 8;
  a(2, 2) = 4;

  ResultSum(0, 0) = 45;
  ResultSum(0, 1) = 40;
  ResultSum(0, 2) = 35;
  ResultSum(1, 0) = 30;
  ResultSum(1, 1) = 25;
  ResultSum(1, 2) = 20;
  ResultSum(2, 0) = 15;
  ResultSum(2, 1) = 10;
  ResultSum(2, 2) = 5;

  d(0, 0) = 9;
  d(0, 1) = 8;
  d(0, 2) = 7;
  d(1, 0) = 6;
  d(1, 1) = 5;
  d(1, 2) = 4;
  d(2, 0) = 3;
  d(2, 1) = 2;
  d(2, 2) = 1;
  e(0, 0) = 36;
  e(0, 1) = 32;
  e(0, 2) = 28;
  e(1, 0) = 24;
  e(1, 1) = 20;
  e(1, 2) = 16;
  e(2, 0) = 12;
  e(2, 1) = 8;
  e(2, 2) = 4;

  f(0, 0) = 9;
  f(0, 1) = 8;
  f(0, 2) = 7;
  f(1, 0) = 6;
  f(1, 1) = 5;
  f(1, 2) = 4;
  f(2, 0) = 3;
  f(2, 1) = 2;
  f(2, 2) = 1;
  g(0, 0) = 36;
  g(0, 1) = 32;
  g(0, 2) = 28;
  g(1, 0) = 24;
  g(1, 1) = 20;
  g(1, 2) = 16;
  g(2, 0) = 12;
  g(2, 1) = 8;
  g(2, 2) = 4;
  ASSERT_ANY_THROW(a.SumMatrix(c));
  b.SumMatrix(a);
  d = d + e;
  f += g;
  for (int i = 0; i < b.GetRows(); ++i) {
    for (int j = 0; j < b.GetCols(); ++j) {
      ASSERT_DOUBLE_EQ(ResultSum(i, j), b(i, j));
    }
  }
  for (int i = 0; i < d.GetRows(); ++i) {
    for (int j = 0; j < d.GetCols(); ++j) {
      ASSERT_DOUBLE_EQ(ResultSum(i, j), d(i, j));
    }
  }
  for (int i = 0; i < f.GetRows(); ++i) {
    for (int j = 0; j < f.GetCols(); ++j) {
      ASSERT_DOUBLE_EQ(ResultSum(i, j), f(i, j));
    }
  }
}

TEST(Matrix, SubMatrix) {
  Matrix a;
  Matrix b;
  Matrix ResultSub;
  Matrix c(3, 1);
  Matrix d;
  Matrix e;
  Matrix f;
  Matrix g;
  b(0, 0) = 9;
  b(0, 1) = 8;
  b(0, 2) = 7;
  b(1, 0) = 6;
  b(1, 1) = 5;
  b(1, 2) = 4;
  b(2, 0) = 3;
  b(2, 1) = 2;
  b(2, 2) = 1;
  a(0, 0) = 36;
  a(0, 1) = 32;
  a(0, 2) = 28;
  a(1, 0) = 24;
  a(1, 1) = 20;
  a(1, 2) = 16;
  a(2, 0) = 12;
  a(2, 1) = 8;
  a(2, 2) = 4;
  ResultSub(0, 0) = -27;
  ResultSub(0, 1) = -24;
  ResultSub(0, 2) = -21;
  ResultSub(1, 0) = -18;
  ResultSub(1, 1) = -15;
  ResultSub(1, 2) = -12;
  ResultSub(2, 0) = -9;
  ResultSub(2, 1) = -6;
  ResultSub(2, 2) = -3;
  d(0, 0) = 9;
  d(0, 1) = 8;
  d(0, 2) = 7;
  d(1, 0) = 6;
  d(1, 1) = 5;
  d(1, 2) = 4;
  d(2, 0) = 3;
  d(2, 1) = 2;
  d(2, 2) = 1;
  e(0, 0) = 36;
  e(0, 1) = 32;
  e(0, 2) = 28;
  e(1, 0) = 24;
  e(1, 1) = 20;
  e(1, 2) = 16;
  e(2, 0) = 12;
  e(2, 1) = 8;
  e(2, 2) = 4;

  f(0, 0) = 9;
  f(0, 1) = 8;
  f(0, 2) = 7;
  f(1, 0) = 6;
  f(1, 1) = 5;
  f(1, 2) = 4;
  f(2, 0) = 3;
  f(2, 1) = 2;
  f(2, 2) = 1;
  g(0, 0) = 36;
  g(0, 1) = 32;
  g(0, 2) = 28;
  g(1, 0) = 24;
  g(1, 1) = 20;
  g(1, 2) = 16;
  g(2, 0) = 12;
  g(2, 1) = 8;
  g(2, 2) = 4;
  ASSERT_ANY_THROW(a.SubMatrix(c));
  b.SubMatrix(a);
  d = d - e;
  f -= g;
  for (int i = 0; i < b.GetRows(); ++i) {
    for (int j = 0; j < b.GetCols(); ++j) {
      ASSERT_DOUBLE_EQ(ResultSub(i, j), b(i, j));
    }
  }
  for (int i = 0; i < d.GetRows(); ++i) {
    for (int j = 0; j < d.GetCols(); ++j) {
      ASSERT_DOUBLE_EQ(ResultSub(i, j), d(i, j));
    }
  }
  for (int i = 0; i < f.GetRows(); ++i) {
    for (int j = 0; j < f.GetCols(); ++j) {
      ASSERT_DOUBLE_EQ(ResultSub(i, j), f(i, j));
    }
  }
}

TEST(Matrix, MulMatrix) {
  Matrix a;
  Matrix b;
  Matrix c(3, 1);
  Matrix result;
  Matrix result2(3, 1);
  Matrix d;
  a(0, 0) = 1;
  a(0, 1) = 2;
  a(0, 2) = 3;
  a(1, 0) = 3;
  a(1, 1) = 2;
  a(1, 2) = 1;
  a(2, 0) = 4;
  a(2, 1) = 3;
  a(2, 2) = 1;
  b(0, 0) = 9;
  b(0, 1) = 8;
  b(0, 2) = 7;
  b(1, 0) = 6;
  b(1, 1) = 5;
  b(1, 2) = 4;
  b(2, 0) = 3;
  b(2, 1) = 2;
  b(2, 2) = 1;
  c(0, 0) = 1;
  c(1, 0) = 2;
  c(2, 0) = 3;
  a.MulMatrix(b);
  d(0, 0) = 1;
  d(0, 1) = 2;
  d(0, 2) = 3;
  d(1, 0) = 3;
  d(1, 1) = 2;
  d(1, 2) = 1;
  d(2, 0) = 4;
  d(2, 1) = 3;
  d(2, 2) = 1;
  d.MulMatrix(c);
  result(0, 0) = 30;
  result(0, 1) = 24;
  result(0, 2) = 18;
  result(1, 0) = 42;
  result(1, 1) = 36;
  result(1, 2) = 30;
  result(2, 0) = 57;
  result(2, 1) = 49;
  result(2, 2) = 41;
  result2(0, 0) = 14;
  result2(1, 0) = 10;
  result2(2, 0) = 13;
  bool res = a.EqMatrix(result);
  bool res2 = d.EqMatrix(result2);
  ASSERT_EQ(res, 1);
  ASSERT_EQ(res2, 1);
}

TEST(Matrix, MulMatrix2) {
  Matrix a, b, d, result;
  Matrix c(3, 1);
  Matrix result2(3, 1);
  a(0, 0) = 1;
  a(0, 1) = 2;
  a(0, 2) = 3;
  a(1, 0) = 3;
  a(1, 1) = 2;
  a(1, 2) = 1;
  a(2, 0) = 4;
  a(2, 1) = 3;
  a(2, 2) = 1;
  b(0, 0) = 9;
  b(0, 1) = 8;
  b(0, 2) = 7;
  b(1, 0) = 6;
  b(1, 1) = 5;
  b(1, 2) = 4;
  b(2, 0) = 3;
  b(2, 1) = 2;
  b(2, 2) = 1;
  c(0, 0) = 1;
  c(1, 0) = 2;
  c(2, 0) = 3;
  d(0, 0) = 1;
  d(0, 1) = 2;
  d(0, 2) = 3;
  d(1, 0) = 3;
  d(1, 1) = 2;
  d(1, 2) = 1;
  d(2, 0) = 4;
  d(2, 1) = 3;
  d(2, 2) = 1;
  result(0, 0) = 30;
  result(0, 1) = 24;
  result(0, 2) = 18;
  result(1, 0) = 42;
  result(1, 1) = 36;
  result(1, 2) = 30;
  result(2, 0) = 57;
  result(2, 1) = 49;
  result(2, 2) = 41;
  result2(0, 0) = 14;
  result2(1, 0) = 10;
  result2(2, 0) = 13;
  a = a * b;
  d *= c;
  bool res = a.EqMatrix(result);
  bool res2 = d == result2;
  for (int i = 0; i < d.GetRows(); ++i) {
    for (int j = 0; j < d.GetCols(); ++j) {
      ASSERT_DOUBLE_EQ(d(i, j), result2(i, j));
    }
  }
  ASSERT_EQ(res, 1);
  ASSERT_EQ(res2, 1);
}

TEST(Matrix, Determinant) {
  Matrix a;
  Matrix b(4, 4);
  a(0, 0) = 1;
  a(0, 1) = 2;
  a(0, 2) = 3;
  a(1, 0) = 4;
  a(1, 1) = 5;
  a(1, 2) = 6;
  a(2, 0) = 7;
  a(2, 1) = 8;
  a(2, 2) = 9;
  b(0, 0) = 1;
  b(0, 1) = 2;
  b(0, 2) = 3;
  b(0, 3) = 4;
  b(1, 0) = 5;
  b(1, 1) = 6;
  b(1, 2) = 7;
  b(1, 3) = 8;
  b(2, 0) = 9;
  b(2, 1) = 10;
  b(2, 2) = 11;
  b(2, 3) = 12;
  b(3, 0) = 13;
  b(3, 1) = 14;
  b(3, 2) = 15;
  b(3, 3) = 16;
  Matrix c(3, 1);
  c(0, 0) = 1;
  c(1, 0) = 2;
  c(2, 0) = 3;
  double det = a.Determinant();
  double det1 = b.Determinant();
  ASSERT_EQ(det, 0);
  ASSERT_EQ(det1, 0);
  ASSERT_ANY_THROW(c.Determinant());
}

TEST(Matrix, CalcComp) {
  Matrix a;
  Matrix resultcheck;
  Matrix result;
  a(0, 0) = 1;
  a(0, 1) = 2;
  a(0, 2) = 3;
  a(1, 0) = 0;
  a(1, 1) = 4;
  a(1, 2) = 2;
  a(2, 0) = 5;
  a(2, 1) = 2;
  a(2, 2) = 1;
  result(0, 0) = 0;
  result(0, 1) = 10;
  result(0, 2) = -20;
  result(1, 0) = 4;
  result(1, 1) = -14;
  result(1, 2) = 8;
  result(2, 0) = -8;
  result(2, 1) = -2;
  result(2, 2) = 4;
  Matrix c(3, 1);
  c(0, 0) = 1;
  c(1, 0) = 2;
  c(2, 0) = 3;
  resultcheck = a.CalcComplements();
  ASSERT_ANY_THROW(c.InverseMatrix());
  for (int i = 0; i < a.GetRows(); ++i) {
    for (int j = 0; j < a.GetCols(); ++j) {
      ASSERT_DOUBLE_EQ(resultcheck(i, j), result(i, j));
    }
  }
}

TEST(Matrix, InverseMatrix) {
  Matrix a;
  Matrix resultcheck;
  Matrix result;
  a(0, 0) = 2;
  a(0, 1) = 5;
  a(0, 2) = 7;
  a(1, 0) = 6;
  a(1, 1) = 3;
  a(1, 2) = 4;
  a(2, 0) = 5;
  a(2, 1) = -2;
  a(2, 2) = -3;
  result(0, 0) = 1;
  result(0, 1) = -1;
  result(0, 2) = 1;
  result(1, 0) = -38;
  result(1, 1) = 41;
  result(1, 2) = -34;
  result(2, 0) = 27;
  result(2, 1) = -29;
  result(2, 2) = 24;
  Matrix c(3, 1);
  c(0, 0) = 1;
  c(1, 0) = 2;
  c(2, 0) = 3;
  ASSERT_ANY_THROW(c.InverseMatrix());
  resultcheck = a.InverseMatrix();
  for (int i = 0; i < resultcheck.GetRows(); ++i) {
    for (int j = 0; j < resultcheck.GetCols(); ++j) {
      ASSERT_DOUBLE_EQ(resultcheck(i, j), result(i, j));
    }
  }
}

TEST(Matrix, mutator) {
  Matrix a, b, c;
  a.SetRows(4);
  a.SetCols(4);
  b.SetRows(2);
  b.SetCols(2);
  ASSERT_EQ(a.GetRows(), 4);
  ASSERT_EQ(a.GetCols(), 4);
  ASSERT_EQ(b.GetRows(), 2);
  ASSERT_EQ(b.GetCols(), 2);
  ASSERT_ANY_THROW(c.SetRows(0));
  ASSERT_ANY_THROW(c.SetCols(0));
}

TEST(Matrix, Constructor) {
  Matrix a;
  a(0, 0) = 2;
  a(0, 1) = 5;
  a(0, 2) = 7;
  a(1, 0) = 6;
  a(1, 1) = 3;
  a(1, 2) = 4;
  a(2, 0) = 5;
  a(2, 1) = -2;
  a(2, 2) = -3;
  Matrix b(a);
  Matrix c(std::move(a));
  bool res = b.EqMatrix(c);
  ASSERT_EQ(res, 1);
}
