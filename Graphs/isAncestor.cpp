#include <bits/stdc++.h>
using namespace std;

const int N = 2e5 + 1;
vector<int> parent(N), timein(N), timeout(N);
vector<vector<int>> graph(N);
int dfstime = 0, n, root = 0;

void dfs(int v) {
    timein[v] = dfstime++;
    for (auto x : graph[v]) {
        if (x == parent[v]) continue;
        dfs(x);
    }
    timeout[v] = dfstime++;
}

bool isAncestor(int a, int b) {
    return (timein[b] > timein[a] and timeout[b] < timeout[a]);
}

void solve() {
    cin >> n;
    for (int i = 0; i < n; i++) {
        int t; cin >> t; t--;
        parent[i] = t;
        if (t >= 0) graph[t].push_back(i);
        else root = i;
    }
    dfs(root);

    int m; cin >> m;
    while (m--) {
        int a, b;
        cin >> a >> b;
        a--; b--;
        cout << isAncestor(a, b) << '\n';
    }
 
}
