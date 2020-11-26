#include <bits/stdc++.h>
using namespace std;
const int N = 2e5 + 1;
int n, m;
vector<vector<int>> graph(N);
vector<int> used(N, 0);
vector<int> parent(N, -1);
int cycleStart, cycleEnd;

bool dfs(int v) {
    used[v] = 1;
    for (auto x : graph[v]) {
        if (used[x] == 0) {
            parent[x] = v;
            if (dfs(x)) return true;
        }
        if (used[x] == 1) {
            cycleStart = x;
            cycleEnd = v;
            return true;
        }
    }
    used[v] = 2;
    return false;
}

void solve() {
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        a--; b--;
        graph[a].push_back(b);
    }

    for (int i = 0; i < n; i++) {
        if (used[i] != 0) continue;
        if (dfs(i)) {
            cout << "YES\n";
            vector<int> ans;
            int x = cycleEnd;
            while (x != cycleStart) {
                ans.push_back(x + 1);
                x = parent[x];
            }
            ans.push_back(x + 1);

            reverse(ans.begin(), ans.end());
            for (auto x : ans) cout << x << ' ';
            return;
        }
    }
    cout << "NO\n";
}
