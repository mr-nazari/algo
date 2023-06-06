template <class Info>
struct SegmentTree {
  std::vector<Info> info;
  int n;

  SegmentTree() : n(0) {}
  SegmentTree(int n_, Info v_ = Info()) {
    init(n_, v_);
  }
  template <class T>
  SegmentTree(std::vector<T> init_) {
    init(init_);
  }
  void init(int n_, Info v_ = Info()) {
    init(std::vector(n_, v_));
  }
  template <class T>
  void init(std::vector<T> init_) {
    n = init_.size();
    info.assign(4 << std::__lg(n), Info());
    std::function<void(int, int, int)> build = [&](int p, int l, int r) {
      if (r - l == 1) {
        info[p] = init_[l];
        return;
      }
      int m = (l + r) / 2;
      build(2 * p, l, m);
      build(2 * p + 1, m, r);
      pull(p);
    };
    build(1, 0, n);
  }
  void pull(int p) {
    info[p] = info[2 * p] + info[2 * p + 1];
  }
  void modify(int p, int l, int r, int x, const Info& v) {
    if (r - l == 1) {
      info[p] = v;
      return;
    }
    int m = (l + r) / 2;
    if (x < m) {
      modify(2 * p, l, m, x, v);
    } else {
      modify(2 * p + 1, m, r, x, v);
    }
    pull(p);
  }
  void modify(int p, const Info &v) {
    modify(1, 0, n, p, v);
  }

  Info range_query(int p, int l, int r, int x, int y) {
    if (l >= y || r <= x) {
      return Info();
    }
    if (l >= x && r <= y) {
      return info[p];
    }
    int m = (l + r) / 2;
    return range_query(2 * p, l, m, x, y) + range_query(2 * p + 1, m, r, x, y);
  }
  Info range_query(int l, int r) {
    return range_query(1, 0, n, l, r);
  }
  template <class F>
  int find_first(int p, int l, int r, int x, int y, F pred) {
    if (l >= y || r <= x || !pred(info[p])) {
      return -1;
    }
    if (r - l == 1) {
      return l;
    }
    int m = (l + r) / 2;
    int res = find_first(2 * p, l, m, x, y, pred);
    if (res == -1) {
      res = find_first(2 * p + 1, m, r, x, y, pred);
    }
    return res;
  }
  template <class F>
  int find_first(int l, int r, F pred) {
    return find_first(1, 0, n, l, r, pred);
  }
  template <class F>
  int find_last(int p, int l, int r, int x, int y, F pred) {
    if (l >= y || r <= x || !pred(info[p])) {
      return -1;
    }
    if (r - l == 1) {
      return l;
    }
    int m = (l + r) / 2;
    int res = find_last(2 * p + 1, m, r, x, y, pred);
    if (res == -1) {
      res = find_last(2 * p, l, m, x, y, pred);
    }
    return res;
  }
  template <class F>
  int find_last(int l, int r, F pred) {
    return find_last(1, 0, n, l, r, pred);
  }
};
