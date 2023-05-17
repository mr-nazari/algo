struct Matrix {
   vector<vector<int>> data;
   int n, m;

   Matrix() {}

   Matrix(int _n, int _m) : n(_n), m(_m), data(n, vector<int>(m)) {}

   Matrix(vector<vector<int>> _data) : n(_data.size()), m(_data[0].size()), data(_data) {}

   vector<int> operator[](int row) {
      return data[row];
   }

   Matrix operator+(const Matrix& other) {
      if (n != other.n || m != other.m) {
         return Matrix();
      }
      vector<vector<int>> ret(n, vector<int>(m));
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
      vector<vector<int>> ret(n, vector<int>(m));
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
      vector<vector<int>> ret(n, vector<int>(other.m));
      for (int i = 0; i < n; ++i) {
         for (int j = 0; j < other.m; ++j) {
            for (int k = 0; k < m; ++k) {
               ret[i][j] += data[i][k] * other.data[k][j];
            }
         }
      }
      return Matrix(ret);
   }

   Matrix operator^(int p) {
      if (n != m) {
         return Matrix();
      }
      if (p == 0) {
         vector<vector<int>> identity(n, vector<int>(n));
         for (int i = 0; i < n; ++i) {
            identity[i][i] = 1;
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
