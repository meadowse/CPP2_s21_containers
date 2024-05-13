#ifndef CONTAINERS_SRC_S21_BTREE_H_
#define CONTAINERS_SRC_S21_BTREE_H_

#include <iostream>
#include <limits>
#include <utility>

#include "s21_comparators.h"

template <class Key, class Compare = s21::SingleComparator<Key>>
class BTree {
 public:
  using key_type = Key;
  using value_type = Key;
  using key_compare = Compare;
  using reference = key_type &;
  using const_reference = const key_type &;
  using size_type = size_t;

  struct Node {
    Node(key_type key, Node *right = nullptr, Node *left = nullptr,
         Node *parent = nullptr) {
      parent_ = parent;
      right_ = right;
      left_ = left;
      data_ = key;
    };
    ~Node(){};

    Node *parent_;
    Node *left_;
    Node *right_;
    key_type data_;
  };

  class Iterator {
   public:
    // Constructors

    Iterator() { address_ = nullptr; }
    Iterator(Node &node) { address_ = &node; }
    Iterator(Node *node_ptr) { address_ = node_ptr; }
    Iterator(const Iterator &other) { address_ = other.address_; }
    Iterator(Iterator &&other) {
      address_ = other.address_;
      other.address_ = nullptr;
    }
    ~Iterator() {}

    Iterator &operator=(const Iterator &other) {
      this->address_ = other.address_;
      return *this;
    }

    Node *node() const { return address_; }

    value_type &operator*() const { return address_->data_; }

    Iterator &operator++() {
      if (this->address_->right_) {
        this->address_ = this->address_->right_;
        while (this->address_->left_) this->address_ = this->address_->left_;
      } else if (this->address_->parent_->left_ == this->address_) {
        this->address_ = this->address_->parent_;
      } else {
        key_type tmp = this->address_->data_;
        do {
          this->address_ = this->address_->parent_;
        } while (comparator_.GreaterThan(tmp, this->address_->data_));
      }
      return *this;
    }

    Iterator operator++(int) {
      Iterator tmp = *this;
      ++*this;
      return tmp;
    }

    Iterator &operator--() {
      if (this->address_->left_) {
        this->address_ = this->address_->left_;
        while (this->address_->right_) this->address_ = this->address_->right_;
      } else if (this->address_->parent_->right_ == this->address_) {
        this->address_ = this->address_->parent_;
      } else {
        key_type tmp = this->address_->data_;
        do {
          this->address_ = this->address_->parent_;
        } while (comparator_.LessThan(tmp, this->address_->data_));
      }
      return *this;
    }

    Iterator operator--(int) {
      Iterator tmp = *this;
      --*this;
      return tmp;
    }

    Iterator operator+(int n) {
      Iterator tmp = *this;
      for (int i = 0; i < n; ++i) ++tmp;
      return tmp;
    }

    Iterator operator-(int n) {
      Iterator tmp = *this;
      for (int i = 0; i < n; ++i) --tmp;
      return tmp;
    }

    Iterator operator+=(int n) {
      for (int i = 0; i < n; ++i) ++*this;
      return *this;
    }

    Iterator operator-=(int n) {
      for (int i = 0; i < n; ++i) --*this;
      return *this;
    }

    bool operator==(const Iterator &other) {
      return address_ == other.address_;
    }

    bool operator!=(const Iterator &other) {
      return address_ != other.address_;
    }

   private:
    key_compare comparator_;
    Node *address_;
  };

  class ConstIterator {
   public:
    ConstIterator() { address_ = nullptr; }
    ConstIterator(Node &node) { address_ = &node; }
    ConstIterator(Node *node_ptr) { address_ = node_ptr; }
    ConstIterator(const ConstIterator &other) { address_ = other.address_; }
    ConstIterator(ConstIterator &&other) {
      address_ = other.address_;
      other.address_ = nullptr;
    }
    ~ConstIterator() {}

    ConstIterator &operator=(const ConstIterator &other) {
      this->address_ = other.address_;
      return *this;
    }

    Node *node() const { return address_; }

    const_reference operator*() const { return address_->data_; }

    ConstIterator &operator++() {
      if (this->address_->right_) {
        this->address_ = this->address_->right_;
        while (this->address_->left_) this->address_ = this->address_->left_;
      } else if (this->address_->parent_->left_ == this->address_) {
        this->address_ = this->address_->parent_;
      } else {
        key_type tmp = this->address_->data_;
        do {
          this->address_ = this->address_->parent_;
        } while (comparator_.GreaterThan(tmp, this->address_->data_));
      }
      return *this;
    }

    ConstIterator operator++(int) {
      ConstIterator tmp = *this;
      ++*this;
      return tmp;
    }

    ConstIterator &operator--() {
      if (this->address_->left_) {
        this->address_ = this->address_->left_;
        while (this->address_->right_) this->address_ = this->address_->right_;
      } else if (this->address_->parent_->right_ == this->address_) {
        this->address_ = this->address_->parent_;
      } else {
        key_type tmp = this->address_->data_;
        do {
          this->address_ = this->address_->parent_;
        } while (comparator_.LessThan(tmp, this->address_->data_));
      }
      return *this;
    }

    ConstIterator operator--(int) {
      ConstIterator tmp = *this;
      --*this;
      return tmp;
    }

    ConstIterator operator+(int n) {
      ConstIterator tmp = *this;
      for (int i = 0; i < n; ++i) ++tmp;
      return tmp;
    }

    ConstIterator operator-(int n) {
      ConstIterator tmp = *this;
      for (int i = 0; i < n; ++i) --tmp;
      return tmp;
    }

    ConstIterator operator+=(int n) {
      for (int i = 0; i < n; ++i) ++*this;
      return *this;
    }

    ConstIterator operator-=(int n) {
      for (int i = 0; i < n; ++i) --*this;
      return *this;
    }

    bool operator==(const ConstIterator &other) {
      return address_ == other.address_;
    };

    bool operator!=(const ConstIterator &other) {
      return address_ != other.address_;
    };

   private:
    key_compare comparator_;
    Node *address_;
  };

  using iterator = Iterator;
  using const_iterator = ConstIterator;

  iterator begin() {
    iterator tmp(begin_null_);
    if (size_) ++tmp;
    return tmp;
  }

  iterator end() { return iterator(end_null_); }

  const_iterator cbegin() const {
    const_iterator tmp(begin_null_);
    if (size_) ++tmp;
    return tmp;
  }

  const_iterator cend() const { return const_iterator(end_null_); }

  bool empty() { return !(bool)size_; }

  size_type size() { return size_; }

  size_type max_size() const {
    return std::numeric_limits<size_type>::max() / (2 * sizeof(Node));
  }

  void clear() {
    if (size_) {
      iterator it = begin();
      while (it != end()) {
        iterator tmp = it + 1;
        erase(it);
        it = tmp;
      }
    }
  }

  void erase(iterator pos) { DeleteOrExtract(pos, true); }

  void swap(BTree &other) {
    Node *tmp_root = this->root_;
    Node *tmp_end_null = this->end_null_;
    Node *tmp_begin_null = this->begin_null_;
    size_type tmp = this->size_;
    this->root_ = other.root_;
    this->end_null_ = other.end_null_;
    this->begin_null_ = other.begin_null_;
    this->size_ = other.size_;
    other.root_ = tmp_root;
    other.end_null_ = tmp_end_null;
    other.begin_null_ = tmp_begin_null;
    other.size_ = tmp;
  }

 protected:
  size_type size_ = 0;
  Node *root_ = nullptr;
  Node *begin_null_;
  Node *end_null_;
  key_compare comparator_;

  void ChangeChildOfParent(Node *parent, Node *old_child, Node *new_child) {
    parent->left_ == old_child ? parent->left_ = new_child
                               : parent->right_ = new_child;
  }

  void DeleteOrExtract(iterator pos, bool del) {
    if (pos.node() && pos.node() != end_null_ && pos.node() != begin_null_) {
      key_type tmp = *pos;
      Node *node = root_;
      Node *parent = Search(tmp, node);

      if (IsLeaf(node)) {
        DeleteLeaf(node);
      } else if (Node *child = HasOneChild(node)) {
        DeleteIfOneChild(node, child);
      } else {
        if (node->left_ == begin_null_ && node->right_ == end_null_) {
          DeleteRoot();
        } else if (node->left_ != begin_null_ && node->right_ != end_null_) {
          DeleteRegular(node, parent);
        } else {
          if (node->left_ == begin_null_) {
            DeleteWithNullInLeft(node, parent);
          } else {
            DeleteWithNullInRight(node, parent);
          }
        }
      }
      if (del) delete node;
      --size_;
    }
  }

  std::pair<iterator, bool> InsertOrPaste(const key_type &key,
                                          Node *node = nullptr) {
    Node *insertible = !node ? new Node(key) : node;
    std::pair<iterator, bool> pair(iterator(insertible), true);

    if (!root_) {
      root_ = insertible;
      insertible->right_ = end_null_;
      insertible->left_ = begin_null_;
      end_null_->parent_ = insertible;
      begin_null_->parent_ = insertible;
      end_null_->right_ = end_null_;
      begin_null_->left_ = begin_null_;
    } else {
      Node *tmp = root_;
      Node *parent = Search(key, tmp);
      if (tmp == end_null_) {
        parent->right_ = insertible;
        insertible->parent_ = parent;
        insertible->left_ = nullptr;
        insertible->right_ = end_null_;
        end_null_->parent_ = insertible;
      } else if (tmp == begin_null_) {
        parent->left_ = insertible;
        insertible->parent_ = parent;
        insertible->right_ = nullptr;
        insertible->left_ = begin_null_;
        begin_null_->parent_ = insertible;
      } else if (!tmp) {
        comparator_.LessThan(key, parent->data_) ? parent->left_ = insertible
                                                 : parent->right_ = insertible;
        insertible->parent_ = parent;
        insertible->left_ = insertible->right_ = nullptr;
      } else {
        pair.first = iterator(tmp);
        pair.second = false;
        if (!node) delete insertible;
      }
    }
    if (pair.second) ++size_;
    return pair;
  }

  void DeleteLeaf(Node *node) {
    ChangeChildOfParent(node->parent_, node, nullptr);
  }

  void DeleteIfOneChild(Node *node, Node *child) {
    ChangeChildOfParent(node->parent_, node, child);
    child->parent_ = node->parent_;
  }

  void DeleteRoot() {
    root_ = nullptr;
    begin_null_->parent_ = end_null_;
    end_null_->parent_ = begin_null_;
  }

  void DeleteRegular(Node *node, Node *parent) {
    Node *max_left = GetMax(node->left_);
    Node *parent_moved = max_left->parent_;
    if (parent_moved == node) {
      max_left->right_ = node->right_;
      node->right_->parent_ = max_left;
      max_left->parent_ = parent;
      if (parent) {
        ChangeChildOfParent(parent, node, max_left);
      } else {
        root_ = max_left;
      }
    } else {
      parent_moved->right_ = max_left->left_;
      if (max_left->left_) parent_moved->right_->parent_ = parent_moved;
      max_left->left_ = node->left_;
      node->left_->parent_ = max_left;
      max_left->parent_ = parent;
      if (parent) {
        ChangeChildOfParent(parent, node, max_left);
      } else {
        root_ = max_left;
      }
      max_left->right_ = node->right_;
      node->right_->parent_ = max_left;
    }
  }

  void DeleteWithNullInLeft(Node *node, Node *parent) {
    if (!node->right_->left_) {
      node->right_->parent_ = parent;
      if (parent) {
        ChangeChildOfParent(parent, node, node->right_);
      } else {
        root_ = node->right_;
      }
      node->right_->left_ = begin_null_;
      begin_null_->parent_ = node->right_;
    } else {
      Node *min_right = GetMin(node->right_);
      Node *tmp = min_right->right_;
      Node *parent_moved = min_right->parent_;
      parent_moved->left_ = tmp;
      if (tmp) tmp->parent_ = parent_moved;
      min_right->parent_ = parent;
      if (parent) {
        ChangeChildOfParent(parent, node, min_right);
      } else {
        root_ = min_right;
      }
      min_right->right_ = node->right_;
      node->right_->parent_ = min_right;
      begin_null_->parent_ = min_right;
      min_right->left_ = begin_null_;
    }
  }

  void DeleteWithNullInRight(Node *node, Node *parent) {
    if (!node->left_->right_) {
      node->left_->parent_ = parent;
      if (parent) {
        ChangeChildOfParent(parent, node, node->left_);
      } else {
        root_ = node->left_;
      }
      node->left_->right_ = end_null_;
      end_null_->parent_ = node->left_;
    } else {
      Node *max_left = GetMax(node->left_);
      Node *tmp = max_left->left_;
      Node *parent_moved = max_left->parent_;
      parent_moved->right_ = tmp;
      if (tmp) tmp->parent_ = parent_moved;
      max_left->parent_ = parent;
      if (parent) {
        ChangeChildOfParent(parent, node, max_left);
      } else {
        root_ = max_left;
      }
      max_left->left_ = node->left_;
      node->left_->parent_ = max_left;
      end_null_->parent_ = max_left;
      max_left->right_ = end_null_;
    }
  }

  Node *Search(const key_type &key, Node *&tmp_node) {
    Node *parent = nullptr;
    while (tmp_node != nullptr && tmp_node != begin_null_ &&
           tmp_node != end_null_ &&
           comparator_.NotEquals(key, tmp_node->data_)) {
      parent = tmp_node;
      if (comparator_.LessThan(key, tmp_node->data_))
        tmp_node = tmp_node->left_;
      else if (comparator_.GreaterThan(key, tmp_node->data_))
        tmp_node = tmp_node->right_;
    }
    return parent;
  }

  bool IsLeaf(Node *check) {
    bool i = false;
    if (check->left_ == nullptr && check->right_ == nullptr) i = true;
    return i;
  }

  Node *HasOneChild(Node *check) {
    Node *i = nullptr;
    if (check->left_ && !check->right_) i = check->left_;
    if (!check->left_ && check->right_) i = check->right_;
    return i;
  }

  Node *GetMax(Node *start) {
    return start->right_ == nullptr ? start : GetMax(start->right_);
  }

  Node *GetMin(Node *start) {
    return start->left_ == nullptr ? start : GetMin(start->left_);
  }
};

#endif  //  CONTAINERS_SRC_S21_BTREE_H_
