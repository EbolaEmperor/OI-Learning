#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int N = 200010, M = N * 20;
int rt[N], lson[M], rson[M], idn = 1, tot = 0;
ll cnt[M];
int a[N];

inline void pushup(int o) {
    cnt[o] = cnt[lson[o]] + cnt[rson[o]];
}

void build(int &o, int l, int r) {
    o = ++tot;
    if (l == r) {
        cnt[o] = a[l];
        return;
    }
    int mid = (l + r) / 2;
    build(lson[o], l, mid);
    build(rson[o], mid+1, r);
    pushup(o);
}

void insert(int &o, int l, int r, int z, int v) {
    if (!o) o = ++tot;
    if (l == r) {
        cnt[o] += v;
        return;
    }
    int mid = (l + r) >> 1;
    if (z <= mid) insert(lson[o], l, mid, z, v);
    else insert(rson[o], mid + 1, r, z, v);
    pushup(o);
}

int merge(int a, int b, int l, int r) {
    if (!a || !b) return a + b;
    if (l == r) {
        cnt[a] += cnt[b];
        return a;
    }
    int mid = (l + r) >> 1;
    lson[a] = merge(lson[a], lson[b], l, mid);
    rson[a] = merge(rson[a], rson[b], mid + 1, r);
    pushup(a);
    return a;
}

void split(int &told, int &tnew, int l, int r, int nl, int nr) {
    if (l >= nl && r <= nr) {
        tnew = told;
        told = 0;
        return;
    }
    int mid = (l + r) / 2;
    tnew = ++tot;
    if (nl <= mid) split(lson[told], lson[tnew], l, mid, nl, nr);
    if (nr > mid) split(rson[told], rson[tnew], mid+1, r, nl, nr);
    pushup(told);
    pushup(tnew);
}

ll qcnt(int o, int l, int r, int nl, int nr) {
    if (l >= nl && r <= nr) {
        return cnt[o];
    }
    int mid = (l + r) / 2;
    ll ans = 0;
    if (nl <= mid) ans += qcnt(lson[o], l, mid, nl, nr);
    if (nr > mid) ans += qcnt(rson[o], mid+1, r, nl, nr);
    return ans;
}

int qrank(int o, int l, int r, int k) {
    if (cnt[o] < k) return -1;
    if (l == r) return l;
    int mid = (l + r) / 2;
    if (k <= cnt[lson[o]]) return qrank(lson[o], l, mid, k);
    else return qrank(rson[o], mid+1, r, k-cnt[lson[o]]);
}

int main() {
    int n, m;
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++)
        scanf("%d", &a[i]);
    build(rt[1], 1, n);
    while(m--) {
        int op, p, x, y;
        scanf("%d%d%d", &op, &p, &x);
        if (op == 0) {
            scanf("%d", &y);
            split(rt[p], rt[++idn], 1, n, x, y);
        } else if (op == 1) {
            rt[p] = merge(rt[p], rt[x], 1, n);
        } else if (op == 2) {
            scanf("%d", &y);
            insert(rt[p], 1, n, y, x);
        } else if (op == 3) {
            scanf("%d", &y);
            printf("%lld\n", qcnt(rt[p], 1, n, x, y));
        } else {
            printf("%d\n", qrank(rt[p], 1, n, x));
        }
    }
    return 0;
}