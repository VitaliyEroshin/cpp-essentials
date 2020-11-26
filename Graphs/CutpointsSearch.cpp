#include <bits/stdc++.h>
using namespace std;

const int N = 2e5 + 1;
int n, m, dfstime = 0;
vector<vector<pair<int, int>>> gr(N);
vector<int> timein(N), fup(N), used(N, 0);
set<int> cutpoints;

void dfs(int v, int p = -1) {
    used[v] = 1;
    timein[v] = fup[v] = dfstime++;
    int children = 0;
    for (auto x : gr[v]) {
        int u = x.first;

        if (u == p) continue;
        if (used[u]) fup[v] = min(fup[v], timein[x.first]);
        else {
            dfs(u, v);
            fup[v] = min(fup[v], fup[u]);
            if (fup[u] >= timein[v] && p != -1) {
                cutpoints.insert(v);
            }
            children++;
        }
    }
    if (p == -1 and children > 1) cutpoints.insert(v);
}

void solve() {
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        a--; b--;
        gr[b].push_back({a, i});
        gr[a].push_back({b, i});
    }
    dfs(0);
    cout << cutpoints.size() << '\n';
    for (auto x : cutpoints) cout << x + 1 << '\n';
}