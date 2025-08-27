#include <bits/stdc++.h>
#define int long long
using namespace std;

typedef pair<int, int> PII;
typedef long long LL;
const int N = 2e5 + 10, I3 = 332748118, I2 = 499122177, MOD = 998244353;

int n, f[N][2][3], g[N][2][2];
// f[i][0/1][0/1/2] 表示当前有i张卡牌, 还未抽到水人卡, 是否有火人卡,
// 复制卡是0张, 1张, 或>=2张 g[i][0/1][0/1]表示当前怪物还有i滴血量, 是否有火人卡, 是否有复制卡

void add(int &a, int b) { a = (a + b) % MOD; }

int dp(int i, int j, int k) {
    if(i <= 0) return 0;
    if(k == 1 && i <= 2) return 0;
    if(k == 1 && j && i <= 4) return 0;
    if(g[i][j][k] != -1) return g[i][j][k];
    g[i][j][k] = 1;
    add(g[i][j][k], I3 * dp(i - 1, j, k) % MOD);  //抽到水人卡
    add(g[i][j][k], I3 * dp(i - 3, 1, k) % MOD);  //抽到火人卡
    if(!k) add(g[i][j][k], I3 * dp(i, j, k + 1) % MOD);  //抽到复制卡
    return g[i][j][k];
}

signed main() {
    cin >> n;
    memset(g, -1, sizeof(g));
    f[0][0][0] = 1;
    for (int i = 0; i <= n; i++)
        for (int j = 0; j < 2; j++)
            for (int k = 0; k < 3; k++) {
                add(f[i + 1][1][k], f[i][j][k] * I3 % MOD);  // 1/3的概率抽到火人卡
                add(f[i + 1][j][min(2ll, k + 1)], f[i][j][k] * I3 % MOD);  // 1/3的概率抽到复制卡
            }
    int res = 0;
    for (int i = 0; i <= n - 1 >> 1; i++) {
        add(res, I3 * (f[i][0][2] + f[i][1][2]) % MOD * (i + 1) % MOD); // 有>=2张复制卡
        for (int j = 0; j <= 1; j++) { //有j张复制卡（0<=j<=1）
            add(res, I3 * f[i][0][j] % MOD * (i + 1 + dp(n, 0, j)) % MOD);
            add(res, I3 * f[i][1][j] % MOD * (i + 1 + dp(n - 3 * (i - j), 1, j)) % MOD);
        }
    }
    for (int i = 0; i <= 2; i++) {
        add(res, f[n + 1 >> 1][1][i] * (n + 1 >> 1) % MOD);
        add(res, f[n + 1 >> 1][0][i] * ((n + 1 >> 1) + 3 * I2 % MOD) % MOD);
    }
    cout << res << endl;
    return 0;
}
