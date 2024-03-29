template <typename T>
class Matrix {
 public:
  Matrix() {}
  Matrix(int _n, int _m) : n(_n), m(_m) {
    data = vector(n, vector<T>(m));
  }
  Matrix(vector<vector<T>> _data)
    : n(_data.size()), m(_data[0].size()), data(_data) {}
  Matrix(vector<T> vec) : n(vec.size()), m(1) {
    data = vector(n, vector<T>(m));
    for (int i = 0; i < n; ++i) {
      data[i][0] = vec[i];
    }
  }

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
      for (int k = 0; k < m; ++k) {
        for (int j = 0; j < other.m; ++j) {
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
    Matrix<T> res(n, n);
    for (int i = 0; i < n; ++i) {
      res[i][i] = (T) 1;
    }
    Matrix<T> mat = *this;
    while (p > 0) {
      if (p & 1) {
        res *= mat;
      }
      mat *= mat;
      p >>= 1;
    }
    return res;
  }

  template <typename V>
  friend vector<V> to_vector(Matrix<V> mat);

  template <typename V, typename U>
  friend V& operator<<(V& stream, Matrix<U> mat);

  template <typename V, typename U>
  friend V& operator>>(V& stream, Matrix<U>& mat);

 private:
  vector<vector<T>> data;
  int n, m;
};

template <typename T>
vector<T> to_vector(Matrix<T> mat) {
  if (mat.m > 1) {
    throw runtime_error("The input matrix isn't a vector.");
  }
  vector<T> res(mat.n);
  for (int i = 0; i < (int) res.size(); ++i) {
    res[i] = mat[i][0];
  }
  return res;
}

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
vector<T> CalculateLinearRecurrence(const vector<T>& bases,
                                    const vector<T>& coeff,
                                    U kth) {
  const int n = (int) bases.size();
  Matrix<T> X(n, n);
  for (int i = 0; i < n - 1; ++i) {
    X[i][i + 1] = 1;
  }
  for (int i = 0; i < n; ++i) {
    X[n - 1][i] = coeff[n - i - 1];
  }
  vector<T> res = to_vector(
                    (X ^ kth) * Matrix(bases)
                  );
  return res;
}

template <typename U, typename T = U>
T fib(U nth) {
  vector<T> bases{0, 1};
  vector<T> coeff{1, 1};
  return CalculateLinearRecurrence(
           bases, coeff,
           nth
         ).front();
}

template <typename T, typename U>
pair<T, T> rec_fib(U n) {
  if (n == 0) {
    return pair(0, 1);
  }
  auto [a, b] = rec_fib<T>(n >> 1);
  auto [c, d] = pair(a * (2 * b - a), a * a + b * b);
  if (n & 1) {
    return pair(d, c + d);
  }
  return pair(c, d);
}

template <int N, int M>
struct BinaryMatrix {
 public:
  bitset<N>& operator[](int row) {
    return data[row];
  }
  template <int K>
  BinaryMatrix<N, K> operator*(BinaryMatrix<M, K>& other) {
    BinaryMatrix<K, M> other_t;
    for (int i = 0; i < M; ++i) {
      for (int j = 0; j < K; ++j) {
        other_t[i][j] = other[j][i];
      }
    }
    BinaryMatrix<N, K> res;
    for (int i = 0; i < N; ++i) {
      for (int j = 0; j < K; ++j) {
        res[i][j] = (data[i] & other_t[j]).any();
      }
    }
    return res;
  }
  template <typename U>
  BinaryMatrix operator^(U p) {
    if (N != M) {
      throw runtime_error("Matrix is not quadratic.");
    }
    BinaryMatrix<N, N> res;
    for (int i = 0; i < N; ++i) {
      res[i][i] = 1;
    }
    BinaryMatrix<N, N> base = *this;
    while (p > 0) {
      if (p & 1) {
        res = res * base;
      }
      base = base * base;
      p >>= 1;
    }
    return res;
  }
  bitset<N> operator*(const bitset<N>& other) {
    bitset<N> res;
    for (int i = 0; i < N; ++i) {
      res[i] = (data[i] & other).any();
    }
    return res;
  }
 
 private:
  array<bitset<M>, N> data;
};
 
constexpr int N = 150;
using BMatrix = BinaryMatrix<N, N>;
