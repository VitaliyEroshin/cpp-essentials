#include <bits/stdc++.h>
using namespace std;

const int N = 1001;

int n;
int A[N], LIS[N], p[N];

int lis (int x) {
    for (int i = 0; i < x; i++) {
        if (A[i] < A[x] and LIS[i] + 1 > LIS[x]) {
            LIS[x] = LIS[i] + 1;
            p[x] = i;
        }
    }
    return LIS[x];
}
void solve() {
    cin >> n;
    for (int i = 0; i < n; i++) cin >> A[i];
    int ans = 0;
    for (int i = 0; i < n; i++) {
        LIS[i] = 1;
        p[i] = -1;
        if (lis(i) > LIS[ans]) {
            ans = i;
        }
    }
    vector<int> out;
    for (int x = ans; x != -1; x = p[x]) {
        out.push_back(A[x]);
    }
    reverse(out.begin(), out.end());
    for (auto x : out) cout << x << ' ';
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