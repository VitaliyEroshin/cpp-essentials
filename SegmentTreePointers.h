#include <iostream>
#include <algorithm>

class Segment_Tree {
private:
  struct Node {
    long long s = 0;
    Node* left = nullptr;
    Node* right = nullptr;
  };

  Node* root;

public:
  Segment_Tree(size_t max_size);

  long long get(size_t l, size_t r) { return get(l, r, 0, size, root); }

  void add(size_t i) { add(i, i, 0, size, root); }

  ~Segment_Tree();

  void dfs_delete(Node* v);
  
private:
  size_t size;

  Node*& touch(Node*& v);

  void update(Node*& v);

  void add(size_t i, int delta, size_t tl, size_t tr, Node*& v);

  long long get(size_t l, size_t r, size_t tl, size_t tr, Node*& v) const;
};

Segment_Tree::Segment_Tree(size_t max_size) {
  root = new Node();
  size = max_size;
}

Segment_Tree::~Segment_Tree() {
  dfs_delete(root);
  delete root;
}

void Segment_Tree::dfs_delete(Segment_Tree::Node *v) {
  if (v->left != nullptr) {
    dfs_delete(v->left);
    delete v->left;
  }
  if (v->right != nullptr) {
    dfs_delete(v->right);
    delete v->right;
  }
}

Segment_Tree::Node*& Segment_Tree::touch(Segment_Tree::Node*& v) {
  if (v == nullptr) {
    v = new Node();
  }
  return v;
}

void Segment_Tree::update(Segment_Tree::Node*& v) {
  long long sum = 0;
  if (v->left != nullptr)
    sum += v->left->s;
  if (v->right != nullptr)
    sum += v->right->s;
  v->s = sum;
}

void Segment_Tree::add(size_t i, int delta, size_t tl, size_t tr, Node*& v) {
  if (tr - tl == 1) {
    v->s += delta;
    return;
  }

  size_t tm = (tl + tr) / 2;

  if (i < tm) {
    add(i, delta, tl, tm, touch(v->left));
  } else {
    add(i, delta, tm, tr, touch(v->right));
  }

  update(v);
}

long long Segment_Tree::get(size_t l, size_t r, size_t tl, size_t tr, Node*& v) const {
  if (v == nullptr || tl >= r || tr <= l) {
    return 0;
  }

  if (tl >= l && tr <= r) {
    return v->s;
  }

  size_t tm = (tl + tr) / 2;

  const long long left_value = get(l, r, tl, tm, v->left);
  const long long right_value = get(l, r, tm, tr, v->right);

  return left_value + right_value;
}