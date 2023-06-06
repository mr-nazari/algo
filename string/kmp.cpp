vector<int> kmp(const string& s) {
  const int n = (int) s.size();
  vector<int> pi(n);
  for (int i = 1, j = 0; i < n; ++i) {
    while (j > 0 && s[j] != s[i]) {
      j = pi[j - 1];
    }
    j += (int) (s[j] == s[i]);
    pi[i] = j;
  }
  return pi;
}
