#include <bits/stdc++.h>
using namespace std;

const int ha = 1e9 + 7;
const int N0 = 1e6, N = N0 + 10;
int fac[N], ifac[N];
// dp[i]: 有几个方案满足：家族 1~i 会联合叛乱，但对任意的 j<i，家族 1~j 都不会联合叛乱
int dp[N];

int power(int a, int b) {
    int res = 1;
    while (b) {
        if (b & 1) res = 1LL * res * a % ha;
        a = 1LL * a * a % ha;
        b >>= 1;
    }
    return res;
}

void initC() {
    fac[0] = 1;
    for (int i = 1; i <= N0; i++)
        fac[i] = 1LL * fac[i - 1] * i % ha;
    ifac[N0] = power(fac[N0], ha - 2);
    for (int i = N0 - 1; i >= 0; i--)
        ifac[i] = 1LL * ifac[i + 1] * (i + 1) % ha;
}

int C(int n, int m) {
    if (m < 0 || m > n) return 0;
    return 1LL * fac[n] * ifac[m] % ha * ifac[n - m] % ha;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    initC();
    
    int n, h;
    cin >> n >> h;
    vector<int> a(h+1, 0);
    for (int i = 1; i <= h; i++) {
        cin >> a[i];
        a[i] += a[i-1];
    }

    int ans = 0;
    for (int i = 1; i <= h; i++) {
        int tot = 1ll * fac[a[i]] * fac[n-a[i]] % ha;
        for (int j = 1; j < i; j++) {
            int x = a[i] - a[j];
            int mns = 1ll * dp[j] * ifac[n-a[j]] % ha;
            // 除法原理：先不允许剩下的人随便排，但 1~j 家族仍排在后面构成联合叛乱
            mns = 1ll * mns * fac[x] % ha * fac[n-a[i]] % ha;
            // 再把 j~i 家族的人排到后面以便构成 1~i 家族联合叛乱，剩下的人还是随便排
            tot = (tot - mns + ha) % ha;
        }
        dp[i] = tot;
        ans = (ans + dp[i]) % ha;
    }
    cout << (fac[n] - ans + ha) % ha << "\n";

    return 0;
}