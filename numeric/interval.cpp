template <typename T>
struct Interval {
  T left, right;

  constexpr Interval() {}
  Interval(const T& _left, const T& _right) : left(_left), right(_right) {}

  bool contains(const T& point) const {
    return is_valid() && left <= point && point <= right;
  }
  bool contains(const Interval& other) const {
    return is_valid() && other.is_valid() && left <= other.left && other.right <= right;
  }

  T length() const {
    return max((T) 0, right - left + 1);
  }

  bool is_valid() const {
    return right >= left;
  }
};

template <typename T>
bool operator==(const Interval<T>& lhs, const Interval<T>& rhs) {
  return pair(lhs.left, lhs.right) == pair(rhs.left, rhs.right);
}
template <typename T>
bool operator!=(const Interval<T>& lhs, const Interval<T>& rhs) {
  return !(lhs == rhs);
}
template <typename T>
bool operator<(const Interval<T>& lhs, const Interval<T>& rhs) {
  return pair(lhs.left, lhs.right) < pair(rhs.left, rhs.right);
}

template <typename T>
Interval<T> intersect(const Interval<T>& lhs, const Interval<T>& rhs) {
  return Interval(max(lhs.left, rhs.left), min(lhs.right, rhs.right));
}

using Itv = Interval<int>;
