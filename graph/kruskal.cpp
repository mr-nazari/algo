template <typename T> T kruskal(vector<Edge<T>> ed) {
   const int n = (int) ed.size();
   sort(ed.begin(), ed.end());
   T res = 0;
   DSU d(n);
   for (auto& [u, v, weight] : ed) {
      if (d.unite(u, v)) {
         res += weight;
      }
   }
   return res;
}
