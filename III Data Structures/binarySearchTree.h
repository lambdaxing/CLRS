#pragma once
#include <functional>
#include <iostream>

// template <typename T>
// class binarySearchTree;
// template <typename T>
// void print(typename binarySearchTree<T>::pNode x);
// template <typename T>
// void preorder_tree_walk(
//     typename binarySearchTree<T>::pNode x,
//     std::function<void(typename binarySearchTree<T>::pNode)> f = print);
// template <typename T>
// void inorder_tree_walk(
//     typename binarySearchTree<T>::pNode x,
//     std::function<void(typename binarySearchTree<T>::pNode)> f = print);
// template <typename T>
// void postorder_tree_walk(
//     typename binarySearchTree<T>::pNode x,
//     std::function<void(typename binarySearchTree<T>::pNode)> f = print);

template <typename T>
class binarySearchTree {
 public:
  struct node;
  using pNode = node*;
  struct node {
    node(const T& k, pNode f = nullptr, pNode l = nullptr, pNode r = nullptr)
        : key(k), p(f), left(f), right(r) {}
    T key;
    pNode p = nullptr;
    pNode left = nullptr;
    pNode right = nullptr;
  };

  binarySearchTree() = default;
  binarySearchTree(const binarySearchTree& rhs);
  binarySearchTree(binarySearchTree&& rhs);
  binarySearchTree& operator=(const binarySearchTree& rhs);
  binarySearchTree& operator=(binarySearchTree&& rhs);
  ~binarySearchTree();

  void insert(const T& k);
  void del(const T& k);

 private:
  void swap(binarySearchTree& rhs);
  void copy(pNode v, pNode c,
            pNode cp);  // 复制 v 子树 到 c 上，cp 是 c 的父节点
  pNode createNode(const T& k, pNode f = nullptr, pNode l = nullptr,
                   pNode r = nullptr) {
    return new node(k, f, l, r);
  }

  pNode tree_search(const T& k);
  pNode tree_search_recursive(pNode x, const T& k);
  pNode tree_search_iterative(pNode x, const T& k);
  pNode tree_minimum(pNode x);
  pNode tree_maximum(pNode x);
  pNode tree_successor(pNode x);    // 寻找 x 的后驱结点
  pNode tree_predecessor(pNode x);  // 寻找 x 的前驱结点
  void tree_insert(pNode z);
  void transplant(pNode u,
                  pNode v);  // 用 v 替代 u，仅使 v 成为 u 的双亲的孩子结点，即
  // u->p->left/right = v 且 v->p = u->p 。
  void tree_delete(pNode z);

  pNode root = nullptr;
};

template <typename T>
void binarySearchTree<T>::insert(const T& k) {
  tree_insert(createNode(k));
}
template <typename T>
void binarySearchTree<T>::del(const T& k) {
  auto x = tree_search(k);
  if (x != nullptr) tree_delete(x);
}
template <typename T>
void binarySearchTree<T>::swap(binarySearchTree& rhs) {
  using std::swap;
  swap(root, rhs.root);
}
template <typename T>
void binarySearchTree<T>::copy(pNode v, pNode c, pNode cp) {
  if (v != nullptr) {
    c = createNode(v->key, cp);   // 复制当前结点
    copy(v->left, c->left, c);    // 复制 left-child
    copy(v->right, c->right, c);  // 复制 right-child
  }
}
template <typename T>
binarySearchTree<T>::binarySearchTree(const binarySearchTree& rhs) {
  copy(rhs.root, root, nullptr);
}
template <typename T>
binarySearchTree<T>::binarySearchTree(binarySearchTree&& rhs) : root(rhs.root) {
  rhs.root = nullptr;
}
template <typename T>
binarySearchTree<T>& binarySearchTree<T>::operator=(
    const binarySearchTree& rhs) {
  if (this != &rhs) {
    auto t = rhs;
    swap(t);
  }
  return *this;
}
template <typename T>
binarySearchTree<T>& binarySearchTree<T>::operator=(binarySearchTree&& rhs) {
  swap(rhs);
  return *this;
}

template <typename T>
void inorder_tree_walk(
    typename binarySearchTree<T>::pNode x,
    std::function<void(typename binarySearchTree<T>::pNode)> f) {
  if (x != nullptr) {
    inorder_tree_walk(x->left, f);
    f(x);
    inorder_tree_walk(x->right, f);
  }
}
template <typename T>
void preorder_tree_walk(
    typename binarySearchTree<T>::pNode x,
    std::function<void(typename binarySearchTree<T>::pNode)> f) {
  if (x != nullptr) {
    f(x);
    preorder_tree_walk(x->left, f);
    preorder_tree_walk(x->right, f);
  }
}
template <typename T>
void postorder_tree_walk(
    typename binarySearchTree<T>::pNode x,
    std::function<void(typename binarySearchTree<T>::pNode)> f) {
  if (x != nullptr) {
    postorder_tree_walk(x->left, f);
    postorder_tree_walk(x->right, f);
    f(x);
  }
}

void postorder_tree_walk(
    typename binarySearchTree<std::string>::pNode,
    std::function<void(typename binarySearchTree<std::string>::pNode)>);
void postorder_tree_walk(
    typename binarySearchTree<int>::pNode,
    std::function<void(typename binarySearchTree<int>::pNode)>);

template <typename T>
binarySearchTree<T>::~binarySearchTree() {
  std::function<void(pNode)> f = [](pNode x) { delete x; };
  postorder_tree_walk(root, f);
}

template <typename T>
typename binarySearchTree<T>::pNode binarySearchTree<T>::tree_search_recursive(
    pNode x, const T& k) {
  if (x == nullptr || x->key == k) return x;
  if (k < x->key)
    return tree_search_recursive(x->left, k);
  else
    return tree_search_recursive(x->right, k);
}
template <typename T>
typename binarySearchTree<T>::pNode binarySearchTree<T>::tree_search(
    const T& k) {
  return tree_search_recursive(root, k);
}
template <typename T>
typename binarySearchTree<T>::pNode binarySearchTree<T>::tree_search_iterative(
    pNode x, const T& k) {
  while (x != nullptr && k != x->key) {
    if (k < x->key)
      x = x->left;
    else
      x = x->right;
  }
  return x;
}

template <typename T>
typename binarySearchTree<T>::pNode binarySearchTree<T>::tree_minimum(pNode x) {
  while (x->left != nullptr) x = x->left;
  return x;
}

template <typename T>
typename binarySearchTree<T>::pNode binarySearchTree<T>::tree_maximum(pNode x) {
  while (x->right != nullptr) x = x->right;
  return x;
}

template <typename T>
typename binarySearchTree<T>::pNode binarySearchTree<T>::tree_successor(
    pNode x) {
  if (x->right != nullptr)
    return tree_minimum(x->right);  // x 的 right-child 不为空
  auto y = x->p;                    // x 的 right-child 为空
  // 向上搜寻，直至根或当前子树为一棵左子树
  while (y != nullptr && x == y->right) {
    x = y;
    y = y->p;
  }
  return y;  // 当前这棵左子树的父节点即为后继
}

template <typename T>
typename binarySearchTree<T>::pNode binarySearchTree<T>::tree_predecessor(
    pNode x) {
  if (x->left != nullptr) return tree_maximum(x->left);
  auto y = x->p;
  while (y != nullptr && x == y->left) {
    x = y;
    y = y->p;
  }
  return y;
}

template <typename T>
void binarySearchTree<T>::tree_insert(pNode z) {
  pNode y = nullptr;
  auto x = root;
  while (x != nullptr) {
    auto y = x;
    if (z->key < x->key)
      x = x->left;
    else
      x = x->right;
  }
  z->p = y;
  if (y == nullptr)
    root = z;  // tree was empty.
  else if (z->key < y->key)
    y->left = z;
  else
    y->right = z;
}

template <typename T>
void binarySearchTree<T>::transplant(pNode u, pNode v) {
  if (u->p == nullptr)
    root = v;
  else if (u == u->p->left)
    u->p->left = v;
  else
    u->p->right = v;
  if (v != nullptr) v->p = u->p;
  // v->left 和 v->right 由调用者处理
}

template <typename T>
void binarySearchTree<T>::tree_delete(pNode z) {
  if (z->left == nullptr)     // left-child 为空
    transplant(z, z->right);  // z 仅有 right-child 或无 child
  else if (z->right == nullptr)
    transplant(z, z->left);
  else {
    auto y = tree_minimum(z->right);  // y 是 z 的后继
    if (y->p != z) {                  // y 不是 z 的 right-child 时
      transplant(y, y->right);  // 将 y->right 变为 y->p 的（左）孩子
      y->right = z->right;      // 更新 y 的 right-child
      y->right->p = y;
    }
    transplant(z, y);   // 将 y 变为 z->p 的孩子
    y->left = z->left;  // 更新 y->left 为 z 的 left-child
    y->left->p = y;
  }
}