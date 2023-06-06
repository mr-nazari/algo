template <typename T>
T extgcd(T a, T b, T& x, T& y) {
  if (a == 0) {
    x = 0;
    y = 1;
    return b;
  }
  T p = b / a;
  T g = extgcd(b - p * a, a, y, x);
  x -= p * y;
  return g;
}

template <typename T>
bool diophantine(T a, T b, T c, T& x, T& y, T& g) {
  g = extgcd(abs(a), abs(b), x, y);
  if (g == 0) {
    // NOTE: Now x = 0 and y = 1.
    return c == 0;
  }
  if (c % g != 0) {
    return false;
  }
  x *= c / g;
  y *= c / g;
  if (a < 0) {
    x *= -1;
  }
  if (b < 0) {
    y *= -1;
  }
  return true;
}
