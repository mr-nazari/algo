template <typename T> T kruskal(vector<edge<T>> ed) {
  const int n = (int) ed.size();
  sort(ed.begin(), ed.end());
  T res = 0;
  dsu d(n);
  for (auto& [u, v, weight] : ed) {
    if (d.unite(u, v)) {
      res += weight;
    }
  }
  return res;
}
