struct HashString {
  i64 M = (i64) 1e9 + 7;
  i64 B = 9973;

  vector<i64> pow{1};
  vector<i64> p_hash;
  int len;

  HashString() {}

  HashString(const string& s, i64 mod = 0) : p_hash(s.size() + 1), len(s.size()) {
    if (mod) {
      M = mod;
    }
    while (pow.size() < s.size()) {
      pow.push_back((pow.back() * B) % M);
    }
    p_hash[0] = 0;
    for (int i = 0; i < (int) s.size(); ++i) {
      p_hash[i + 1] = ((p_hash[i] * B) % M + s[i]) % M;
    }
  }

  i64 get(int start, int end) {
    i64 raw_val = (p_hash[end + 1] - (p_hash[start] * pow[end - start + 1]));
    return (raw_val % M + M) % M;
  }
};
