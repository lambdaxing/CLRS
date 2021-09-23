#pragma once
#include "myExceptions.h"

template <typename T>
class rbTree {
 public:
  struct node;
  using pNode = node*;
  enum class colorType { RED, BLACK };
  struct node {
    node() = default;
    node(colorType c) : color(c) {}
    node(const T& k, pNode f, pNode l, pNode r, colorType c)
        : key(k), p(f), left(l), right(f), color(c) {}
    T key;
    pNode p;
    pNode left;
    pNode right;
    colorType color;
  };

  rbTree();
  rbTree(const rbTree& rhs);
  rbTree(rbTree&& rhs);
  rbTree& operator=(const rbTree& rhs);
  rbTree& operator=(rbTree&& rhs);
  ~rbTree();
  void swap(rbTree& rhs);

  void insert(const T& k);
  void del(const T& k);

 protected:
  void rb_insert(pNode z);
  void rb_delete(pNode z);
  pNode tree_search(const T& k);
  pNode tree_search_recursive(pNode x, const T& k);
  pNode tree_search_iterative(pNode x, const T& k);
  pNode tree_successor(pNode x);
  pNode tree_predecessor(pNode x);
  pNode tree_minimum(pNode x);
  pNode tree_maximum(pNode x);

  void left_rotate(pNode x);
  void right_rotate(pNode y);
  void rb_transplant(pNode u, pNode v);
  void rb_insert_fixup(pNode z);
  void rb_delete_fixup(pNode x);

  template <typename... Ts>
  pNode createNode(Ts&&... params) {
    return new node(std::forward<Ts>(params)...);
  }
  pNode copy(pNode v, pNode cp, pNode vnil);
  void clear(pNode x);

  pNode root;
  pNode nil;
};
template <typename T>
rbTree<T>::rbTree() {
  nil = createNode(colorType::BLACK);
  root = nil;
}
template <typename T>
rbTree<T>::rbTree(const rbTree& rhs) {
  nil = createNode(*(rhs.nil));
  root = copy(rhs.root, nil, rhs.nil);
}
template <typename T>
rbTree<T>::rbTree(rbTree&& rhs) : nil(rhs.nil), root(rhs.root) {
  rhs.nil = createNode(colorType::BLACK);
  rhs.root = rhs.nil;  // 恢复 rhs 为默认 rbTree ，只为了可析构
}
template <typename T>
rbTree<T>& rbTree<T>::operator=(const rbTree& rhs) {
  if (this != &rhs) {
    auto t = rhs;
    swap(t);
  }
  return *this;
}
template <typename T>
rbTree<T>& rbTree<T>::operator=(rbTree&& rhs) {
  swap(rhs);
  return *this;
}
template <typename T>
rbTree<T>::~rbTree() {
  clear(root);
  delete nil;
}
template <typename T>
void rbTree<T>::clear(pNode x) {
  if (x != nil) {
    clear(x->left);
    clear(x->right);
    delete x;
  }
}
template <typename T>
void rbTree<T>::swap(rbTree& rhs) {
  using std::swap;
  swap(nil, rhs.nil);  // 交换两个的值
  swap(root,
       rhs.root);  // 交换后，两个指针分别指向对方的元素，当 nil = root 时无冲突
}
template <typename T>
typename rbTree<T>::pNode rbTree<T>::copy(pNode v, pNode cp, pNode vnil) {
  if (v != vnil) {
    auto c = createNode(v->key, cp, nil, nil, v->color);
    c->left = copy(v->left, c, vnil);
    c->right = copy(v->right, c, vnil);
    return c;
  }
  return nil;
}
template <typename T>
typename rbTree<T>::pNode rbTree<T>::tree_predecessor(pNode x) {
  if (x->left != nil) return tree_maximum(x->left);
  auto y = x->p;
  while (y != nil && x == y->left) {
    x = y;
    y = x->p;
  }
  return y;
}
template <typename T>
typename rbTree<T>::pNode rbTree<T>::tree_successor(pNode x) {
  if (x->right != nil) return tree_minimum(x->right);
  auto y = x->p;
  while (y != nil && x == y->right) {
    x = y;
    y = x->p;
  }
  return y;
}
template <typename T>
typename rbTree<T>::pNode rbTree<T>::tree_search_recursive(pNode x,
                                                           const T& k) {
  if (x == nil || x->key == k) return x;
  if (k < x->key)
    return tree_search_recursive(x->left, k);
  else
    return tree_search_recursive(x->right, k);
}
template <typename T>
typename rbTree<T>::pNode rbTree<T>::tree_search_iterative(pNode x,
                                                           const T& k) {
  while (x != nil && x->key != k) {
    if (k < x->key)
      x = x->left;
    else
      x = x->right;
  }
  return x;
}
template <typename T>
typename rbTree<T>::pNode rbTree<T>::tree_search(const T& k) {
  return tree_search_recursive(root, k);
}
template <typename T>
typename rbTree<T>::pNode rbTree<T>::tree_minimum(pNode x) {
  while (x->left != nil) x = x->left;
  return x;
}
template <typename T>
typename rbTree<T>::pNode rbTree<T>::tree_maximum(pNode x) {
  while (x->right != nil) x = x->right;
  return x;
}
template <typename T>
void rbTree<T>::rb_delete_fixup(pNode x) {
  while (x != root && x->color == colorType::BLACK) {
    if (x == x->p->left) {  // x 是 x->p->left 时
      auto w = x->p->right;
      if (w->color == colorType::RED) {
        w->color = colorType::BLACK;   // case 1
        x->p->color = colorType::RED;  // case 1
        left_rotate(x->p);             // case 1
        w = x->p->right;               // case 1
      }
      if (w->left->color == colorType::BLACK &&
          w->right->color == colorType::BLACK) {
        w->color = colorType::RED;  // case 2
        x = x->p;                   // case 2
        continue;
      } else if (w->right->color == colorType::BLACK) {
        w->left->color = colorType::BLACK;  // case 3
        w->color = colorType::RED;          // case 3
        right_rotate(w);                    // case 3
        w = x->p->right;                    // case 3
      }
      w->color = x->p->color;              // case 4
      x->p->color = colorType::BLACK;      // case 4
      w->right->color = colorType::BLACK;  // case 4
      left_rotate(x->p);                   // case 4
      x = root;                            // case 4
    } else {  // x 是 x->p->right 时，与上面对称，case 3,4 尤其。
      auto w = x->p->left;
      if (w->color == colorType::RED) {
        w->color = colorType::BLACK;
        x->p->color = colorType::RED;
        right_rotate(x->p);
        w = x->p->left;
      }
      if (w->left->color == colorType::BLACK &&
          w->right->color == colorType::BLACK) {
        w->color = colorType::RED;
        x = x->p;
        continue;
      } else if (w->left->color == colorType::BLACK) {
        w->right->color = colorType::BLACK;
        w->color = colorType::RED;
        left_rotate(w);
        w = x->p->left;
      }
      w->color = x->p->color;
      x->p->color = colorType::BLACK;
      w->left->color = colorType::BLACK;
      right_rotate(x->p);
      x = root;
    }
  }
  x->color = colorType::BLACK;
}
template <typename T>
void rbTree<T>::rb_delete(pNode z) {
  auto y = z;
  auto y_original_color = y->color;
  pNode x;
  if (z->left == nil) {
    x = z->right;
    rb_transplant(z, z->right);
  } else if (z->right == nil) {
    x = z->left;
    rb_transplant(z, z->left);
  } else {
    y = tree_minimum(z->right);
    y_original_color = y->color;
    x = y->right;
    if (y->p == z)
      x->p = y;
    else {
      rb_transplant(y, y->right);
      y->right = z->right;
      y->right->p = y;
    }
    rb_transplant(z, y);
    y->left = z->left;
    y->left->p = y;
    y->color = z->color;
  }
  if (y_original_color == colorType::BLACK) rb_delete_fixup(x);
}

template <typename T>
void rbTree<T>::rb_transplant(pNode u, pNode v) {
  if (u->p == nil)
    root = v;
  else if (u == u->p->left)
    u->p->left = v;
  else
    u->p->right = v;
  v->p = u->p;
}
template <typename T>
void rbTree<T>::rb_insert(pNode z) {
  auto y = nil;
  auto x = root;
  while (x != nil) {  // find position of inserting
    y = x;
    if (z->key < x->key)
      x = x->left;
    else
      x = x->right;
  }
  z->p = y;
  if (y == nil)
    root = z;  // insert empty rbTree
  else if (z->key < y->key)
    y->left = z;
  else
    y->right = z;
  z->left = z->right = nil;
  z->color = colorType::RED;
  rb_insert_fixup(z);
}
template <typename T>
void rbTree<T>::rb_insert_fixup(pNode z) {
  // while 循环处理性质四（red 结点的子结点为 black）背违反的情形，
  // 仅性质二被违反，while 循环不执行。
  while (z->p->color == colorType::RED) {
    if (z->p == z->p->p->left) {  // 结点 z 的父节点是其父结点的 left 时
      // 根据根结点为黑色的性质可知，z->p 不是根结点，因此 z->p->p 一定存在。
      auto y = z->p->p->right;  // y 是 z 的叔节点（祖父节点的 right)
      if (y->color == colorType::RED) {
        // 情况一，y 是 red，则 y->p(z->p->p) 一定是 black，
        // 将 y 和 z->p 即 z->p->p 的孩子结点变为 black,
        // z->p->p 变为 red，违反规则的 z 结点成了 z->p->p 。
        z->p->color = colorType::BLACK;   // case 1
        y->color = colorType::BLACK;      // case 1
        z->p->p->color = colorType::RED;  // case 1
        z = z->p->p;
        continue;
      } else if (z == z->p->right) {
        // 情况二，z 的叔结点 y 是 black，且 z 是 z->p 的 right
        // 利用一个左旋，将 情况二变为情况三
        z = z->p;        // case 2
        left_rotate(z);  // case 2
      }
      // 情况三，z 的叔结点 y 是 black ，且 z 是 z->p 的 left
      z->p->color = colorType::BLACK;   // case 3
      z->p->p->color = colorType::RED;  // case 3
      right_rotate(z->p->p);            // case 3
    } else {  // 结点 z 的父节点是其父节点的 right 时
      // 根据根结点为黑色的性质可知，z->p 不是根结点，因此 z->p->p 一定存在。
      auto y = z->p->p->left;  // y 是 z 的叔节点（祖父节点的 left)
      if (y->color == colorType::RED) {
        // 情况一，y 是 red，则 y->p(z->p->p) 一定是 black，
        // 将 y 和 z->p 即 z->p->p 的孩子结点变为 black,
        // z->p->p 变为 red，违反规则的 z 结点成了 z->p->p 。
        z->p->color = colorType::BLACK;   // case 1
        y->color = colorType::BLACK;      // case 1
        z->p->p->color = colorType::RED;  // case 1
        z = z->p->p;
        continue;
      } else if (z == z->p->right) {
        // 情况二，z 的叔结点 y 是 black，且 z 是 z->p 的 right
        // 利用一个左旋，将 情况二变为情况三
        z = z->p;        // case 2
        left_rotate(z);  // case 2
      }
      // 情况三，z 的叔结点 y 是 black ，且 z 是 z->p 的 left
      z->p->color = colorType::BLACK;   // case 3
      z->p->p->color = colorType::RED;  // case 3
      left_rotate(z->p->p);             // case 3
    }
  }
  // 若 rbTree 的性质二（根结点是黑色）被违反，此处纠正。
  // 注：while 循环结束时，z->p->color 是黑色，若 z 是根结点，
  // 则 z->p = nil 的 color 也是黑色。
  root->color = colorType::BLACK;
}

template <typename T>
void rbTree<T>::left_rotate(pNode x) {
  auto y = x->right;   // set y
  x->right = y->left;  // turn y's left subtree into x's right subtree
  if (y->left != nil) y->left->p = x;
  y->p = x->p;  // link x's parent to y
  if (x->p == nil)
    root = y;
  else if (x == x->p->left)
    x->p->left = y;
  else
    x->p->right = y;
  y->left = x;  // put x on y's left
  x->p = y;
}

template <typename T>
void rbTree<T>::right_rotate(pNode y) {
  auto x = y->left;    // set x
  y->left = x->right;  // turn x's right subtree into y's left subtree
  if (x->right != nil) x->right->p = y;
  x->p = y->p;  // link y's parent to x
  if (y->p == nil)
    root = x;
  else if (y->p->left == y)
    y->p->left = x;
  else
    y->p->right = x;
  x->right = y;  // put y on x's left
  y->p = x;
}

template <typename T>
void rbTree<T>::insert(const T& k) {
  rb_insert(createNode(k, nil, nil, nil, colorType::RED));
}

template <typename T>
void rbTree<T>::del(const T& k) {
  auto z = tree_search(k);
  if (z == nil) {
    throw illegalInputData("Delete elements that do not exist!");
  }
  rb_delete(z);
  delete z;
}