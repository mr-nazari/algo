template <typename T>
struct Matrix {
  vector<vector<T>> data;
  int n, m;

  Matrix() {}
  Matrix(int _n, int _m) : n(_n), m(_m), data(n, vector<T>(m)) {}
  Matrix(vector<vector<T>> _data) : n(_data.size()), m(_data[0].size()), data(_data) {}

  vector<T> operator[](int row) {
    return data[row];
  }
  Matrix operator+(const Matrix& other) {
    if (n != other.n || m != other.m) {
      return Matrix();
    }
    vector<vector<T>> ret(n, vector<T>(m));
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < m; ++j) {
        ret[i][j] = data[i][j] + other.data[i][j];
      }
    }
    return Matrix(ret);
  }
  Matrix operator+=(const Matrix& other) {
    *this = *this + other;
    return *this;
  }
  Matrix operator-(const Matrix& other) {
    if (n != other.n || m != other.m) {
      return Matrix();
    }
    vector<vector<T>> ret(n, vector<T>(m));
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < m; ++j) {
        ret[i][j] = data[i][j] - other.data[i][j];
      }
    }
    return Matrix(ret);
  }
  Matrix operator-=(const Matrix& other) {
    *this = *this - other;
    return *this;
  }
  Matrix operator*(const Matrix& other) {
    if (m != other.n) {
      return Matrix();
    }
    vector<vector<T>> ret(n, vector<T>(other.m));
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < other.m; ++j) {
        for (int k = 0; k < m; ++k) {
          ret[i][j] += data[i][k] * other.data[k][j];
        }
      }
    }
    return Matrix(ret);
  }
  template <typename U>
  Matrix operator^(U p) {
    if (n != m) {
      return Matrix();
    }
    if (p == 0) {
      vector<vector<T>> identity(n, vector<T>(n));
      for (int i = 0; i < n; ++i) {
        identity[i][i] = T(1);
      }
      return Matrix(identity);
    }
    Matrix mat = *this;
    if (p & 1) {
      return mat * ((mat * mat) ^ (p / 2));
    }
    return (mat * mat) ^ (p / 2);
  }

  void print(string seperator = " ", string endline = "\n") {
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < m; ++j) {
        cout << data[i][j] << seperator;
      }
      cout << endline;
    }
  }
};

template <typename T, typename U>
T fib(U n) {
  Matrix<T> base({
    {T(1), T(1)},
    {T(1), T(0)}
  });
  return (base ^ n)[0][1];
}
template <typename T, typename U>
pair<T, T> fib(U n) {
  if (n == 0) {
    return pair(0, 1);
  }
  auto [a, b] = fib<T>(n >> 1);
  auto [c, d] = pair(a * (2 * b - a), a * a + b * b);
  if (n & 1) {
    return pair(d, c + d);
  }
  return pair(c, d);
}
