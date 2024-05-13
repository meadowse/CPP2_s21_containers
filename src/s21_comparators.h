#ifndef CONTAINERS_SRC_S21_COMPARATORS_H_
#define CONTAINERS_SRC_S21_COMPARATORS_H_

#include <utility>

namespace s21 {
template <class A>
struct SingleComparator {
  using type = A;
  bool LessThan(const type &a, const type &b) const { return a < b; }
  bool GreaterThan(const type &a, const type &b) const { return a > b; }
  bool LessOrEquals(const type &a, const type &b) const { return a <= b; }
  bool GreaterOrEquals(const type &a, const type &b) const { return a >= b; }
  bool Equals(const type &a, const type &b) const { return a == b; }
  bool NotEquals(const type &a, const type &b) const { return a != b; }
};

template <class A, class B>
struct PairComparator {
  using pair = std::pair<A, B>;
  bool LessThan(const pair &a, const pair &b) const {
    return a.first < b.first;
  }
  bool GreaterThan(const pair &a, const pair &b) const {
    return a.first > b.first;
  }
  bool LessOrEquals(const pair &a, const pair &b) const {
    return a.first <= b.first;
  }
  bool GreaterOrEquals(const pair &a, const pair &b) const {
    return a.first >= b.first;
  }
  bool Equals(const pair &a, const pair &b) const { return a.first == b.first; }
  bool NotEquals(const pair &a, const pair &b) const {
    return a.first != b.first;
  }
};

}  // namespace s21

#endif  // CONTAINERS_SRC_S21_COMPARATORS_H_
