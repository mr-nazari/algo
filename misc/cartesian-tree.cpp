template <typename T, class C = less<int>>
pair<vector<array<int, 2>>, int> cartesian_tree(const vector<T>& a) {
   const int n = (int) a.size();
   vector<array<int, 2>> to(n, { -1, -1 });
   vector<int> stk;
   constexpr C cmp;
   for (int i = 0; i < n; ++i) {
      int last = -1;
      while (!stk.empty() && cmp(a[i], a[stk.back()])) {
         last = stk.back();
         stk.pop_back();
      }
      to[i][0] = last;
      if (!stk.empty()) {
         to[stk.back()][1] = i;
      }
      stk.emplace_back(i);
   }
   return pair(move(to), stk.empty() ? -1 : stk[0]);
}
