#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int MOD = 998244353;

ll qpow(ll a, ll e = MOD - 2)
{
    ll r = 1;
    for(; e; e >>= 1, a = a * a % MOD)
        if (e & 1) r = r * a % MOD;
    return r;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    vector<string> s(5);
    for (int i = 0; i < 5; ++i) cin >> s[i];

    auto rank_val = [](const string &t) -> int
    {
        if (t == "A") return 1;
        if (t == "J") return 11;
        if (t == "Q") return 12;
        if (t == "K") return 13;
        return stoi(t);
    };

    vector<int> hand;
    for (auto &t : s)
        hand.push_back(rank_val(t));
    sort(hand.begin(), hand.end());
    const int MAX_SUM = 65;

    int cnt[14] = {0};
    for (int v = 1; v <= 13; ++v) cnt[v] = 4;
    for (int v : hand) --cnt[v];

    static int f[6][6][MAX_SUM + 1][MAX_SUM + 1] = {0};
    static int g[6][6][MAX_SUM + 1][MAX_SUM + 1] = {0};
    f[0][0][0][0] = 1;

    for (int v = 1; v <= 13; ++v)
        for (int rep = 0; rep < cnt[v]; ++rep)
        {
            memset(g, 0, sizeof(g));
            for (int i = 0; i <= 5; ++i)
                for (int j = 0; j <= 5; ++j)
                    for (int x = 0; x <= MAX_SUM; ++x)
                        for (int y = 0; y <= MAX_SUM; ++y)
                        {
                            int val = f[i][j][x][y];
                            if (!val) continue;
                            (g[i][j][x][y] += val) %= MOD;
                            if (i < 5 && x + v <= MAX_SUM)
                                (g[i + 1][j][x + v][y] += val) %= MOD;
                            if (j < 5 && y + v <= MAX_SUM)
                                (g[i][j + 1][x][y + v] += val) %= MOD;
                        }
            memcpy(f, g, sizeof(f));
        }

    static int table[6][MAX_SUM + 1][MAX_SUM + 1] = {0};
    for (int i = 0; i <= 5; ++i)
        for (int x = 0; x <= MAX_SUM; ++x)
            for (int y = 0; y <= MAX_SUM; ++y)
                table[i][x][y] = f[i][5][x][y];

    for (int k = 1; k <= 5; ++k)
    {
        int s_k = 0;
        for (int idx = k; idx < 5; ++idx) s_k += hand[idx];

        ll winCnt = 0, loseCnt = 0, total = 0;
        for (int x = 0; x <= MAX_SUM; ++x)
            for (int y = 0; y <= MAX_SUM; ++y)
            {
                int val = table[k][x][y];
                if (!val) continue;
                total = (total + val) % MOD;
                ll sumJ = s_k + x;
                if (sumJ > y) winCnt = (winCnt + val) % MOD;
                else if (sumJ < y) loseCnt = (loseCnt + val) % MOD;
            }

        ll diff = (winCnt - loseCnt + MOD) % MOD;
        ll ans = k * diff % MOD * qpow(total) % MOD;
        cout << ans << '\n';
    }
    return 0;
}