#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T; 
    if (!(cin >> T)) return 0;
    while (T--) {
        int H, W; 
        cin >> H >> W;
        vector<string> S(H);
        for (int i = 0; i < H; ++i) cin >> S[i];

        vector<int> row(H, 0);
        for (int i = 0; i < H; ++i) {
            int m = 0;
            for (int j = 0; j < W; ++j) if (S[i][j] == '#') m |= (1 << j);
            row[i] = m;
        }

        const int M = 1 << W, ALL = M - 1, INF = 1e9;
        vector<int> dp(M, INF), ndp(M, INF);

        int blacks0 = __builtin_popcount(row[0]);
        for (int cur = 0; cur < M; ++cur) {
            if ((cur & ~row[0]) == 0) {
                dp[cur] = blacks0 - __builtin_popcount(cur);
            }
        }

        for (int i = 1; i < H; ++i) {
            fill(ndp.begin(), ndp.end(), INF);
            int blacks = __builtin_popcount(row[i]);
            for (int prev = 0; prev < M; ++prev) if (dp[prev] < INF) {
                for (int cur = 0; cur < M; ++cur) {
                    if ((cur & ~row[i]) != 0) continue;
                    if (prev & ((prev << 1) & ALL) & cur & ((cur << 1) & ALL)) continue;
                    int repaint = blacks - __builtin_popcount(cur);
                    ndp[cur] = min(ndp[cur], dp[prev] + repaint);
                }
            }
            dp.swap(ndp);
        }

        cout << *min_element(dp.begin(), dp.end()) << "\n";
    }
    return 0;
}