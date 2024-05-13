#ifndef CONTAINERS_SRC_S21_SET_H_
#define CONTAINERS_SRC_S21_SET_H_

#include <iostream>

#include "s21_btree.h"

namespace s21 {
template <typename Key, class Compare = s21::SingleComparator<Key>>
class Set : public BTree<Key, Compare> {
 public:
  using key_type = Key;
  using value_type = typename BTree<Key>::value_type;
  using reference = typename BTree<Key>::value_type&;
  using const_reference = const typename BTree<Key>::value_type&;
  using size_type = size_t;
  using iterator = typename BTree<Key>::Iterator;
  using const_iterator = typename BTree<Key>::ConstIterator;
  using tree_node = typename BTree<Key, Compare>::Node;

  Set() {
    this->end_null_ = new tree_node(0);
    this->begin_null_ = new tree_node(0, nullptr, nullptr, this->end_null_);
    this->end_null_->parent_ = this->begin_null_;
  }

  Set(std::initializer_list<value_type> const& items) : Set() {
    for (auto it = items.begin(); it != items.end(); ++it) this->insert(*it);
  }

  Set(const Set& other) : Set() {
    for (auto it = other.cbegin(); it != other.cend(); ++it) this->insert(*it);
  }

  Set(Set&& other) : Set() { this->swap(other); }

  ~Set() {
    this->clear();
    delete this->end_null_;
    delete this->begin_null_;
  }

  Set& operator=(Set&& other) {
    this->clear();
    this->swap(other);
    return *this;
  }

  Set& operator=(const Set& other) {
    this->clear();
    for (auto it = other.cbegin(); it != other.cend(); ++it) this->insert(*it);
    return *this;
  }

  std::pair<iterator, bool> insert(const value_type& value) {
    return this->InsertOrPaste(value);
  }

  void merge(Set& other) {
    auto it = other.begin();
    while (it != other.end()) {
      auto tmp = it + 1;
      if (!this->contains(*it)) {
        other.DeleteOrExtract(it, false);
        this->InsertOrPaste(*it, it.node());
      }
      it = tmp;
    }
  }

  iterator find(const Key& key) {
    auto it = this->end();
    if (this->contains(key)) {
      it = this->begin();
      while (*it != key) ++it;
    }
    return it;
  }

  bool contains(const Key& key) {
    tree_node* tmp = this->root_;
    bool flag = false;
    this->Search(key, tmp);
    if (tmp && tmp != this->end_null_ && tmp != this->begin_null_ &&
        tmp->data_ == key)
      flag = true;
    return flag;
  }
};
}  // namespace s21
#endif  // CONTAINERS_SRC_S21_SET_H_
