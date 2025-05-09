// 路径计数问题（ICPC 武汉邀请赛 T607368）
// 按题解思路分轻重两类颜色处理
// 代码均带中文注释，除注释外无多余说明

#include <bits/stdc++.h>
using namespace std;
using int64 = long long;
const int MOD = 998244353;

// ---- 组合数预处理 ----
struct Comb {
    vector<int> fac, ifac;
    Comb(int N = 0) { init(N); }
    int mod_pow(int64 a, int b) const {
        int64 res = 1;
        while (b) {
            if (b & 1) res = res * a % MOD;
            a = a * a % MOD;
            b >>= 1;
        }
        return int(res);
    }
    void init(int N) {
        fac.resize(N + 1);
        ifac.resize(N + 1);
        fac[0] = 1;
        for (int i = 1; i <= N; ++i) fac[i] = int64(fac[i - 1]) * i % MOD;
        ifac[N] = mod_pow(fac[N], MOD - 2);
        for (int i = N; i; --i) ifac[i - 1] = int64(ifac[i]) * i % MOD;
    }
    int C(int n, int k) const {
        if (k < 0 || k > n) return 0;
        return int64(fac[n]) * ifac[k] % MOD * ifac[n - k] % MOD;
    }
};

// ---- 主程序 ----
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    if (!(cin >> n >> m)) return 0;
    const int NM = n * m;
    vector<int> grid(NM);                        // 平铺后的颜色
    vector<vector<pair<int, int>>> pos(NM + 1);  // 每种颜色出现位置
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            int c; cin >> c;
            grid[(i - 1) * m + (j - 1)] = c;
            pos[c].push_back({i, j});
        }
    }

    Comb comb(n + m + 5);            // 组合数
    const int B = int(sqrt(NM)) + 1; // 分界阈值
    // const int B = NM;
    int64 answer = 0;

    // ---- 处理轻颜色（出现次数 ≤ B）----
    vector<pair<int, int>> tmp;
    for (int col = 1; col <= NM; ++col) if (!pos[col].empty() && (int)pos[col].size() <= B) {
        auto &v = pos[col];
        int cnt = v.size();
        vector<int> g(cnt, 0);        // g 值
        // 暴力 O(cnt^2) 转移
        for (int idx = cnt - 1; idx >= 0; --idx) {
            auto [r, c] = v[idx];
            int64 val = comb.C((n - r) + (m - c), n - r); // (r,c) -> (n,m) 的总路径
            for (int j = idx; j < cnt; ++j) {               // 枚举之后的位置
                auto [s, t] = v[j];
                if (s >= r && t >= c) {
                    int ways = comb.C((s - r) + (t - c), s - r);
                    val = (val - int64(ways) * g[j]) % MOD;
                }
            }
            if (val < 0) val += MOD;
            g[idx] = int(val);

            int fromStart = comb.C(r + c - 2, r - 1);     // (1,1) -> (r,c)
            answer = (answer + int64(fromStart) * g[idx]) % MOD;
        }
    }

    // ---- 处理重颜色（出现次数 > B）----
    vector<int> heavyList;
    for (int col = 1; col <= NM; ++col)
        if ((int)pos[col].size() > B) heavyList.push_back(col);

    vector<int> dp(NM, 0); // dp[i*m+j] 记录避开当前颜色的路径数
    for (int col : heavyList) {
        // 自底向上填 dp
        for (int i = n; i >= 1; --i) {
            for (int j = m; j >= 1; --j) {
                int idx = (i - 1) * m + (j - 1);
                if (grid[idx] == col) {
                    dp[idx] = 0;
                } else if (i == n && j == m) {
                    dp[idx] = 1;
                } else {
                    int64 sum = 0;
                    if (i < n) sum += dp[idx + m];   // 向下
                    if (j < m) sum += dp[idx + 1];   // 向右
                    dp[idx] = int(sum % MOD);
                }
            }
        }
        // 累加贡献
        for (auto [r, c] : pos[col]) {
            int idx = (r - 1) * m + (c - 1);
            int avoid = 0;
            if (r < n) avoid = (avoid + dp[idx + m]) % MOD;
            if (c < m) avoid = (avoid + dp[idx + 1]) % MOD;
            if (r == n && c == m) avoid = 1; // (n,m) 位置
            int fromStart = comb.C(r + c - 2, r - 1);
            answer = (answer + int64(fromStart) * avoid) % MOD;
        }
    }

    cout << answer % MOD << '\n';
    return 0;
}