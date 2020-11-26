#include <bits/stdc++.h>
using namespace std;
const int N = 2e5 + 1;

int n, m, dfstime = 0;
vector<vector<pair<int, int>>> gr(N);
vector<int> timein(N), fup(N), used(N, 0), bridges;

void dfs(int v, int p = -1) {
    used[v] = 1;
    timein[v] = fup[v] = dfstime++;
    for (auto x : gr[v]) {
        int u = x.first;

        if (u == p) continue;

        if (used[u]) fup[v] = min(fup[v], timein[u]);
        else {
            dfs(u, v);
            fup[v] = min(fup[v], fup[u]);
            if (fup[u] > timein[v]) {
                bridges.push_back(x.second + 1);
            }
        }
    }
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
    cout << bridges.size() << '\n';
    sort(bridges.begin(), bridges.end());
    for (auto x : bridges) cout << x << ' ';
}
