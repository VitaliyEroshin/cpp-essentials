#include <vector>

class Fenwick_Tree {
public:
  Fenwick_Tree(size_t size);

  void add(size_t i, int x);

  int sum(size_t l, size_t r) const { return sum(r) - sum(l - 1); }

private:
  std::vector<int> tree;
  size_t size;

  size_t f(size_t i) const { return i & -i; }

  int sum(size_t p) const;
};

Fenwick_Tree::Fenwick_Tree(size_t size): size(size) {
  tree.assign(size + 1, 0);
}

void Fenwick_Tree::add(size_t i, int x) {
  while (i <= size) {
    tree[i] += x;
    i += f(i);
  }
}

int Fenwick_Tree::sum(size_t p) const {
  int s = 0;
  while (p > 0) {
    s += tree[p];
    p -= f(p);
  }
  return s;
}