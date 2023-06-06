/** Tree class with LCA capabilities and some other handy functions. */
class Tree {
 public:
  /**
   * Constructs a tree based on a given parent array.
   * @param parents
   * The parent array. The root (assumed to be node 0) is not included.
   */
  Tree(const vector<int>& parents)
    : par(parents.size() + 1),
      log2dist((int) ceil(log2(parents.size() + 1))) {
    par[0] = -1;
    for (int i = 0; i < (int) parents.size(); ++i) {
      par[i + 1] = parents[i];
    }

    pow2ends = vector<vector<int>>(par.size(), vector<int>(log2dist + 1));
    for (int n = 0; n < (int) par.size(); ++n) {
      pow2ends[n][0] = par[n];
    }
    for (int p = 1; p <= log2dist; ++p) {
      for (int n = 0; n < (int) par.size(); ++n) {
        int halfway = pow2ends[n][p - 1];
        if (halfway == -1) {
          pow2ends[n][p] = -1;
        } else {
          pow2ends[n][p] = pow2ends[halfway][p - 1];
        }
      }
    }

    vector<vector<int>> children(par.size());
    for (int n = 1; n < (int) par.size(); ++n) {
      children[par[n]].push_back(n);
    }

    depth = vector<int>(par.size());
    vector<int> frontier{0};
    while (!frontier.empty()) {
      int curr = frontier.back();
      frontier.pop_back();
      for (int n : children[curr]) {
        depth[n] = depth[curr] + 1;
        frontier.push_back(n);
      }
    }
  }

  /** @return the kth parent of node n (or -1 if it doesn't exist). */
  int kth_parent(int n, int k) {
    if (k > (int) par.size()) {
      return -1;
    }
    int at = n;
    for (int pow = 0; pow <= log2dist; ++pow) {
      if ((k & (1 << pow)) != 0) {
        at = pow2ends[at][pow];
        if (at == -1) {
          break;
        }
      }
    }
    return at;
  }

  /** @return the lowest common ancestor of n1 and n2. */
  int LCA(int n1, int n2) {
    if (depth[n1] < depth[n2]) {
      return LCA(n2, n1);
    }
    n1 = kth_parent(n1, depth[n1] - depth[n2]);
    if (n1 == n2) {
      return n1;
    }
    for (int i = log2dist; i >= 0; --i) {
      if (pow2ends[n1][i] != pow2ends[n2][i]) {
        n1 = pow2ends[n1][i];
        n2 = pow2ends[n2][i];
      }
    }
    return n1 == 0 ? 0 : pow2ends[n1][0];
  }

  /** @return the distance between n1 and n2. */
  int dist(int n1, int n2) {
    return depth[n1] + depth[n2] - 2 * depth[LCA(n1, n2)];
  }

 private:
  vector<int> par;
  vector<vector<int>> pow2ends;
  vector<int> depth;
  const int log2dist;
};
