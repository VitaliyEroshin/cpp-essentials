#include <bits/stdc++.h>
using namespace std;
 
const int N = 1600043;
 
vector<int> graph[N], transposedGraph[N];
vector<int> order, result;
int component[N];
int used[N];
int v;
 
 
void addEdge (int x, int y) {
    graph[x].push_back(y);
    transposedGraph[y].push_back(x);
}
 
void addDisjunction (int x, int y) {
    addEdge(x ^ 1, y);
    addEdge(y ^ 1, x);
}
 
void topologicalSort (int x = 0) {
    if (used[x]) return;
    used[x] = 1;
    for (auto y : graph[x]) {
        topologicalSort(y);
    }
    order.push_back(x);
}
 
void setStrongComponents (int x, int c) {
    if (component[x]) return;
    component[x] = c;
    for (auto y : transposedGraph[x]) {
        setStrongComponents(y, c);
    }
}
 
bool solve2SAT() {
    for (int x = 0; x < 2 * v; x++) {
        if (!used[x]) topologicalSort(x);
    }
 
    reverse(order.begin(), order.end());
    int c = 1;
    for (auto x : order) {
        if (!component[x]) setStrongComponents(x, ++c);
    }
 
    for (int i = 0; i < v; i++) {
        if (component[2 * i] == component[2 * i + 1]) 
            return false;
        if (component[2 * i] > component[2 * i + 1])
            result.push_back(i);
    }
    return true;
}
 
void solve() {
    int n, p, M, m;
    cin >> n >> p >> M >> m;
 
    v = p + M - 1;
 
    for (int i = 0; i < n; i++) {
        int x, y;
        cin >> x >> y;
        x--; y--;
        addDisjunction(2 * x, 2 * y);
    }
    
    for (int i = 0; i < p; i++) {
        int l, r;
        cin >> l >> r;
        if (l != 1) 
            addDisjunction((p + l - 2) * 2, 2 * i + 1);
        if (r != M)
            addDisjunction((p + r - 1) * 2 + 1, 2 * i + 1);
    }
 
    for (int i = 0; i < m; i++) {
        int x, y;
        cin >> x >> y;
        x--; y--;
        addDisjunction(2 * x + 1, 2 * y + 1);
    }
 
    for(int i = 2; i <= M - 1; i++) {
	    int f1 = i - 2 + p;
	    int f2 = f1 + 1;
	    addDisjunction(f1 * 2, f2 * 2 + 1);
	}
 
    if (!solve2SAT()) {
        cout << -1;
        return;
    }
 
    int k = 1;
	vector<int> stations;
	for(auto x : result)
		if(x < p)
			stations.push_back(x);
		else
			k = max(k, x - p + 2);
    
    cout << stations.size() << ' ' << k << '\n';
	for(auto x : stations)
        cout << x + 1 << ' ';
	return;
}
 
 
signed main() {
    #ifdef debug
        freopen("input.txt", "r", stdin);
        freopen("output.txt", "w", stdout);
    #endif
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    solve();
 
    
    #ifdef debug
        cout << "\n\ntime: " << 1.0 * clock() / CLOCKS_PER_SEC << "s    ";
    #endif
}