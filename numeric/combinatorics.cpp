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

Mint Catalan(int x, int y) {
  // NOTE: Formal catalan number C(n)
  // is equal to Catalan(2 * n, n).
  if (x > y) {
    return Mint(0);
  }
  return C(x + y, y) - C(x + y, y + 1);
};

Mint LucasC(int n, int k) {
  if (k < 0 || k > n) {
    return 0;
  }
  vector<int> narr;
  while (n > 0) {
    narr.push_back(n % md);
    n /= md;
  }
  vector<int> karr;
  while (k > 0) {
    karr.push_back(k % md);
    k /= md;
  }
  auto r = max(narr.size(), karr.size());
  narr.resize(r);
  karr.resize(r);
  Mint res = 1;
  for (int i = 0; i < r; ++i) {
    res *= C(narr[i], karr[i]);
  }
  return res;
}

namespace linear_equation {

Mint Normal(int n, int s) {
  return C(n + s - 1, s);
}

Mint Bounded(int n, int s,
             int max_lim, int min_lim = 0) {
  s -= n * min_lim;
  if (n < 0 || s < 0) {
    return Mint(0);
  }
  if (n == 0) {
    return Mint(s == 0);
  }
  Mint res = 0;
  for (int i = 0; i <= n; ++i) {
    res += (i & 1 ? -1 : 1) * C(n, i) * Normal(n, s - i * max_lim);
  }
  return res;
}

map<int, Mint> _with_gcd1;

Mint WithGcd1(int r) {
  if (_with_gcd1.count(r)) {
    return _with_gcd1[r];
  }
  Mint res = Mint(2) ^ (r - 1);
  for (int d = 1; d * d <= r; ++d) {
    if (r % d == 0) {
      if (d > 1) {
        res -= WithGcd1(r / d);
      }
      if (r / d > 1 && d * d != r) {
        res -= WithGcd1(d);
      }
    }
  }
  return _with_gcd1[r] = res;
}

}  // linear_equation
