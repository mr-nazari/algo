struct dsu {
  vector<int> e;

  dsu(int n) {
    e = vector<int>(n, -1);
  }

  int get(int x) {
    return e[x] < 0 ? x : e[x] = get(e[x]);
  }

  bool same_set(int a, int b) {
    return get(a) == get(b);
  }

  int size(int x) {
    return -e[get(x)];
  }

  bool unite(int a, int b) {
    a = get(a), b = get(b);
    if (a == b) {
      return false;
    }
    if (size(a) > size(b)) {
      swap(a, b);
    }
    e[b] += e[a];
    e[a] = b;
    return true;
  }
};
