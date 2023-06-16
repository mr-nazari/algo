int Phi(int n) {
  int res = n;
  for (int d = 2; d * d <= n; ++d) {
    if (n % d == 0) {
      while (n % d == 0) {
        n /= d;
      }
      res -= res / d;
    }
  }
  if (n > 1) {
    res -= res / n;
  }
  return res;
}

vector<int> phi;

void PhiUpTo(int n) {
  phi.resize(n + 1);
  iota(phi.begin(), phi.end(), 0);
  for (int i = 2; i <= n; ++i) {
    if (phi[i] == i) {
      for (int j = i; j <= n; j += i) {
        phi[j] -= phi[j] / i;
      }
    }
  }
}
