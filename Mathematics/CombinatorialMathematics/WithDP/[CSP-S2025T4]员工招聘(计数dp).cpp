#include <bits/stdc++.h>
using namespace std;
const int MOD = 998244353;

int addmod(int a, int b) {
    a += b;
    if (a >= MOD) a -= MOD;
    return a;
}
int mulmod(long long a, long long b) {
    return int(a * b % MOD);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m;
    if (!(cin >> n >> m)) return 0;
    string s; cin >> s;               // s[0..n-1], 每天的题目难度
    vector<int> c(n);
    for (int i = 0; i < n; ++i) cin >> c[i];

    // 统计 t_i = 有多少人 c_x = i
    vector<int> cnt(n + 2, 0);
    for (int x : c) {
        if (x > n) x = n;
        cnt[x]++;
    }

    // s_i = t_0 + ... + t_i
    vector<int> pre(n + 2, 0);
    pre[0] = cnt[0];
    for (int i = 1; i <= n + 1; ++i) pre[i] = pre[i - 1] + cnt[i];

    // factorial
    vector<int> fact(n + 2, 1);
    for (int i = 1; i <= n + 1; ++i) fact[i] = mulmod(fact[i - 1], i);

    // C(n,k) 直接 Pascal 预处理
    static int C[505][505];
    for (int i = 0; i <= n + 1; ++i) {
        C[i][0] = C[i][i] = 1;
        for (int j = 1; j < i; ++j) {
            C[i][j] = C[i - 1][j - 1] + C[i - 1][j];
            if (C[i][j] >= MOD) C[i][j] -= MOD;
        }
    }

    // dp_prev[j][k] = f_{i, j, k}
    static int dp_prev[505][505], dp_cur[505][505];
    dp_prev[0][0] = 1;

    for (int i = 0; i < n; ++i) {
        // 清空当前层
        for (int j = 0; j <= n; ++j)
            for (int k = 0; k <= n; ++k)
                dp_cur[j][k] = 0;

        int day = s[i] - '0';  // 这一天的 s_i

        for (int j = 0; j <= i; ++j) {            // 已经有 j 个离开
            int sj = pre[j];                      // c_x ≤ j 的总人数
            for (int k = 0; k <= sj; ++k) {       // 前 i 位里真正排到前面的有 k 个 c_x ≤ j
                int val = dp_prev[j][k];
                if (!val) continue;

                int used_big = i - k;             // 前 i 位里 c_x > j 的个数
                int tj1 = (j + 1 <= n) ? cnt[j + 1] : 0;  // c_x = j+1 的总个数

                if (day == 1) {
                    // 填 > j 的数：只把状态往 i+1 推，不拆具体人
                    dp_cur[j][k] = addmod(dp_cur[j][k], val);

                    // 填 ≤ j 的数：公式里的那一条
                    int maxc = min(used_big, tj1);
                    int rest_small = sj - k;      // 还没被放进去的 c_x ≤ j
                    if (rest_small > 0) {
                        for (int cnum = 0; cnum <= maxc; ++cnum) {
                            long long ways = val;
                            ways = ways * C[used_big][cnum] % MOD;
                            ways = ways * C[tj1][cnum] % MOD;
                            ways = ways * fact[cnum] % MOD;
                            ways = ways * rest_small % MOD;
                            int nk = k + cnum + 1;
                            dp_cur[j + 1][nk] = addmod(dp_cur[j + 1][nk], (int)ways);
                        }
                    }
                } else {
                    // s_i = 0 的三条

                    // 1) 填 ≤ j 的数
                    {
                        int maxc = min(used_big, tj1);
                        int rest_small = sj - k;
                        if (rest_small > 0) {
                            for (int cnum = 0; cnum <= maxc; ++cnum) {
                                long long ways = val;
                                ways = ways * C[used_big][cnum] % MOD;
                                ways = ways * C[tj1][cnum] % MOD;
                                ways = ways * fact[cnum] % MOD;
                                ways = ways * rest_small % MOD;
                                int nk = k + cnum + 1;
                                dp_cur[j + 1][nk] = addmod(dp_cur[j + 1][nk], (int)ways);
                            }
                        }
                    }

                    // 2) 填 j+1 的数
                    {
                        int maxc = min(used_big + 1, tj1);
                        for (int cnum = 1; cnum <= maxc; ++cnum) {
                            long long ways = val;
                            ways = ways * C[used_big][cnum - 1] % MOD;
                            ways = ways * C[tj1][cnum] % MOD;
                            ways = ways * fact[cnum] % MOD;
                            int nk = k + cnum;
                            dp_cur[j + 1][nk] = addmod(dp_cur[j + 1][nk], (int)ways);
                        }
                    }

                    // 3) 填 > j 的数
                    {
                        int maxc = min(used_big, tj1);
                        for (int cnum = 0; cnum <= maxc; ++cnum) {
                            long long ways = val;
                            ways = ways * C[used_big][cnum] % MOD;
                            ways = ways * C[tj1][cnum] % MOD;
                            ways = ways * fact[cnum] % MOD;
                            int nk = k + cnum;
                            dp_cur[j + 1][nk] = addmod(dp_cur[j + 1][nk], (int)ways);
                        }
                    }
                }
            }
        }
        // 滚动
        for (int j = 0; j <= n; ++j)
            for (int k = 0; k <= n; ++k)
                dp_prev[j][k] = dp_cur[j][k];
    }

    // 最后答案：∑_{j=0}^{n-m} f_{n, j, s_j} * (n - s_j)!
    int ans = 0;
    for (int j = 0; j <= n - m; ++j) {
        int sj = pre[j];
        int ways = dp_prev[j][sj];
        if (!ways) continue;
        ways = mulmod(ways, fact[n - sj]);
        ans = addmod(ans, ways);
    }
    cout << ans << "\n";
    return 0;
}
