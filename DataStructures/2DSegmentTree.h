class Segment_Tree {
  int max_size;

  struct Inner_Node {
    Inner_Node(int l, int r) : tl(l), tr(r), left(nullptr), right(nullptr), value(0ll) {}

    int value;
    int tl;
    int tr;
    Inner_Node *left;
    Inner_Node *right;
  };

  struct Outer_Node {
    Outer_Node() : left(nullptr), right(nullptr) {
      inner_segment_tree = new Inner_Node(0, 50000);
    }

    Outer_Node *left;
    Outer_Node *right;
    Inner_Node *inner_segment_tree;
  };

  Outer_Node root;

  void zoom(int &tl, int &tr, int &tm, int i) {
    if (i < tm) {
      tr = tm;
    } else {
      tl = tm;
    }
    tm = (tl + tr) / 2;
  }

  void update_inner(Inner_Node *node, int i, int value) {
    int tl = node->tl;
    int tr = node->tr;

    if (tr - tl == 1) {
      node->value = value;
      return;
    }

    int tm = (tl + tr) / 2;

    Inner_Node *&inner_tree = (i < tm) ? (node->left) : (node->right);

    if (inner_tree == nullptr) {
      inner_tree = new Inner_Node(i, i + 1);
      inner_tree->value = value;

    } else if (inner_tree->tl <= i && i < inner_tree->tr) {
      update_inner(inner_tree, i, value);

    } else {
      zoom(tl, tr, tm, i);
      while ((i < tm) == (inner_tree->tl < tm)) {
        zoom(tl, tr, tm, i);
      }
      Inner_Node *new_inner_node = new Inner_Node(tl, tr);

      if (inner_tree->tl < tm) {
        new_inner_node->left = inner_tree;
      } else {
        new_inner_node->right = inner_tree;
      }

      inner_tree = new_inner_node;

      update_inner(new_inner_node, i, value);

    }

    int sum = 0;
    if (node->left) {
      sum += node->left->value;
    }
    if (node->right) {
      sum += node->right->value;
    }
    node->value = sum;
  }

  void update_outer(Outer_Node *node, int tl, int tr, int l, int r, int value) {

    int tm = (tl + tr) / 2;

    if (tr - tl == 1) {
      update_inner(node->inner_segment_tree, r, value);
      return;
    }

    if (l < tm) {
      if (node->left == nullptr) {
        node->left = new Outer_Node();
      }
      update_outer(node->left, tl, tm, l, r, value);
    } else {
      if (node->right == nullptr) {
        node->right = new Outer_Node();
      }
      update_outer(node->right, tm, tr, l, r, value);
    }

    int sum = 0;
    if (node->left) {
      sum += get_inner_sum(node->left->inner_segment_tree, r, r + 1);
    }
    if (node->right) {
      sum += get_inner_sum(node->right->inner_segment_tree, r, r + 1);
    }

    value = sum;
    update_inner(node->inner_segment_tree, r, value);

  }

  int get_inner_sum(Inner_Node *node, int l, int r) {
    if (node == nullptr) {
      return 0;
    }

    int tl = node->tl;
    int tr = node->tr;

    if (r <= tl || tr <= l) {
      return 0;
    }

    if (l <= tl && tr <= r) {
      return node->value;
    }

    if (node->value == 0) {
      return 0;
    }

    int left = get_inner_sum(node->left, l, r);
    int right = get_inner_sum(node->right, l, r);

    return left + right;
  }

  int get_outer_sum(Outer_Node *node, int tl, int tr, int xl, int xr, int yl, int yr) {

    if (node == nullptr || xr <= tl || tr <= xl) {
      return 0;
    }

    if (xl <= tl && tr <= xr) {
      return get_inner_sum(node->inner_segment_tree, yl, yr);
    }

    int mid = (tl + tr) / 2;

    int left = get_outer_sum(node->left, tl, mid, xl, xr, yl, yr);
    int right = get_outer_sum(node->right, mid, tr, xl, xr, yl, yr);

    return left + right;
  }

public:
  void set(int x, int y, int value) {
    update_outer(&root, 0, max_size, x, y, value);
  }

  int get(int x, int y) {
    return get_outer_sum(&root, 0, max_size, 0, x + 1, 0, y + 1);
  }

  Segment_Tree(int max_size): max_size(max_size) {};
};
