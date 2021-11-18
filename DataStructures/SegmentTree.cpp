/*
    Универсальное дерево отрезков в виде структуры.
*/

#include <vector>
using namespace std;

struct Value {
    /*
        Структура полезного значения. Тут лежит то, из чего
        состоит наше дерево отрезков.
    */

    int x;
    Value(int x): x(x) {};
};

struct SegTree {
    
    vector<Value> tree;

    /*
        Важно не забывать указывать нейтральное значение 
        для нашего дерева отрезков, т.е значение, которое
        не повлияет на ответ. (Например 0 если мы считаем 
        сумму, или INF если считаем минимум.)
    */

    Value NeutralValue = Value(0);
    int size;

    Value treeFunction(Value a, Value b) {
        /*
            Сама функция дерева. Например в этом случае
            указана функция сложения.
        */

        return Value(a.x + b.x);
    }

    void init(int n) {
        size = 1;
        while (size < n) size *= 2;
        tree.assign(2 * size - 1, NeutralValue);
    }

    void build(vector<Value> &a, int x, int lx, int rx) {
        if (rx - lx == 1) {
            if (lx < a.size()) tree[x] = a[lx];
            return;
        }
        int m = (lx + rx) / 2;
        build(a, 2 * x + 1, lx, m);
        build(a, 2 * x + 2, m, rx);
        tree[x] = treeFunction(tree[2 * x + 1], tree[2 * x + 2]);
    }

    void build(vector<Value> &a) {
        /*
            Функция для постройки дерева отрезков.
            На вход подается вектор полезных значений.
        */

        init(a.size());
        build(a, 0, 0, size);
        
    }
    void set(int pos, Value v, int x, int lx, int rx) {
        if (rx - lx == 1) {
            tree[x] = v;
            return;
        }
        int m = (lx + rx) / 2;
        if (pos < m) {
            set(pos, v, 2 * x + 1, lx, m);
        } else {
            set(pos, v, 2 * x + 2, m, rx);
        }
        tree[x] = treeFunction(tree[2 * x + 1], tree[2 * x + 2]);
    }

    void set(int pos, Value v) {
        /*
            Функция для изменения значения определенного
            элемента в дереве.
        */

        set(pos, v, 0, 0, size);
    }

    Value calculate(int l, int r, int x, int lx, int rx) {
        if (l >= rx || r <= lx) return NeutralValue;
        if (l <= lx && rx <= r) return tree[x];

        int m = (lx + rx) / 2;
        Value lh = calculate(l, r, 2 * x + 1, lx, m);
        Value rh = calculate(l, r, 2 * x + 2, m, rx);

        return treeFunction(lh, rh);
    }

    Value calculate(int l, int r) {
        /*
            Функция подсчета значения на отрезке
        */

        return calculate(l, r, 0, 0, size);
    }
};