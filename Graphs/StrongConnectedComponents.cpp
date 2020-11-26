#include <bits/stdc++.h>
using namespace std;

const int N = 2e5;
int n, m; // n - количество вершин, m - количество ребер.
vector<vector<int>> graph(N); // Сам граф в виде списка ребер
vector<vector<int>> graphT(N); // Траспонированный граф
vector<bool> used;
vector<int> component, order;

void topologicalSort(int v) {
    used[v] = true;
    for (auto x : graph[v]) {
        if (!used[x]) topologicalSort(x);
    }
    order.push_back(v);
}

void componentSearch(int v) {
    used[v] = true;
    component.push_back(v);
    for (auto x : graphT[v]) {
        if (!used[x]) componentSearch(x);
    }
}

void solve() {
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        a--; b--;
        graph[a].push_back(b);
        graphT[b].push_back(a);
    }
    used.assign(n, false);
    for (int i = 0; i < n; i++) {
        if (!used[i]) topologicalSort(i);
    }
    used.assign(n, false);
    for (int i = 0; i < n; i++) {
        if (!used[i]) {
            componentSearch(i);
            for (auto x : component) cout << x + 1 << ' ';
            cout << '\n';
            component.clear();
        }
    }
}