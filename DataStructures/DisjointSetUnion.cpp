#include <bits/stdc++.h>
using namespace std;

struct DisjointSetUnion {
    vector<int> dsu_rank, dsu_parent;
    int size;

    void init(int n) {
        size = n + 1;
        dsu_rank.assign(size, 0);
        dsu_parent.assign(size, 0);
        for (int i = 1; i <= n; i++) {
            dsu_parent[i] = i;
        }
    }

    int find_set(int x) {
        if (x == dsu_parent[x])
		    return x;
	    return dsu_parent[x] = find_set(dsu_parent[x]); 
    }

    void union_sets (int x, int y) {
        x = find_set(x);
        y = find_set(y);
        if (x != y) {
            if (dsu_rank[x] < dsu_rank[y])
                swap (x, y);
            dsu_parent[y] = x;
            if (dsu_rank[x] == dsu_rank[y])
                ++dsu_rank[x];
        }
    }
};

void solve() {
    /*
        https://codeforces.com/problemset/problem/1167/C

        Disjoint Set Union solution example.
    */

    int n, m;
    cin >> n >> m;

    DisjointSetUnion DSU; DSU.init(n);
    vector<int> ans(n + 1, 0);

    for (int i = 1; i <= m; i++) {
        int sz, p = -1;
        cin >> sz;
        for (int j = 0; j < sz; j++) {
            int x;
            cin >> x;
            if (p != -1) {
                DSU.union_sets(p, x);
            }
            p = x;
        }
    }
    for (int x = 1; x <= n; x++) {
        ans[DSU.find_set(x)]++;
    }
    for (int x = 1; x <= n; x++) {
        cout << ans[DSU.find_set(x)] << ' ';
    }
    
}
 
signed main() {
    #ifdef _DEBUG
        freopen("input.txt", "r", stdin);
        freopen("output.txt", "w", stdout);
    #endif
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    solve();

    
    #ifdef _DEBUG
        cout << "\n\ntime: " << 1.0 * clock() / CLOCKS_PER_SEC << "s    ";
    #endif
}