#include <bits/stdc++.h>
using namespace std;

const int N = 500010;
const int all = (1u << 31) - 1;
int mn[N << 2], sand[N << 2], sor[N << 2];
int tand[N << 2], tor[N << 2];
int n, q, a[N];

void pushup(int o) {
    sand[o] = sand[o << 1] & sand[o << 1 | 1];
    sor[o] = sor[o << 1] | sor[o << 1 | 1];
    mn[o] = min(mn[o << 1], mn[o << 1 | 1]);
}

inline void mand(int o, int x) {
    mn[o] &= x;
    sand[o] &= x;
    sor[o] &= x;
    tand[o] &= x;
    tor[o] &= x;
}
inline void mor(int o, int x) {
    mn[o] |= x;
    sand[o] |= x;
    sor[o] |= x;
    tor[o] |= x;
}

void pushdown(int o) {
    if (tand[o] < all) {
        mand(o << 1, tand[o]);
        mand(o << 1 | 1, tand[o]);
        tand[o] = all;
    }

    if (tor[o] > 0) {
        mor(o << 1, tor[o]);
        mor(o << 1 | 1, tor[o]);
        tor[o] = 0;
    }
}

void build(int o, int l, int r) {
    tand[o] = all;
    tor[o] = 0;
    if (l == r) {
        mn[o] = sand[o] = sor[o] = a[l];
        return;
    }
    int mid = (l + r) / 2;
    build(o << 1, l, mid);
    build(o << 1 | 1, mid + 1, r);
    pushup(o);
}

void cand(int o, int l, int r, int nl, int nr, int x) {
    if ((sor[o]&x) == sor[o]) return;
    if (l >= nl && r <= nr && (sand[o]&x) == (sor[o]&x))
        return mand(o, x); // 打上 lazy 标记，结束递归
    pushdown(o);
    int mid = (l + r) / 2;
    if (nl <= mid) cand(o << 1, l, mid, nl, nr, x);
    if (nr > mid) cand(o << 1 | 1, mid + 1, r, nl, nr, x);
    pushup(o);
}

void cor(int o, int l, int r, int nl, int nr, int x) {
    if ((sand[o] | x) == sand[o]) return;
    if (l >= nl && r <= nr && (sand[o] | x) == (sor[o] | x))
        return mor(o, x); // 打上 lazy 标记，结束递归
    pushdown(o);
    int mid = (l + r) / 2;
    if (nl <= mid) cor(o << 1, l, mid, nl, nr, x);
    if (nr > mid) cor(o << 1 | 1, mid + 1, r, nl, nr, x);
    pushup(o);
}

int qmin(int o, int l, int r, int nl, int nr) {
    if (l >= nl && r <= nr) return mn[o];
    int mid = (l + r) / 2, res = INT_MAX;
    pushdown(o);
    if (nl <= mid) res = min(res, qmin(o << 1, l, mid, nl, nr));
    if (nr > mid) res = min(res, qmin(o << 1 | 1, mid + 1, r, nl, nr));
    return res;
}

int main() {
    scanf("%d%d", &n, &q);
    for (int i = 1; i <= n; i++)
        scanf("%d", a + i);
    build(1, 1, n);
    int opt, l, r, x;
    while (q--) {
        scanf("%d%d%d", &opt, &l, &r);
        if (opt < 3) scanf("%d", &x);
        if (opt == 1) cand(1, 1, n, l, r, x);
        if (opt == 2) cor(1, 1, n, l, r, x);
        if (opt == 3) printf("%d\n", qmin(1, 1, n, l, r));
    }
    return 0;
}