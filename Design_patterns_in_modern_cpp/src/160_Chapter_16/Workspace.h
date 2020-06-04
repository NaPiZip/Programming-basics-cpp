// Copyright 2019, Nawin

#ifndef _HEADER_WORKSPACE
#define _HEADER_WORKSPACE

template <typename T>
struct BinaryTree;

template <typename T>
struct Node {
  T value_;
  Node<T>* left_ = nullptr;
  Node<T>* right_ = nullptr;
  Node<T>* parent_ = nullptr;
  BinaryTree<T>* tree_ = nullptr;

  explicit Node(const T& value) : value_{ value } {}
  Node(const T& value, Node<T>* const left, Node<T>* const right) : value_{ value }, left_{ left }, right_{ right } {
    this->left_->tree_ = this->right_->tree_ = tree_;
    this->left_->parent_ = this->right_->parent_ = this;
  }
  void set_tree(BinaryTree<T>* t) {
    tree_ = t;
    if (left_)
      left_->set_tree(t);
    if (right_)
      right_->set_tree(t);
  }
};

template <typename T>
struct BinaryTree {
  Node<T>* root_ = nullptr;
  explicit BinaryTree(Node<T>* const root) : root_{ root } {
    root_->set_tree(this);
  }

  template <typename U>
  struct PreOrderIterator {
    Node<U>* current_;
    explicit PreOrderIterator(Node<U>* current) : current_{ current } {}

    bool operator!=(const PreOrderIterator<U>& other) {
      return current_ != other.current_;
    }
    Node<U>& operator*() {
      return *current_;
    }
    PreOrderIterator<U>& operator++() {
      if (current_->right_) {
        current_ = current_->right_;
        while (current_->left_)
          current_ = current_->left_;
      }
      else {
        Node<T>* p = current_->parent_;
        while (p && current_ == p->right_) {
          current_ = p;
          p = p->parent_;
        }
        current_ = p;
      }
      return *this;
    }
  };
    using iterator = PreOrderIterator<T>;
    iterator begin() {
      Node<T>* n = root_;
      if (n) {
        while (n->left_)
          n = n->left_;
      }
      return iterator{ n };
    }
    iterator end() {
      return iterator{ nullptr };
    }
  
};

#endif // _HEADER_WORKSPACE
