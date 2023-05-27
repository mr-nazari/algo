#define popcount __builtin_popcount // pre-c++20

using i64 = long long;
using u64 = unsigned long long;
using u128 = __uint128_t;

constexpr double PI = std::numbers::pi;

template <typename T> bool ckmin(T& a, const T& b) {
   return a > b ? a = b, 1 : 0;
}

template <typename T> bool ckmax(T& a, const T& b) {
   return a < b ? a = b, 1 : 0;
}
