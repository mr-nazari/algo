template <class Info, class Tag>
class LazySegmentTree {
 public:
  std::vector<Info> info;
  std::vector<Tag> tag;
  int n;

  LazySegmentTree() : n(0) {}
  LazySegmentTree(int n_, Info v_ = Info()) {
    init(n_, v_);
  }
  LazySegmentTree(std::vector<Info> init_) {
    init(init_);
  }

  void init(int n_, Info v_ = Info()) {
    init(std::vector(n_, v_));
  }
  void init(std::vector<Info> init_) {
    n = (int) init_.size();
    info.assign(4 << std::__lg(n), Info());
    tag.assign(4 << std::__lg(n), Tag());
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
  void apply(int p, const Tag& v) {
    info[p].apply(v);
    tag[p].apply(v);
  }
  void push(int p) {
    apply(2 * p, tag[p]);
    apply(2 * p + 1, tag[p]);
    tag[p] = Tag();
  }
  void modify(int p, int l, int r, int x, const Info& v) {
    if (r - l == 1) {
      info[p] = v;
      return;
    }
    int m = (l + r) / 2;
    push(p);
    if (x < m) {
      modify(2 * p, l, m, x, v);
    } else {
      modify(2 * p + 1, m, r, x, v);
    }
    pull(p);
  }
  void modify(int p, const Info& v) {
    modify(1, 0, n, p, v);
  }

  Info RangeQuery(int p, int l, int r, int lx, int rx) {
    if (l >= rx || r <= lx) {
      return Info();
    }
    if (l >= lx && r <= rx) {
      return info[p];
    }
    int m = (l + r) / 2;
    push(p);
    return RangeQuery(2 * p, l, m, lx, rx) +
           RangeQuery(2 * p + 1, m, r, lx, rx);
  }
  Info RangeQuery(int lx, int rx) {
    return RangeQuery(1, 0, n, lx, rx);
  }
  void RangeApply(int p, int l, int r, int lx, int rx,
                  const Tag& v) {
    if (l >= rx || r <= lx) {
      return;
    }
    if (l >= lx && r <= rx) {
      apply(p, v);
      return;
    }
    int m = (l + r) / 2;
    push(p);
    RangeQuery(2 * p, l, m, lx, rx, v);
    RangeQuery(2 * p + 1, m, r, lx, rx, v);
    pull(p);
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
    push(p);
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
    push(p);
    int res = FindLast(2 * p + 1, m, r, lx, rx, pred);
    if (res == -1) {
      res = FindFirst(2 * p, l, m, lx, rx, pred);
    }
    return res;
  }
  template <class F = std::function<bool(const Info&)>>
  int FindLast(int lx, int rx, F pred) {
    return FindLast(1, 0, n, lx, rx, pred);
  }
};

struct Tag {  // For range apply
              // e.x Add v to every element in [l, r)
  i64 add = 0;

  void apply(Tag t) {
    add += t.add;
  }
};

struct Info {  // For range query
               // e.x Get minimum of elements in [l, r)
  i64 mn = 1E18;

  void apply(Tag t) {
    mn += t.add;
  }
};

Info operator+(Info a, Info b) {
  return {std::min(a.mn, b.mn)};
}
