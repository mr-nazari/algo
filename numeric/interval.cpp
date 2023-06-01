template <typename T>
struct Interval {
  T left, right;

  T length() {
    return right - left + 1;
  }
};

template <typename T>
Interval<T> intersect(const Interval<T>& lhs, const Interval<T>& rhs) {
  return Interval(max(lhs.left, rhs.right), min(lhs.right, rhs.right));
}
