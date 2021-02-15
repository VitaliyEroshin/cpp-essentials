#include <bits/stdc++.h>
using namespace std;

const int N = 1e6;

struct Node {
    int l, r;
    int s;

    Node(): l(-1), r(-1), s(-1) {};
};

int node_cnt = 0;
int versions[2 * N];
Node nodes[2 * N];

int init_a[2 * N];

int build(int l, int r) {
    if (r - l == 1) {
        int cur_v = node_cnt++;
        nodes[cur_v].s = init_a[l];
        return cur_v;
    }
    
    int cur_v = node_cnt++;
    int m = (l + r) / 2;
    int new_l = build(l, m);
    int new_r = build(m, r);
    nodes[cur_v].l = new_l;
    nodes[cur_v].r = new_r;
    return cur_v;
}

int get(int cur_v, int i, int l, int r) {
    if (r - l == 1) {
        return nodes[cur_v].s;
    }
     
    int m = (l + r) / 2;
    if (i < m) return get(nodes[cur_v].l, i, l, m);
    else return get(nodes[cur_v].r, i, m, r);

}

int upd(int cur_v, int i, int x, int l, int r) {
    if (r <= i or l > i) {
        return cur_v;
    }
    if (r - l == 1) {
        cur_v = node_cnt++;
        nodes[cur_v].s = x;
        return cur_v;
    }
    int m = (r + l) / 2;
    int new_v = node_cnt++;
    nodes[new_v].l = upd(nodes[cur_v].l, i, x, l, m);
    nodes[new_v].r = upd(nodes[cur_v].r, i, x, m, r);
    return new_v;
}

void solve() {
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> init_a[i];
    }
    int k = 1;
    versions[k++] = build(0, n);

    int m;
    cin >> m;
    for (int i = 0; i < m; i++) {
        string type;
        cin >> type;
        if (type == "create") {
            int v, j, x;
            cin >> v >> j >> x;
            j--;
            versions[k++] = upd(versions[v], j, x, 0, n);
        } else {
            int v, j;
            cin >> v >> j;
            j--;

            cout << get(versions[v], j, 0, n) << '\n';
        }
    }
 
}
       
signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    
    #ifdef debug
        freopen("input.txt", "r", stdin);
        freopen("output.txt", "w", stdout);
    #endif
     
    solve();
}