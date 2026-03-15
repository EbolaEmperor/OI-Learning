#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int MOD = 998244353;
const int N = 5005;

long long C[N][N];
long long pw2[N];

void init() {
    for (int i = 0; i < N; i++) {
        C[i][0] = 1;
        for (int j = 1; j <= i; j++)
            C[i][j] = (C[i - 1][j - 1] + C[i - 1][j]) % MOD;
    }
    pw2[0] = 1;
    for (int i = 1; i < N; i++)
        pw2[i] = (pw2[i - 1] * 2) % MOD;
}

long long getC(int n, int r) {
    if (r < 0 || r > n) return 0;
    return C[n][r];
}

void solve() {
    int n;
    long long m;
    if (!(cin >> n >> m)) return;
    vector<long long> a(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    sort(a.begin() + 1, a.end(), greater<long long>());

    long long bad = 0;
    for (int u = 1; u <= n; ++u) {
        int r = u;
        while (r + 1 <= n && 2 * a[r + 1] > a[u]) r++;
        int szA = u - 1;
        int szB = r - u;
        long long tot = getC(szA + szB, m - 1 - szA);
        if (tot == 0) continue; 
        
        int pB = r + 1; 
        for (int v = r + 1; v <= n + 1; ++v) {
            long long d = (v <= n) ? a[u] - a[v] : a[u];
            while (pB > u + 1 && a[pB - 1] < d) pB--;
            int cntB = r - pB + 1;
            long long ok = getC(szA + szB - cntB, m - 1 - szA);
            long long fail = (tot - ok + MOD) % MOD;
            if (fail > 0) {
                int rem = (v <= n) ? (n - v) : 0;
                bad = (bad + fail * pw2[rem]) % MOD;
            }
        }
    }
    cout << (pw2[n] - bad + MOD) % MOD << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    init();
    int c, t;
    cin >> c >> t;
    while (t--) solve();
    return 0;
}
