#include <bits/stdc++.h>
#define INF 0x7effffff
using namespace std;

const int N = 300010;

namespace RMQ {
    int st[20][N];

    void init(int n, int* a) {
        for (int i = 1; i <= n; i++) st[0][i] = a[i];
        for (int j = 1; (1 << j) <= n; j++)
            for (int i = 1; i + (1 << j) - 1 <= n; i++)
                st[j][i] = max(st[j - 1][i], st[j - 1][i + (1 << (j - 1))]);
    }

    int query(int l, int r) {
        if (l > r) return -INF;
        int k = 31 - __builtin_clz(r - l + 1);
        return max(st[k][l], st[k][r - (1 << k) + 1]);
    }
}

namespace SGT {
    int cnt[N << 2];

    void update(int o, int l, int r, int k, int v) {
        if (l == r) {
            cnt[o] += v;
            return;
        }
        int m = (l + r) >> 1;
        if (k <= m) update(o << 1, l, m, k, v);
        else update(o << 1 | 1, m + 1, r, k, v);
        cnt[o] = min(cnt[o << 1], cnt[o << 1 | 1]);
    }
}

int n, m, p, r[N], f[N];
// v[c] 是公司 c 修的所有边的【终点】编号
vector<int> v[N];
// g[v] 是以 v 为终点的所有边的公司编号
vector<int> g[N];
int allC[N];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int placeholder;
    cin >> n >> m >> p;
    for (int i = 1; i <= m; i++) {
        int b, c;
        cin >> placeholder >> b >> c;
        g[b].push_back(c);
        allC[i] = c;
    }
    sort(allC + 1, allC + m + 1);
    p = unique(allC + 1, allC + m + 1) - allC - 1;
    for (int i = 1; i <= n; i++)
        for (int c : g[i]) {
            int cid = lower_bound(allC + 1, allC + p + 1, c) - allC;
            v[cid].push_back(i);
        }

    int pr = 0;
    for (int i = 1; i <= p; i++) {
        while (pr < p && SGT::cnt[1] == 0) {
            ++pr;
            for (int b : v[pr])
                SGT::update(1, 2, n, b, 1);
        }
        r[i] = (SGT::cnt[1] == 0) ? INF : pr;
        f[i] = (r[i] <= p) ? allC[i] - allC[r[i]] : -INF;
        for (int b : v[i])
            SGT::update(1, 2, n, b, -1);
    }

    RMQ::init(p, f);
    int q, L, R, X;
    cin >> q;
    while (q--) {
        cin >> L >> R >> X;
        int ql = lower_bound(allC + 1, allC + p + 1, L - X) - allC;
        int qr = upper_bound(allC + 1, allC + p + 1, L) - allC - 1;
        // 对所有的 c (未离散化下标) 满足 L - X <= c < L，查询是否存在一个 c，满足 
        //             r[L - X + c] <= R + c
        // 等价于：f[L - X + c] >= L - X - R
        int ans = RMQ::query(ql, qr);
        bool flag = (ans >= L - X - R);
        // 如果 qr 不是恰好为 L 对应的离散化位置，那可以考虑不移动 L，
        // 看 L 的下一个离散化位置是否满足 r[i] <= R + X
        if (qr < p && allC[qr] < L) {
            flag |= (r[qr + 1] <= p && allC[r[qr + 1]] <= R + X);
        }
        puts(flag ? "Yes" : "No");
    }

    return 0;
}