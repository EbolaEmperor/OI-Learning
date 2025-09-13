#include <bits/stdc++.h>
using namespace std;

const int ha = 998244353;
const int N = 510;
// f[i][j]: 在 s[i..n] 里做 j 次操作有几种方案
int f[N][N], fac[N], ifac[N];

int Pow(int a, int b) {
    int ans = 1;
    for (; b; b >>= 1, a = 1ll * a * a % ha)
        if (b & 1) ans = 1ll * ans * a % ha;
    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    fac[0] = 1;
    for (int i = 1; i <= 500; i++)
        fac[i] = 1ll * fac[i-1] * i % ha;
    ifac[500] = Pow(fac[500], ha - 2);
    for (int i = 499; i >= 0; i--)
        ifac[i] = 1ll * ifac[i+1] * (i+1) % ha;
    
    auto C = [&](int n, int m) {
        return (n < m) ? 0 : 1ll * fac[n] * ifac[m] % ha * ifac[n-m] % ha;
    };

    int t, n, k;
    string s;
    cin >> t;
    while(t--) {
        memset(f, 0, sizeof(f));
        cin >> n >> k >> s;
        f[n+1][0] = 1;
        for (int i = n; i >= 1; i--) {
            for (int j = 0; j <= k; j++) {
                if (!f[i+1][j]) continue;
                // 在 s[i+1..n] 里面做了 j 次操作，准备在 s[i] 里做 l 次操作
                for (int l = 0; j + l <= k; l++) {
                    // 如果 s[i]==0，那么这 l 次操作必须安排在 j+l 次操作里的第奇数次操作里
                    if (s[i-1] == '0') f[i][j+l] = (f[i][j+l] + 1ll * f[i+1][j] * C((j+l+1)/2, l)) % ha;
                    else f[i][j+l] = (f[i][j+l] + 1ll * f[i+1][j] * C((j+l)/2, l)) % ha;
                }
            }
        }
        cout << f[1][k] << "\n";
    }
    return 0;
}