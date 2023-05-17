template <typename T, int MAX_LOG>
struct BinaryTrie {
   struct Node {
      std::array<int, 2> nxt;
      int count;
      Node() : nxt{ -1, -1 }, count(0) { }
   };

   inline static struct : vector<Node> {
      vector<int> free_id;

      int create() {
         if (free_id.empty()) {
            int res = vector<Node>::size();
            vector<Node>::emplace_back();
            return res;
         }
         else {
            int res = free_id.back();
            free_id.pop_back();
            (*this)[res] = {};
            return res;
         }
      }

      void release(int i) {
         free_id.emplace_back(i);
      }
   } nodes;

   int root;

   BinaryTrie() : root(-1) { }

   BinaryTrie(BinaryTrie&& other) : root(other.root) {
      other.root = -1;
   }

   ~BinaryTrie() {
      if (root == -1) {
         return;
      }
      static vector<int> todo;
      todo.emplace_back(root);
      do {
         int i = todo.back(); todo.pop_back();
         for (int j : nodes[i].nxt) {
            if (j != -1) {
               todo.emplace_back(j);
            }
         }
         nodes.release(i);
      } while (!todo.empty());
   }

   BinaryTrie& operator=(BinaryTrie&& other) {
      swap(root, other.root);
      return *this;
   }

   void insert(const T& x) {
      if (root == -1) {
         root = nodes.create();
      }
      int p = root;
      ++nodes[p].count;
      for (int k = MAX_LOG - 1; k >= 0; --k) {
         bool bit = x >> k & 1;
         int nxt = nodes[p].nxt[bit];
         if (nxt == -1) {
            nxt = nodes[p].nxt[bit] = nodes.create();
         }
         ++nodes[p = nxt].count;
      }
   }

   int erase(const T& x, int delta = -1) {
      assert(delta >= -1);
      if (root == -1) {
         return 0;
      }
      vector<int> idx(MAX_LOG + 1);
      int p = root;
      idx[MAX_LOG] = p;
      for (int k = MAX_LOG - 1; k >= 0; --k) {
         p = nodes[p].nxt[x >> k & 1];
         if (p == -1) {
            return 0;
         }
         idx[k] = p;
      }
      if (0 <= delta && delta < nodes[p].count) {
         nodes[p].count -= delta;
         return delta;
      }
      delta = nodes[p].count;
      int k = 0;
      while (k <= MAX_LOG && nodes[idx[k]].count == delta) {
         nodes.release(idx[k]);
         ++k;
      }
      if (k == MAX_LOG + 1) {
         root = -1;
      }
      else {
         nodes[idx[k]].nxt[x >> (k - 1) & 1] = -1;
         while (k <= MAX_LOG) {
            nodes[idx[k]].count -= delta;
            ++k;
         }
      }
      return delta;
   }

   T xor_min(const T& xor_val) {
      assert(root != -1);
      int p = root;
      T res = 0;
      for (int k = MAX_LOG - 1; k >= 0; --k) {
         const auto& nxt = nodes[p].nxt;
         bool bit = xor_val >> k & 1;
         if (nxt[bit] == -1) {
            bit = !bit;
         }
         p = nxt[bit];
         res = res << 1 | bit;
      }
      return xor_val ^ res;
   }

   T xor_max(const T& xor_val) {
      assert(root != -1);
      int p = root;
      T res = 0;
      for (int k = MAX_LOG - 1; k >= 0; --k) {
         const auto& nxt = nodes[p].nxt;
         bool bit = (xor_val >> k & 1) ^ 1;
         if (nxt[bit] == -1) {
            bit = !bit;
         }
         p = nxt[bit];
         res = res << 1 | bit;
      }
      return xor_val ^ res;
   }

   int count(const T& x) {
      if (root == -1) return 0;
      int p = root;
      for (int k = MAX_LOG - 1; k >= 0; --k) {
         bool bit = x >> k & 1;
         p = nodes[p].nxt[bit];
         if (p == -1) {
            return 0;
         }
      }
      return nodes[p].count;
   }

   bool empty() {
      return root == -1;
   }

   int size() {
      return root == -1 ? 0 : nodes[root].count;
   }

   void merge(BinaryTrie& bt) {
      static vector<pair<int, int>> todo;
      if (bt.empty()) {
         return;
      }
      if (empty()) {
         *this = move(bt);
         return;
      }
      todo.emplace_back(root, bt.root);
      do {
         auto [p, q] = todo.back(); todo.pop_back();
         nodes[p].count += nodes[q].count;
         for (int i = 0; i < 2; i++) {
            if (nodes[p].nxt[i] == -1) {
               nodes[p].nxt[i] = nodes[q].nxt[i];
               nodes[q].nxt[i] = -1;
            }
            else if (nodes[q].nxt[i] != -1) {
               todo.emplace_back(nodes[p].nxt[i], nodes[q].nxt[i]);
            }
         }
      } while (!todo.empty());
   }

   vector<T> all() {
      if (empty()) {
         return vector<int>{};
      }
      vector<T> res;
      res.reserve(size());
      auto dfs = [&](auto && self, int p, int k, T v) -> void {
         if (k == 0) {
            for (int i = nodes[p].count; i > 0; --i) {
               res.emplace_back(v);
            }
         }
         else {
            for (int i : {0, 1}) {
               int nxt = nodes[p].nxt[i];
               if (nxt != -1) {
                  self(self, nxt, k - 1, v << 1 | i);
               }
            }
         }
      };
      dfs(dfs, root, MAX_LOG, 0);
      return res;
   }
};
