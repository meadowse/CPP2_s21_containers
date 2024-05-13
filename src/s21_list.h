#ifndef CONTAINERS_SRC_S21_LIST_H_
#define CONTAINERS_SRC_S21_LIST_H_

#include <iostream>
#include <limits>

namespace s21 {
template <typename T>
class List {
 public:
  using value_type = T;
  using reference = T&;
  using const_reference = const T&;
  using size_type = size_t;

  class Node {
   public:
    Node() : content_(0), next_(this), prev_(this) {}

    Node(value_type value, Node* next, Node* prev)
        : content_(value), next_(next), prev_(prev) {}

    Node(const Node& other)
        : content_(other.get_content()),
          next_(other.get_next()),
          prev_(other.get_prev()) {}

    Node(Node&& node)
        : content_(node.get_content()),
          next_(node.get_next()),
          prev_(node.get_prev()) {
      node.set_content(0);
      node.set_next(nullptr);
      node.set_prev(nullptr);
    }

    ~Node() {}

    Node& operator=(const Node& other) {
      next_ = other.get_next();
      prev_ = other.get_prev();
      content_ = other.get_content();
    }
    void set_content(const value_type& value) { content_ = value; }
    reference get_content_ref() { return content_; }
    const_reference get_content() const { return content_; }
    void set_next(Node* next) { next_ = next; }
    void set_next(const Node& next) { next_ = &next; }
    Node* get_next() const { return next_; }
    void set_prev(Node* prev) { prev_ = prev; }
    void set_prev(const Node& prev) { prev_ = &prev; }
    Node* get_prev() const { return prev_; }

   private:
    value_type content_;
    Node* next_;
    Node* prev_;
  };

  class ListIterator {
   public:
    ListIterator(Node& node) { node_ = &node; }

    ListIterator(Node* node_ptr) { node_ = node_ptr; }

    ListIterator(const ListIterator& other) { node_ = other.node_; }

    ListIterator(ListIterator&& other) {
      node_ = other.node_;
      other.node_ = nullptr;
    }

    ~ListIterator() {}

    ListIterator& operator=(const ListIterator& other) {
      node_ = other.node_;
      return *this;
    }

    Node* node() const { return node_; }

    reference operator*() { return node_->get_content_ref(); }

    const_reference operator*() const { return node_->get_content(); }

    ListIterator operator++(int) {
      ListIterator tmp = *this;
      node_ = node_->get_next();
      return tmp;
    }

    ListIterator& operator++() {
      node_ = node_->get_next();
      return *this;
    }

    ListIterator operator--(int) {
      ListIterator tmp = *this;
      node_ = node_->get_prev();
      return tmp;
    }

    ListIterator& operator--() {
      node_ = node_->get_prev();
      return *this;
    }

    ListIterator operator+(int n) {
      ListIterator temp = *this;
      for (int i = 0; i < n; i++) {
        ++temp;
      }
      return temp;
    }

    ListIterator operator-(int n) {
      ListIterator temp = *this;
      for (int i = 0; i < n; i++) {
        --temp;
      }
      return temp;
    }

    ListIterator operator+=(int n) {
      for (int i = 0; i < n; i++) {
        ++*this;
      }
      return *this;
    }

    ListIterator operator-=(int n) {
      for (int i = 0; i < n; i++) {
        --*this;
      }
      return *this;
    }

    bool operator==(const ListIterator& other) { return node_ == other.node_; }

    bool operator!=(const ListIterator& other) { return node_ != other.node_; }

   private:
    Node* node_;
  };

  class ListConstIterator {
   public:
    ListConstIterator(Node& node) { node_ = &node; }

    ListConstIterator(Node* node_ptr) { node_ = node_ptr; }

    ListConstIterator(const ListConstIterator& other) { node_ = other.node_; }

    ListConstIterator(ListConstIterator&& other) {
      node_ = other.node_;
      other.node_ = nullptr;
    }

    ~ListConstIterator() {}

    ListConstIterator& operator=(const ListConstIterator& other) {
      node_ = other.node_;
      return *this;
    }

    Node* node() const { return node_; }

    const_reference operator*() const { return node_->get_content(); }

    ListConstIterator operator++() {
      node_ = node_->get_next();
      return *this;
    }

    ListConstIterator operator++(int) {
      ListConstIterator tmp = *this;
      node_ = node_->get_next();
      return tmp;
    }

    ListConstIterator operator--() {
      node_ = node_->get_prev();
      return *this;
    }

    ListConstIterator operator--(int) {
      ListConstIterator tmp = *this;
      node_ = node_->get_prev();
      return tmp;
    }

    ListConstIterator operator+(int n) {
      ListConstIterator tmp = *this;
      for (int i = 0; i < n; i++) ++tmp;
      return tmp;
    }

    ListConstIterator operator-(int n) {
      ListConstIterator tmp = *this;
      for (int i = 0; i < n; i++) --tmp;
      return tmp;
    }

    ListConstIterator operator+=(int n) {
      for (int i = 0; i < n; i++) ++this;
      return *this;
    }

    ListConstIterator operator-=(int n) {
      for (int i = 0; i < n; i++) --this;
      return *this;
    }

    bool operator==(const ListConstIterator other) {
      return node_ == other.node_;
    }

    bool operator!=(const ListConstIterator other) {
      return node_ != other.node_;
    }

   private:
    Node* node_;
  };

  using iterator = ListIterator;
  using const_iterator = ListConstIterator;

  List() {}

  List(size_type n) {
    for (int i = 0; i < n; ++i) push_back(0);
  }

  List(std::initializer_list<value_type> const& items) {
    for (auto it = items.begin(); it != items.end(); ++it) push_back(*it);
  }

  List(const List& l) {
    for (auto it = l.cbegin(); it != l.cend(); ++it) push_back(*it);
  }

  List(List&& l) { this->swap(l); }

  ~List() {
    this->clear();
    delete node_null_;
  }

  List& operator=(const List& l) {
    this->clear();
    for (auto i = l.cbegin(); i != l.cend(); i++) this->push_back(*i);
    return *this;
  };

  const_reference front() { return *this->begin(); }

  const_reference back() { return *(this->end() - 1); }

  iterator begin() {
    iterator it(node_null_);
    if (size_ > 0) ++it;
    return it;
  }

  const_iterator cbegin() const {
    const_iterator it(node_null_);
    if (size_ > 0) ++it;
    return it;
  }

  iterator end() { return iterator(node_null_); }
  const_iterator cend() const { return const_iterator(node_null_); }

  bool empty() { return !(bool)size_; }

  size_type size() { return size_; }

  size_type max_size() const {
    return std::numeric_limits<size_type>::max() / (2 * sizeof(Node));
  }

  void clear() {
    if (size_ > 0) {
      auto it = this->begin();
      while (it != this->end()) {
        iterator tmp = it + 1;
        this->erase(it);
        it = tmp;
      }
    }
  }

  iterator insert(iterator pos, const_reference value) {
    Node* prev = (pos - 1).node();
    Node* next = pos.node();
    Node* tmp = new Node(value, next, prev);
    prev->set_next(tmp);
    next->set_prev(tmp);
    ++size_;
    return iterator(tmp);
  }

  void erase(iterator pos) {
    Node* prev = (pos - 1).node();
    Node* next = (pos + 1).node();
    next->set_prev(prev);
    prev->set_next(next);
    --size_;
    delete pos.node();
  }

  void push_back(const_reference value) { insert(this->end(), value); }
  void push_front(const_reference value) { insert(this->begin(), value); }

  void pop_back() {
    if (size_) erase(this->end() - 1);
  }

  void pop_front() {
    if (size_) erase(this->begin());
  }

  void swap(List& other) {
    List<Node*> this_nodes;
    List<Node*> other_nodes;
    this->ExtractNodes(this_nodes);
    other.ExtractNodes(other_nodes);
    this->InsertNodes(other_nodes);
    other.InsertNodes(this_nodes);

    size_type size_temp = size_;
    size_ = other.size();
    other.size_ = size_temp;
  }

  void merge(List& other) {
    auto it_1 = this->begin();
    auto it_2 = other.begin();
    while (it_2 != other.end()) {
      if (*it_2 <= *it_1) {
        auto temp = it_2 + 1;
        NodeHandOver(it_2, it_1, other, *this);
        it_2 = temp;
      } else if (it_1 == this->end()) {
        auto temp = it_2 + 1;
        NodeHandOver(it_2, it_1, other, *this);
        it_2 = temp;
        ++it_1;
      } else {
        ++it_1;
      }
    }
  }

  void splice(const_iterator pos, List& other) {
    if (!other.empty()) {
      List<Node*> other_nodes;
      List<Node*> zero;
      other.ExtractNodes(other_nodes);
      other.size_ = 0;
      other.InsertNodes(zero);

      Node* next = pos.node();
      Node* prev = (pos - 1).node();
      next->set_prev(other_nodes.back());
      prev->set_next(other_nodes.front());

      Node* first = other_nodes.front();
      Node* last = other_nodes.back();
      first->set_prev(prev);
      last->set_next(next);
    }
  }

  void reverse() {
    iterator it = this->end();
    do {
      SwitchNextPrev(it);
      --it;
    } while (it != this->end());
  }

  void unique() {
    auto it_1 = this->begin();
    auto it_2 = it_1 + 1;
    while (it_2 != this->end()) {
      if (*it_1 == *it_2) {
        auto tmp = it_1;
        ++it_1;
        erase(tmp);
      } else {
        ++it_1;
      }
      ++it_2;
    }
  }

  void sort() {
    if (size_ > 1) {
      auto it_compare = this->begin();
      auto it_switch = it_compare + 1;
      while (it_switch != this->end()) {
        if (*it_switch < *it_compare) {
          auto tmp_switch = it_switch + 1;
          while (*it_switch <= *it_compare && it_compare != this->end())
            --it_compare;
          ++it_compare;
          NodeHandOver(it_switch, it_compare, *this, *this);
          it_switch = tmp_switch;
          it_compare = it_switch - 1;
        } else {
          ++it_compare;
          ++it_switch;
        }
      }
    }
  }

 private:
  size_type size_ = 0;
  Node* node_null_ = new Node;

  void ExtractNodes(List<Node*>& dest) {
    if (size_ > 0) {
      dest.push_back(node_null_->get_next());
      dest.push_back(node_null_->get_prev());
    }
  }

  void InsertNodes(List<Node*>& source) {
    if (source.empty()) {
      node_null_->set_next(node_null_);
      node_null_->set_prev(node_null_);
    } else {
      Node* temp = source.front();
      temp->set_prev(node_null_);
      node_null_->set_next(temp);
      temp = source.back();
      temp->set_next(node_null_);
      node_null_->set_prev(temp);
    }
  }

  void SwitchNextPrev(iterator& it) {
    Node* node = it.node();
    Node* temp = node->get_next();
    node->set_next(node->get_prev());
    node->set_prev(temp);
  }

  void NodeHandOver(iterator& it_src, iterator& it_dest, List& src_list,
                    List& dest_list) {
    Node* src = it_src.node();
    Node* src_next = src->get_next();
    Node* src_prev = src->get_prev();
    src_next->set_prev(src_prev);
    src_prev->set_next(src_next);

    Node* dest_next = it_dest.node();
    Node* dest_prev = dest_next->get_prev();
    dest_next->set_prev(src);
    dest_prev->set_next(src);
    src->set_next(dest_next);
    src->set_prev(dest_prev);

    --src_list.size_;
    ++dest_list.size_;
  }
};
}  // namespace s21

#endif  // CONTAINERS_SRC_S21_LIST_H_