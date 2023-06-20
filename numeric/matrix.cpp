template <typename T>
class Matrix {
 public:
  Matrix() {}
  Matrix(int _n, int _m) : n(_n), m(_m) {
    data = vector(n, vector<T>(m));
  }
  Matrix(vector<vector<T>> _data)
    : n(_data.size()), m(_data[0].size()), data(_data) {}

  vector<T>& operator[](int row) {
    return data[row];
  }
  Matrix operator+(Matrix& other) {
    if (n != other.n || m != other.m) {
      throw runtime_error("Dimensions doesn't match.");
    }
    Matrix<T> res(n, m);
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < m; ++j) {
        res[i][j] = data[i][j] + other[i][j];
      }
    }
    return res;
  }
  Matrix& operator+=(const Matrix& other) {
    *this = *this + other;
    return *this;
  }
  Matrix operator-(Matrix& other) {
    if (n != other.n || m != other.m) {
      throw runtime_error("Dimensions doesn't match.");
    }
    Matrix<T> res(n, m);
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < m; ++j) {
        res[i][j] = data[i][j] - other[i][j];
      }
    }
    return res;
  }
  Matrix& operator-=(const Matrix& other) {
    *this = *this - other;
    return *this;
  }
  Matrix operator*(Matrix other) {
    if (m != other.n) {
      throw runtime_error("Dimensions doesn't match.");
    }
    Matrix<T> res(n, other.m);
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < other.m; ++j) {
        for (int k = 0; k < m; ++k) {
          res[i][j] += data[i][k] * other[k][j];
        }
      }
    }
    return res;
  }
  Matrix& operator*=(const Matrix& other) {
    *this = *this * other;
    return *this;
  }
  template <typename U>
  Matrix operator^(U p) {
    if (n != m) {
      throw runtime_error("Matrix is not quadratic.");
    }
    if (p == 0) {
      Matrix<T> I(n, n);
      for (int i = 0; i < n; ++i) {
        I[i][i] = (T) 1;
      }
      return I;
    }
    Matrix mat = *this;
    Matrix res = (mat * mat) ^ (p / 2);
    if (p & 1) {
      res *= mat;
    }
    return res;
  }

  template <typename V, typename U>
  friend V& operator<<(V& stream, Matrix<U> mat);

  template <typename V, typename U>
  friend V& operator>>(V& stream, Matrix<U>& mat);

 private:
  vector<vector<T>> data;
  int n, m;
};

template <typename U, typename T>
U& operator<<(U& stream, Matrix<T> mat) {
  for (int i = 0; i < mat.n; ++i) {
    for (int j = 0; j < mat.m; ++j) {
      stream << mat[i][j] << " ";
    }
    if (i + 1 == mat.n) {
      break;
    }
    stream << "\n";
  }
  return stream;
}

template <typename U, typename T>
U& operator>>(U& stream, Matrix<T>& mat) {
  for (int i = 0; i < mat.n; ++i) {
    for (int j = 0; j < mat.m; ++j) {
      stream >> mat[i][j];
    }
  }
  return stream;
}

template <typename T, typename U>
T fib(U n) {
  Matrix<T> base({
    {T(1), T(1)},
    {T(1), T(0)}
  });
  return (base ^ n)[0][1];
}
template <typename T, typename U>
pair<T, T> Fib(U n) {
  if (n == 0) {
    return pair(0, 1);
  }
  auto [a, b] = Fib<T>(n >> 1);
  auto [c, d] = pair(a * (2 * b - a), a * a + b * b);
  if (n & 1) {
    return pair(d, c + d);
  }
  return pair(c, d);
}
