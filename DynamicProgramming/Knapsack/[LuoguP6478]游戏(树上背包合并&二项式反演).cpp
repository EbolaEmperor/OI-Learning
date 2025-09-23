#include <bits/stdc++.h>
using namespace std;

const int ha = 998244353;
const int N = 5050;
// dp[u][k]: 子树 u 里钦定 k 次非平局，其它不管的方案数
int dp[N][N], C[N][N], fac[N], siz[N], black[N], n;
vector<int> g[N];
string s;

void dfs(int u, int fa) {
    siz[u] = 1;
    black[u] = (s[u] == '1');
    dp[u][0] = 1;
    static int tmpdp[N];
    for (int v : g[u]) {
        if (v == fa) continue;
        dfs(v, u);
        for (int i = 0; i <= min(black[u], siz[u] - black[u]); i++)
            for (int j = 0; j <= min(black[v], siz[v] - black[v]); j++)
                tmpdp[i+j] = (tmpdp[i+j] + 1ll * dp[u][i] * dp[v][j]) % ha;
        siz[u] += siz[v];
        black[u] += black[v];
        for (int i = 0; i <= siz[u]; i++)
            dp[u][i] = tmpdp[i], tmpdp[i] = 0;
    }
    int tmp = (s[u] == '1') ? (siz[u] - black[u]) : black[u];
    for (int i = min(black[u], siz[u] - black[u]); i >= 1; i--)
        dp[u][i] = (dp[u][i] + 1ll * dp[u][i-1] * (tmp - i + 1)) % ha;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    cin >> n >> s;
    for (int i = 1; i < n; i++) {
        int x, y;
        cin >> x >> y;
        --x; --y;
        g[x].push_back(y);
        g[y].push_back(x);
    }
    dfs(0, -1);

    C[0][0] = 1;
    for (int i = 1; i <= n; i++) {
        C[i][0] = 1;
        for (int j = 1; j <= i; j++)
            C[i][j] = (C[i-1][j-1] + C[i-1][j]) % ha;
    }
    fac[0] = 1;
    for (int i = 1; i <= n; i++)
        fac[i] = 1ll * fac[i-1] * i % ha;
    // 除了钦定不平局的回合，其余回合可以按任意顺序排列
    for (int i = 0; i <= n/2; i++)
        dp[0][i] = 1ll * dp[0][i] * fac[n/2-i] % ha;

    // 二项式反演
    for (int i = 0; i <= n/2; i++) {
        int ans = 0;
        for (int j = i; j <= n/2; j++) {
            int tmp = 1ll * C[j][i] * dp[0][j] % ha;
            if ((j - i) & 1) tmp = ha - tmp;
            ans = (ans + tmp) % ha;
        }
        cout << ans << "\n";
    }
    int ans = 0;
    return 0;
}