template <typename T, class F = function<T(const T&, const T&)>>
struct SparseTable {
  int n;
  vector<vector<T>> mat;
  F func;

  SparseTable(const vector<T>& a, const F& f) : func(f) {
    n = (int) a.size();
    int max_log = (int) log2(n) + 1;
    mat.resize(max_log);
    mat[0] = a;
    for (int b = 1; b < max_log; ++b) {
      mat[b].resize(n - (1 << b) + 1);
      for (int i = 0; i + (1 << b) - 1 < n; ++i) {
        mat[b][i] = func(mat[b - 1][i], mat[b - 1][i + (1 << (b - 1))]);
      }
    }
  }

  T get(int from, int to) const {
    assert(0 <= from && from <= to && to <= n - 1);
    int lg = (int) log2(to - from + 1);
    return func(mat[lg][from], mat[lg][to - (1 << lg) + 1]);
  }
};
