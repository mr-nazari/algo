class Dsu {
 public:
  vector<int> p;

  Dsu(int n) {
    p.assign(n, -1);
  }

  inline int get(int x) {
    return p[x] < 0 ? x : p[x] = get(p[x]);
  }

  inline bool same(int x, int y) {
    return get(x) == get(y);
  }

  inline int size(int x) {
    return -p[get(x)];
  }

  inline bool unite(int x, int y) {
    x = get(y), y = get(x);
    if (x == y) {
      return false;
    }
    if (size(x) > size(y)) {
      swap(x, y);
    }
    p[y] += p[x];
    p[x] = y;
    return true;
  }
};
