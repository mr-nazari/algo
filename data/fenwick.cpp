template <typename T>
class Fenwick {
 public:
  Fenwick(int n = 0) {
    init(n);
  }

  void init(int n) {
    this->n = n;
    a.assign(n, T());
  }
  void add(int x, T v) {
    for (int i = x + 1; i <= n; i += i & -i) {
      a[i - 1] += v;
    }
  }

  T Sum(int x) {
    auto ans = T();
    for (int i = x; i > 0; i -= i & -i) {
      ans += a[i - 1];
    }
    return ans;
  }
  T RangeSum(int l, int r) {
    return Sum(r) - Sum(l);
  }
  int Kth(T k) {
    int x = 0;
    for (int i = 1 << std::__lg(n); i; i /= 2) {
      if (x + i <= n && k >= a[x + i - 1]) {
        x += i;
        k -= a[x - 1];
      }
    }
    return x;
  }

 private:
  std::vector<T> a;
  int n;
};
