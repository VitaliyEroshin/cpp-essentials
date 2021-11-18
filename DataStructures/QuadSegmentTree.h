const int MAXX = 1e9;
const int MAXY = 1e9;
class Segment_Tree {
  struct Node {
    int value = 0;
    Node* leftup = nullptr;
    Node* rightup = nullptr;
    Node* leftdown = nullptr;
    Node* rightdown = nullptr;
  };

  Node* root;

  void update(Node* v) {
    int sum = 0;
    if (v->leftdown != nullptr) {
      sum += v->leftdown->value;
    }
    if (v->leftup != nullptr) {
      sum += v->leftup->value;
    }
    if (v->rightdown != nullptr) {
      sum += v->rightdown->value;
    }
    if (v->rightup != nullptr) {
      sum += v->rightup->value;
    }
    v->value = sum;
  }

  void set(int xtl, int xtr, int ytl, int ytr, int x, int y, Node* v, int value) {
    if (xtr - xtl == 1 && ytr - ytl == 1) {
      v->value = value;
      return;
    }
    int xtm = (xtl + xtr) / 2;
    int ytm = (ytl + ytr) / 2;
    if (x >= xtl && x < xtm) {
      if (y >= ytl && y < ytm) {
        if (v->leftdown == nullptr) {
          v->leftdown = new Node();
        }
        set(xtl, xtm, ytl, ytm, x, y, v->leftdown, value);
      } else {
        if (v->rightdown == nullptr) {
          v->rightdown = new Node();
        }
        set(xtl, xtm, ytm, ytr, x, y, v->rightdown, value);
      }

    } else {
      if (y >= ytl && y < ytm) {
        if (v->leftup == nullptr) {
          v->leftup = new Node();
        }
        set(xtm, xtr, ytl, ytm, x, y, v->leftup, value);
      } else {
        if (v->rightup == nullptr) {
          v->rightup = new Node();
        }
        set(xtm, xtr, ytm, ytr, x, y, v->rightup, value);
      }
    }
    update(v);
  }

  int get(int xtl, int xtr, int ytl, int ytr, int xl, int xr, int yl, int yr, Node* v) {
    if (v == nullptr || xtl >= xr || xtr <= xl || ytr <= yl || ytl >= yr) {
      return 0;
    }

    if (xtl >= xl && xtr <= xr && ytl >= yl && ytr <= yr) {
      return v->value;
    }

    int xtm = (xtr + xtl) / 2;
    int ytm = (ytr + ytl) / 2;

    int sum = 0;
    sum += get(xtl, xtm, ytl, ytm, xl, xr, yl, yr, v->leftdown);
    sum += get(xtl, xtm, ytm, ytr, xl, xr, yl, yr, v->rightdown);
    sum += get(xtm, xtr, ytl, ytm, xl, xr, yl, yr, v->leftup);
    sum += get(xtm, xtr, ytm, ytr, xl, xr, yl, yr, v->rightup);
    return sum;
  }

public:

  Segment_Tree() {
    root = new Node();
  };

  void set(int x, int y, int value) {
    set(0, MAXX, 0, MAXY, x, y, root, value);
  }

  int get(int x, int y) {
    return get(0, MAXX, 0, MAXY, 0, x, 0, y, root);
  }

};
