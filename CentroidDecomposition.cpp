#include <bits/stdc++.h>
#define int long long
using namespace std;

const int N = 1e5;
const int C = 20;
vector<int> gr[N];
int ci[N];
int ce[N];
int st[N];
unordered_map<int, int> di[N];
pair<int, int> pre[C][N];

int calcST(int x, int p = -1) {
    int &sz = st[x] = 1;
    for (auto y : gr[x]) {
        if (ce[y] == 0 and y != p)
            sz += calcST(y, x);
    }
    return sz;
}

int findCentroid(int x, int sz, int p = -1) {
    int son = false;
    for (auto &y : gr[x]) {
        if (ce[y] == 0 and y != p and st[y] > sz / 2) {
            son = true;
            swap(y, gr[x][0]);
        }
    }
    if (son)
        return findCentroid(gr[x][0], sz, x);
    else
        return x;
}

void setInfo(int x, int lv, int pr, int d = 0, int p = -1) {
    if (di[pr].count(ci[x])) 
        di[pr][ci[x]] = min(d, di[pr][ci[x]]);
    else
        di[pr][ci[x]] = d;
    
    pre[lv][x] = {pr, d};
    for (auto y : gr[x]) {
        if (y != p and ce[y] == 0) {
            setInfo(y, lv, pr, d + 1, x);
        }
    }
}

void centroid(int x, int cei) {
    int stsz = calcST(x);
    int cent = findCentroid(x, stsz);
    ce[cent] = cei;
    setInfo(cent, cei, cent);
    for (auto y : gr[cent]) {
        if (ce[y] == 0) {
            centroid(y, cei + 1);
        }
    }
}

void solve() {
    int n;
    cin >> n;
    for (int x = 1; x < n; x++) {
        int y;
        cin >> y;
        gr[x].push_back(y);
        gr[y].push_back(x);
    }
    for (int x = 0; x < n; x++) {
        cin >> ci[x];
    }
    
    int q;
    cin >> q;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < C; j++) {
            pre[j][i] = {-1, -1};
        }
    }
    centroid(0, 1);
    while (q--) {
        int x, c;
        cin >> x >> c;
        int ans = 1e9;
        for (int l = 0; l < C; l++) {
            if (pre[l][x].first == -1)
                continue;
            
            int ct = pre[l][x].first;
            int ds = 1e9;
            if (di[ct].count(c))
                ds = di[ct][c];
            ans = min(ans, pre[l][x].second + ds);
        }
        if (ans == 1e9) 
            ans = -1;

        cout << ans << ' ';
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