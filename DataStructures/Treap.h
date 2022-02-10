#include <utility>
#include <vector>

struct Treap {
  int value;
  int priority;
  size_t size;
  Treap* l;
  Treap* r;

  explicit Treap(int x) : value(x), priority(rand()), size(1), l(nullptr), r(nullptr) {};
};

size_t getSize(Treap* tree) {
  if (tree == nullptr)
    return 0;

  return tree->size;
}

void updateSize(Treap* tree) {
  tree->size = getSize(tree->l) + getSize(tree->r) + 1;
}

std::pair<Treap*, Treap*> split(Treap* tree, int key) {
  if (tree == nullptr) {
    return {nullptr, nullptr};

  } else if (tree->value <= key) {
    auto pair = split(tree->r, key);
    tree->r = pair.first;
    updateSize(tree);
    return {tree, pair.second};

  } else {
    auto pair = split(tree->l, key);
    tree->l = pair.second;
    updateSize(tree);
    return {pair.first, tree};
  }
}

Treap* merge(Treap* l, Treap* r) {
  if (l == nullptr) {
    return r;

  } else if (r == nullptr) {
    return l;

  } else if (l->priority < r->priority) {
    l->r = merge(l->r, r);
    updateSize(l);
    return l;

  } else {
    r->l = merge(l, r->l);
    updateSize(r);
    return r;
  }
}
