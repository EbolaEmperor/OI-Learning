#include <bits/stdc++.h>
using namespace std;

const int ha = 1e9 + 7;
const int N0 = 5000, N = N0 + 10;
int fac[N], ifac[N];
// d[i][j]: 有几个区间满足包含 i 个 -1，且包含 0～j 里所有出现过的数
int d[N][N];

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
    
    int t, n;
    cin >> t;
    while (t--) {
        cin >> n;
        vector<int> a(n), cnt(n+1, 0);
        int tot = 0;
        for (int i = 0; i < n; i++) {
            cin >> a[i];
            if (a[i] == -1) tot++;
            else cnt[a[i]]++;
        }
        for (int i = 1; i <= n; i++)
            cnt[i] += cnt[i - 1];

        int mnl = n, totl = 0;
        for (int l = 0; l < n; l++) {
            int mnr = n, totr = 0;
            for (int r = n-1; r >= l; r--) {
                d[tot - totl - totr][0]++;
                d[tot - totl - totr][min(mnl, mnr)]--;
                if (a[r] == -1) totr++;
                else mnr = min(mnr, a[r]);
            }
            if (a[l] == -1) totl++;
            else mnl = min(mnl, a[l]);
        }

        for (int i = 0; i <= tot; i++)
            for (int j = 1; j <= n; j++)
                d[i][j] += d[i][j - 1];
        
        int ans = 0;
        for (int i = 0; i <= n; i++) {
            int c1 = (i + 1) - cnt[i]; // 0~i 里有几个没出现的数
            for (int j = c1; j <= tot; j++) {
                ans = (ans + 1LL * d[j][i] * C(j, c1) % ha 
                                 * fac[c1] % ha * fac[tot - c1] % ha) % ha;
            }
        }
        cout << ans << '\n';

        for (int i = 0; i <= tot; i++)
            for (int j = 0; j <= n; j++)
                d[i][j] = 0;
    }

    return 0;
}