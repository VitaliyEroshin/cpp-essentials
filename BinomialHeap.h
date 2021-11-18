/*
  Warning! This code is extremely bad.
  Do not use it, it is dangerous for society.
*/

#include <iostream>
#include <vector>
#define int long long
const int MAX_TREES = 32;
const int MAX_Q = 1000002;

struct Heap;
struct Node {
  int value;
  int num;
  int rank = 0;
  std::vector<Node*> children;
  Node* parent = nullptr;
  int heap = -1;
};

struct Tree {
  Tree() : root(nullptr) {};
  Node* root = nullptr;
  bool is_null() {
    return (root == nullptr);
  }
};

Tree unite(Tree x, Tree y) {
  Node* xr = x.root;
  Node* yr = y.root;
  if (xr->value > yr->value or (xr->value == yr->value && xr->num > yr->num)) {
    std::swap(xr, yr);
    std::swap(x, y);
  }
  yr->parent = xr;
  xr->children.push_back(yr);
  
  xr->rank++;
  xr->parent = nullptr;
  return x;
}

struct Heap {
  Tree trees[MAX_TREES];
  int heap_id;
  int getMin() {
    int res = INT32_MAX;
    for (int i = 0; i < MAX_TREES; i++) {
      if (!trees[i].is_null()) {
        res = std::min(res, trees[i].root->value);
      }
    }
    return res;
  }
  void clear() {
    for (int i = 0; i < MAX_TREES; i++) {
      trees[i].root = nullptr;
    }
  }
};

void merge(Heap& x, Heap& y, int heap_id) {
  Heap t;
  Tree carry = Tree();
  for (int i = 0; i < MAX_TREES; i++) {
    Tree x_tree = x.trees[i];
    Tree y_tree = y.trees[i];
    if (!carry.is_null() && !x_tree.is_null() && !y_tree.is_null()) {
      t.trees[i] = carry;
      carry = unite(x_tree, y_tree);
    } else if (carry.is_null() && !x_tree.is_null() && !y_tree.is_null()) {
      carry = unite(x_tree, y_tree);
    } else if (!carry.is_null() && x_tree.is_null() && !y_tree.is_null()) {
      carry = unite(carry, y_tree);
    } else if (!carry.is_null() && !x_tree.is_null() && y_tree.is_null()) {
      carry = unite(carry, x_tree);
    } else if (!carry.is_null() && x_tree.is_null() && y_tree.is_null()) {
      t.trees[i] = carry;
      carry.root = nullptr;
    } else if (carry.is_null() && !x_tree.is_null() && y_tree.is_null()) {
      t.trees[i] = x_tree;
    } else if (carry.is_null() && x_tree.is_null() && !y_tree.is_null()) {
      t.trees[i] = y_tree;
    }
  }
  x = t;
  y.clear();
  for (int i = 0; i < MAX_TREES; i++) {
    if (x.trees[i].is_null())
      continue;

    x.trees[i].root->heap = heap_id;
  }
  x.heap_id = heap_id;
}

Node* pointer[MAX_Q + 1];

void swap(Node* x, Node* y) {
  std::swap(pointer[x->num], pointer[y->num]);
  std::swap(x->num, y->num);
  std::swap(x->value, y->value);
}

void siftUp(Node* x) {
  if (x->parent == nullptr)
    return;
  
  
  if (x->value < x->parent->value || 
      (x->value == x->parent->value && x->num < x->parent->num)) {

    swap(x, x->parent);
    x = x->parent;
    siftUp(x);
  }
  return;
}

void decreaseKey(int i, int delta) {
  Node* node = pointer[i];
  node->value -= delta;
  siftUp(node);
}

void insert(Heap &x, int value, int i) {
  Heap t;
  t.trees[0].root = new Node();
  t.trees[0].root->value = value;
  t.trees[0].root->num = i;
  pointer[i] = t.trees[0].root;
  merge(x, t, x.heap_id);
}

void extractMin(Heap &h) {
  int minimal = -1;
  for (int i = 0; i < MAX_TREES; i++) {
    if (!h.trees[i].is_null()) {
      minimal = i;
      break;
    }
  }
  if (minimal == -1)
    return;

  for (int i = minimal + 1; i < MAX_TREES; i++) {
    if (!h.trees[i].is_null()) {
      Node* i_rt = h.trees[i].root;
      if (i_rt->value < h.trees[minimal].root->value || (i_rt->value == h.trees[minimal].root->value && i_rt->num < h.trees[minimal].root->num)) {
        minimal = i;
      }
    }
  }
  Heap other;
  for (auto N : h.trees[minimal].root->children) {
    Heap t;
    N->parent = nullptr;
    t.trees[N->rank].root = N;
    merge(other, t, h.heap_id);
  }

  delete h.trees[minimal].root;
  h.trees[minimal].root = nullptr;
  merge(h, other, h.heap_id);
}

int getHeap(Node* node) {
  while (node->parent != nullptr) {
    node = node->parent;
  }
  return node->heap;
}

void erase(int i, std::vector<Heap> &hps) {
  Node* node = pointer[i];
  node->value = INT32_MIN;
  int h = getHeap(node);
  siftUp(node);
  extractMin(hps[h]);
}
