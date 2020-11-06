/*

    Этот файл содержит набор полезных функций для нахождения
    биномиального коэффициента по модулю MOD.

*/

const int MOD = 998244353;

// Расширенный алгоритм Евклида.
// Extended Euclidean algorithm
int xGCD(int a, int b, int &x, int &y) {
    if (b == 0) {x = 1; y = 0; return a;}
    int x1, y1, gcd = xGCD(b, a % b, x1, y1);
    x = y1;
    y = x1 - (long long) (a / b) * y1;
    return gcd;
}

// Факториал n по модулю MOD.
// Factorial of n modulo MOD
int modfact(int n) {
    int result = 1;
    while (n > 1) {
        result = (long long) result * n % MOD;
        n -= 1;
    }
    return result;
}

// Инверсия по модулю MOD.
// Inverse of a modulo MOD
int inverse(int a) {
    int x, y;
    xGCD(a, MOD, x, y);
    return x;
}

// Биномиальный коэффициент по модулю MOD.
// Binomial coefficient modulo MOD.
long long C(int n, int k) {
    return (long long) (modfact(n) * inverse(modfact(k)) % MOD) * inverse(modfact(n - k)) % MOD;
}