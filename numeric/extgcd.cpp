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
