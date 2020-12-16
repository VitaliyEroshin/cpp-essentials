#include <bits/stdc++.h>
using namespace std;

int EulerFunction (int n) {
	int ans = n;
	for (int i = 2; i * i <= n; i++)
		if (n % i == 0) {
			while (n % i == 0)
				n /= i;
			ans -= ans / i;
		}
	if (n > 1)
		ans -= ans / n;
	return ans;
}

int BinPow (int a, int n, int m) {
	int ans = 1;
	while (n) {
		if (n & 1)
			ans = a * ans % m;
		a = a * a % m;
		n >>= 1;
	}
	return ans;
}

int InversedMod (int a, int m) {
    return BinPow(a, EulerFunction(m) - 1, m);
}

vector<int> Factorize (int n) {
    vector<int> factorization;
    for (int i = 2; i * i <= n; i++) {
        if (n % i == 0) {
            factorization.push_back(i);
            while (n % i == 0) n /= i;
        }
    }
    if (n > 1) factorization.push_back(n);
    return factorization;
}

int Generator (int p) {
	int phi = EulerFunction(p);
    vector<int> factorization = Factorize(phi);
    vector<int> pfactorization = Factorize(p);
	for (int g = 2; g <= p; g++) {
        bool ok = true;
        for (auto x : pfactorization) {
            if (g % x == 0) {
                ok = false;
                break;
            }
        }
        if (!ok) continue;
		
        for (auto divisor : factorization) {
            if (BinPow(g, phi / divisor, p) == 1) {
                ok = false;
                break;
            }
        }
		if (ok) return g;
	}
	return -1;
}

bool ExistanceOfGenerator(int n) {
    vector<int> fact = Factorize(n);
    if (fact.size() > 2) return false;
    if (fact.size() == 1) return true;
    if (fact[0] == 2) return true;
    return false;
}

void solve() {
    cout << "GL HF!";
}

signed main() {
    #ifdef _DEBUG
        freopen("input.txt", "r", stdin);
        freopen("output.txt", "w", stdout);
    #endif
    
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int t = 1;
    //cin >> t;
    while (t--) solve();
    
    #ifdef _DEBUG
        cout << "\n\nproc time: " << 1.0 * clock() / CLOCKS_PER_SEC << "s    ";
    #endif
    
}