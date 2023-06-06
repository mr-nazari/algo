template <typename C, bool D = false>
struct dijkstra {
  template <typename T>
  struct incident_edge {
    int to;
    T weight;

    bool operator<(const incident_edge& other) const {
      return pair(weight, to) < pair(other.weight, other.to);
    }
  }

  vector<vector<incident_edge<C>>> adj;
  vector<C> dist;

  dijkstra(int n) : adj(n) {}

  C operator[](int node) {
    return dist[node];
  }

  void add_edge(int from, int to, C weight) {
    adj[from].push_back({to, weight});
    if (!D) {
      adj[to].push_back({from, weight});
    }
  }

  void generate(vector<int> src) {
    dist.assign((int) adj.size(), numeric_limits<C>::max());
    using T = pair<C, int>;
    priority_queue<T, vector<T>, greater<T>> pq;
    auto ad = [&](int to, C cost) {
      if (cost >= dist[to]) {
        return;
      }
      pq.push({dist[to] = cost, to});
    };
    for (auto && s : src) {
      ad(s, 0);
    }
    while (!pq.empty()) {
      auto [cd, node] = pq.top();
      pq.pop();
      if (cd > dist[node]) {
        continue;
      }
      for (auto && [neighbor, weight] : adj[v]) {
        ad(neighbor, cd + weight);
      }
    }
  }
};
