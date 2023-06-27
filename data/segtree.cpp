template <class Info>
class SegmentTree {
 public:
  std::vector<Info> info;
  int n;

  SegmentTree() : n(0) {}
  SegmentTree(int n_, Info v_ = Info()) {
    init(n_, v_);
  }
  SegmentTree(std::vector<Info> init_) {
    init(init_);
  }

  void init(int n_, Info v_ = Info()) {
    init(std::vector(n_, v_));
  }
  void init(std::vector<Info> init_) {
    n = (int) init_.size();
    info.assign(4 << std::__lg(n), Info());
    std::function<void(int, int, int)> build;
    build = [&](int p, int l, int r) {
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
  void modify(int x, const Info& v) {
    modify(1, 0, n, x, v);
  }

  Info RangeQuery(int p, int l, int r, int lx, int rx) {
    if (l >= rx || r <= lx) {
      return Info();
    }
    if (l >= lx && r <= rx) {
      return info[p];
    }
    int m = (l + r) / 2;
    return RangeQuery(2 * p, l, m, lx, rx) +
           RangeQuery(2 * p + 1, m, r, lx, rx);
  }
  Info RangeQuery(int lx, int rx) {
    return RangeQuery(1, 0, n, lx, rx);
  }
  template <class F = std::function<bool(const Info&)>>
  int FindFirst(int p, int l, int r, int lx, int rx,
                F pred) {
    if (l >= rx || r <= lx || !pred(info[p])) {
      return -1;
    }
    if (r - l == 1) {
      return l;
    }
    int m = (l + r) / 2;
    int res = FindFirst(2 * p, l, m, lx, rx, pred);
    if (res == -1) {
      res = FindFirst(2 * p + 1, m, r, lx, rx, pred);
    }
    return res;
  }
  template <class F = std::function<bool(const Info&)>>
  int FindFirst(int lx, int rx, F pred) {
    return FindFirst(1, 0, n, lx, rx, pred);
  }
  template <class F = std::function<bool(const Info&)>>
  int FindLast(int p, int l, int r, int lx, int rx,
               F pred) {
    if (l >= rx || r <= lx || !pred(info[p])) {
      return -1;
    }
    if (r - l == 1) {
      return l;
    }
    int m = (l + r) / 2;
    int res = FindLast(2 * p + 1, m, r, lx, rx, pred);
    if (res == -1) {
      res = FindLast(2 * p, l, m, lx, rx, pred);
    }
    return res;
  }
  template <class F = std::function<bool(const Info&)>>
  int FindLast(int lx, int rx, F pred) {
    return FindLast(1, 0, n, lx, rx, pred);
  }
};

struct Info {
  int sum = 0;
};

Info operator+(const Info& a, const Info& b) {
  return {a.sum + b.sum};
}

template <typename U>
U& operator<<(U& stream, const Info& v) {
  return stream << v.sum;
}

template <typename U>
U& operator>>(U& stream, Info& v) {
  return stream >> v.sum;
}
