#include <bits/stdc++.h>
using namespace std;

const int N = 1001;

int n, m;
int A[1001];
int B[1001];
int LCS[1001][1001];

int lcs(int x, int y) {
    if (LCS[x][y] != -1) return LCS[x][y];
    int ans;
    if (A[x - 1] == B[y - 1]) ans = lcs(x - 1, y - 1) + 1;
    else ans = max(lcs(x - 1, y), lcs(x, y - 1));

    LCS[x][y] = ans;
    return ans;
}

void solve() {
    cin >> n;
    for (int i = 0; i < n; i++) cin >> A[i];
    cin >> m;
    for (int i = 0; i < m; i++) cin >> B[i];

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            LCS[i][j] = -1;
        }
    }

    cout << lcs(n, m);
    
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