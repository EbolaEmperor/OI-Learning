// 费马小定理：a^{p-1} = 1 (mod p)  (p 是质数)
// 欧拉定理：a^{phi(m)} = 1 (mod m)  (a,m 互质)
// 扩展欧拉定理：a^{phi(m)+1} = a (mod m)  (a,m 是任意正数)

#include <iostream>
#include <cstring>
using namespace std;

int phi(int n) {
    int result = n;
    for (int i = 2; i * i <= n; ++i) {
        if (n % i == 0) {
            while (n % i == 0) n /= i;
            result -= result / i;
        }
    }
    if (n > 1) result -= result / n;
    return result;
}

int Pow(int a, int b, int m) {
    int result = 1;
    a %= m;
    while (b > 0) {
        if (b & 1) result = 1ll * result * a % m;
        a = 1ll * a * a % m;
        b >>= 1;
    }
    return result;
}

int main() {
    int a, m;
    string b_str;
    cin >> a >> m >> b_str;

    a %= m;
    if (a == 0 || m == 1) {
        cout << 0 << endl;
        return 0;
    }

    int b = 0, phi_m = phi(m);
    for (char c : b_str)
        b = (b * 10 + (c - '0')) % phi_m;
    if (b == 0) b = phi_m;
    int result = Pow(a, b, m);
    cout << result << endl;

    return 0;
}