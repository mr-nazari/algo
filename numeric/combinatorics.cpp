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

Mint liep(int n, int s) {
  // number of solutions to linear equation
  // with unit coefficients $x_1 + x_2 + \dots + x_n = s$
  return C(n + s - 1, s);
}

Mint biep(int n, int s, int b, int r = 0) {
  // number of solutions to bounded linear equation
  // with fixed limit (unit coefficients)
  // $x_1 + x_2 + \dots + x_n = s \forall 1 \le i\ len : r \le x_i \le b$
  s -= n * r;
  if (n < 0 || s < 0) {
    return Mint(0);
  }
  if (n == 0) {
    return Mint(s == 0);
  }
  Mint res = 0;
  for (int i = 0; i <= n; ++i) {
    res += (i & 1 ? -1 : 1) * C(n, i) * C((s - i * b) + (n - 1), n - 1);
  }
  return res;
}
