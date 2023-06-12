template <typename T>
T SolveLinearEquation(T a, T b) {
  if (a == 0) {
    throw domain_error("This isn't a linear equation.");
  }
  return -b / a;
}
 
template <typename T>
pair<T, T> SolveQuadraticEquation(T a, T b, T c) {
  if (a == 0) {
    throw domain_error("This isn't a quadratic equation.");
  }
  T delta = b * b - 4 * a * c;
  if (delta < 0) {
    throw domain_error("Delta is negetive.");
  }
  return pair((-b - sqrt(delta)) / (2 * a),
              (-b + sqrt(delta)) / (2 * a));
}
