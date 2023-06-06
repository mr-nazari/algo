vector<Mint> fact(1, 1);
vector<Mint> inv_fact(1, 1);

void init_fact(int n) {
  while ((int) fact.size() < n + 1) {
    fact.push_back(fact.back() * (int) fact.size());
    inv_fact.push_back(1 / fact.back());
  }
}

Mint C(int n, int k) {
  // Binomial Coefficient
  if (k < 0 || k > n) {
    return 0;
  }
  init_fact(n);
  return fact[n] * inv_fact[k] * inv_fact[n - k];
}

Mint P(int n, int k) {
  // k-Permutaion
  return C(n, k) * fact[k];
}

Mint Q(int n, int k) {
  // k-Circular Permutation
  return P(n, k) / k;
}

Mint S(int n, int k) {
  // Stirling numbers of the second kind
  if (k < 0 || k > n) {
    return 0;
  }
  Mint res = 0;
  init_fact(k);
  for (int i = 0; i <= k; ++i) {
    res += (
      ((k - i) & 1 ? -1 : 1) * power(Mint(i), n)
      * inv_fact[k - i] * inv_fact[i]
    );
  }
  return res;
}

Mint catalan(int x, int y) {
  // NOTE: Formal catalan number C(n)
  // is equal to catalan(2 * n, n).
  if (x > y) {
    return Mint(0);
  }
  return C(x + y, y) - C(x + y, y + 1);
};
