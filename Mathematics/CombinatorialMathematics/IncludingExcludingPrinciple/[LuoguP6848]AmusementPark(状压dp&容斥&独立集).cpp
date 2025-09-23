#include <bits/stdc++.h>
using namespace std;

const int ha = 998244353;
const int inv2 = (ha + 1) / 2;
const int N = 18;
int g[N][N], n, m;
// indep[S]: 点集 S 构成的子图是否为独立集
bool indep[1 << N];
int f[1 << N], cnt[1 << N];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    cin >> n >> m;
    for (int i = 1; i <= m; i++) {
        int x, y;
        cin >> x >> y;
        --x; --y;
        g[x][y] = g[y][x] = 1;
    }

    cnt[0] = 0;
    for (int S = 0; S < (1 << n); S++) {
        indep[S] = true;
        for (int i = 0; i < n; i++) if ((S >> i) & 1) {
            for (int j = i + 1; j < n; j++) if ((S >> j) & 1) {
                if (g[i][j]) {
                    indep[S] = false;
                    break;
                }
            }
            if (!indep[S]) break;
        }
        if (S) cnt[S] = cnt[S & (S - 1)] + 1;
    }

    f[0] = 1;
    for (int S = 1; S < (1 << n); S++) {
        for (int T = S; T; T = (T - 1) & S) {
            if (indep[T]) {
                int tmp = (cnt[T] & 1) ? f[S ^ T] : ha - f[S ^ T];
                f[S] = (f[S] + tmp) % ha;
            }
        }
    }
    int ans = 1ll * f[(1 << n) - 1] * inv2 % ha * m % ha;
    cout << ans << endl;

    return 0;
}