#define popcount __builtin_popcount  // pre-c++20

using i64 = long long;
using u64 = unsigned long long;
using u128 = __uint128_t;
using ldb = long double;

constexpr double PI = std::numbers::pi;

template <typename T> bool ckmin(T& a, const T& b) {
   return a > b ? a = b, 1 : 0;
}

template <typename T> bool ckmax(T& a, const T& b) {
   return a < b ? a = b, 1 : 0;
}

#include <bits/extc++.h>

struct splitmix64_hash {
  static uint64_t splitmix64(uint64_t x) {
    // http://xorshift.di.unimi.it/splitmix64.c
    x += 0x9e3779b97f4a7c15;
    x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
    x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
    return x ^ (x >> 31);
  }

  size_t operator()(uint64_t x) const {
    static const uint64_t kFixedRandom =
      std::chrono::steady_clock::now().time_since_epoch().count();
    return splitmix64(x + kFixedRandom);
  }
};

template <typename K, typename V, typename Hash = splitmix64_hash>
using hash_map = __gnu_pbds::gp_hash_table<K, V, Hash>;

template <typename K, typename Hash = splitmix64_hash>
using hash_set = hash_map<K, __gnu_pbds::null_type, Hash>;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
mt19937_64 rng((unsigned int) chrono::steady_clock::now().time_since_epoch().count());

int rnd(int l, int r) {
  return uniform_int_distribution<int>(l, r)(rng);
}

double clock_begin = clock();
auto cur_time = [&]() -> double {
  return (clock() - clock_begin) / CLOCKS_PER_SEC;
};
