vector<int> minp = {0, 1};
vector<int> primes;
int precalculated = 1;

void RunLinearSieve(int n) {
  n = max(n, 1);
  minp.assign(n + 1, 0);
  primes.clear();
  for (int i = 2; i <= n; ++i) {
    if (minp[i] == 0) {
      minp[i] = i;
      primes.push_back(i);
    }
    for (int p : primes) {
      if (p > minp[i] || i * p > n) {
        break;
      }
      minp[i * p] = p;
    }
  }
  precalculated = n;
}

void RunSlowSieve(int n) {
  n = max(n, 1);
  minp.assign(n + 1, 0);
  for (int i = 2; i * i <= n; ++i) {
    if (minp[i] == 0) {
      for (int j = i * i; j <= n; j += i) {
        if (minp[j] == 0) {
          minp[j] = i;
        }
      }
    }
  }
  primes.clear();
  for (int i = 2; i <= n; ++i) {
    if (minp[i] == 0) {
      minp[i] = i;
      primes.push_back(i);
    }
  }
  precalculated = n;
}

void RunSieve(int n) {
  RunLinearSieve(n);
}
