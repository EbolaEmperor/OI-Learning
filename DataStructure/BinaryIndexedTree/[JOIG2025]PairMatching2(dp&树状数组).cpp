#include <bits/stdc++.h>
#define lowbit(x) ((x) & -(x))
using namespace std;

const int N = 800010;
int n, a[N], v[N], fst[N];
// dp[i][0/1]: 考虑到 i 位置，fst[a[i]] 到 i 之间 (不选别的牌 / 选一张别的牌)，最高分数
long long fenwick[N], dp[N][2], maxdp[N];

void update(int x, long long v) {
    for (int i = x; i <= n * 2; i += lowbit(i))
        fenwick[i] = max(fenwick[i], v);
}

long long query(int x) {
    long long res = 0;
    for (int i = x; i; i -= lowbit(i))
        res = max(res, fenwick[i]);
    return res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n;
    for (int i = 1; i <= 2*n; i++) {
        cin >> a[i];
        if (!fst[a[i]]) fst[a[i]] = i;
    }
    for (int i = 1; i <= n; i++) cin >> v[i];

    for (int i = 1; i <= 2*n; i++) {
        if (fst[a[i]] != i) {
            dp[i][0] = maxdp[fst[a[i]] - 1] + v[a[i]];
            dp[i][1] = query(fst[a[i]]) + v[a[i]];
            update(fst[a[i]], dp[i][0]);
        }
        maxdp[i] = max(maxdp[i-1], max(dp[i][0], dp[i][1]));
    }

    cout << maxdp[2*n] << "\n";
    return 0;
}