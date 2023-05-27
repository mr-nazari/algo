bool is_prime(int n) {
   if (n <= 1) {
      return false;
   }
   if (n <= 3) {
      return true;
   }
   if (n % 2 == 0 || n % 3 == 0) {
      return false;
   }
   for (int d = 5; d * d <= n; d += 6) {
      if (n % d == 0 || n % (d + 2) == 0) {
         return false;
      }
   }
   return true;
}

i64 modpow(i64 base, i64 exp, i64 mod) {
  i64 res = 1;
  base %= mod;
  while (exp > 0) {
    if (exp & 1) {
      res *= base;
      res %= mod;
    }
    base *= base;
    base %= mod;
    exp >>= 1;
  }
  return res;
}
bool is_prime(i64 n) {
  if (n < 2) {
    return false;
  }

  int s = 0;
  i64 d = n - 1;
  while ((d & 1) == 0) {
    d >>= 1;
    ++s;
  }

  auto check = [&](i64 a) -> bool {
    i64 x = modpow(a, d, n);
    if (x == 1 || x == n - 1) {
      return false;
    }
    for (int r = 1; r < s; ++r) {
      x = (u128) x * x % n;
      if (x == n - 1) {
        return false;
      }
    }
    return true;
  };

  const vector<int> A{2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37};
  for (int a : A) {
    if (n == a) {
      return true;
    }
    if (check(a)) {
      return false;
    }
  }
  return true;
};
