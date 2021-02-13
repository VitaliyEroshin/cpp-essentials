#include <bits/stdc++.h>
using namespace std;
  
const double PI = atan2(0, -1);
const int bp = 3;
const int sz = 1 << bp;
const int n = (1 << bp);

complex<double> arra[sz], arrb[sz], roots[sz];
int perm[sz];

void buildRoots(int sz = n) {
    for (int i = 0; i < sz; i++) 
        roots[i] = {cos(2 * PI * i / sz), sin(2 * PI * i / sz)};
}

void buildPerm(int sz = n) {
    for (int i = 1; i < sz; i++) 
        perm[i] = (perm[i >> 1] >> 1) | ((i & 1) << (bp - 1));
}

void FFT(complex<double> arr[]) {
    // Applying permutation
    for (int i = 0; i < sz; i++) {
        if (i < perm[i]) {
            swap(arr[i], arr[perm[i]]);
        }
    }

    int rootShift = sz / 2;
    for (int i = 1; i < sz; i *= 2) {
        for (int j = 0; j < sz; j += i * 2) {
            int rootPos = 0;
            for (int k = 0; k < i; k++) {

                auto val1 = arr[j + i + k] * roots[rootPos];
                arr[j + i + k] = arr[j + k] - val1;
                arr[j + k] += val1;

                rootPos += rootShift;
            }
            
        }
        rootShift /= 2;
    }
}
  
vector<int> mult(vector<int> a, vector<int> b) {
    fill(arra, arra + sz, 0);
    fill(arrb, arrb + sz, 0);

    for (int i = 0; i < a.size(); i++) {
        arra[i] = {(double) a[i], 0.0};
    }
    
    for (int i = 0; i < b.size(); i++) {
        arrb[i] = {(double) b[i], 0.0};
    }

    FFT(arra);
    FFT(arrb);
  
    for (int i = 0; i < sz; i++) {
        arra[i] *= arrb[i];
    }

    FFT(arra);

    reverse(arra + 1, arra + sz);

    vector<int> product;

    for (int i = 0; i < sz; i++) {
        product.push_back(round(arra[i].real() / sz));
    }
    while (!product.empty() && product.back() == 0) {
        product.pop_back();
    }
    return product;
  
}

void solve() {
    buildRoots();
    buildPerm();
    string s, t;
    cin >> s >> t;
    if (s == "0" or t == "0") {
        cout << 0;
        return;
    }
    vector<int> a, b;

    bool minus = 0;

    for (auto ch : s) {
        if (ch == '-') {
            minus ^= 1;
            continue;
        }
        a.push_back(ch - '0');
    }

    for (auto ch : t) {
        if (ch == '-') {
            minus ^= 1;
            continue;
        }
        b.push_back(ch - '0');
    }

    reverse(a.begin(), a.end());
    reverse(b.begin(), b.end());
    
    auto product = mult(a, b);
  
    int carry = 0;
    for (int i = 0; i < product.size() || carry; ++i) {
        if (i == product.size()) {
            product.push_back(0);
        }
        carry += product[i];
        product[i] = carry % 10;
        carry /= 10;
    }
  
    reverse(product.begin(), product.end());

    if (minus) cout << '-';
    for (int x : product) cout << x;
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