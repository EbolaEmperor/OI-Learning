#include <bits/stdc++.h>
using namespace std;

const int N = 400010, M = 1e7;
vector<int> son[N];
int fa[N], dep[N], root[N], sgt[N];
int dfn[N], odfn[N], dfc = 0;
int ls[M], rs[M], cnt[M], mx[M], tot = 0;
int dsu[N];
int n, stcnt[N];
vector<int> damn[N];
int ans = 0;

int find(int x) {
    return dsu[x] == x ? x : dsu[x] = find(dsu[x]);
}

void pushup(int o) {
    cnt[o] = cnt[ls[o]] + cnt[rs[o]];
    mx[o] = max(mx[rs[o]], mx[ls[o]] + cnt[rs[o]]);
}

void update(int &o, int l, int r, int k, int v) {
    if (!o) o = ++tot;
    if (l == r) {
        cnt[o] += v;
        mx[o] = cnt[o] ? l + cnt[o] : 0;
        return;
    }
    int mid = (l + r) >> 1;
    if (k <= mid) update(ls[o], l, mid, k, v);
    else update(rs[o], mid + 1, r, k, v);
    pushup(o);
}

void merge(int &x, int y, int l, int r) {
    if (!x || !y) {
        x |= y;
        return;
    }
    if (l == r) {
        cnt[x] += cnt[y];
        mx[x] = cnt[x] ? l + cnt[x] : 0;
        return;
    }
    int mid = (l + r) >> 1;
    merge(ls[x], ls[y], l, mid);
    merge(rs[x], rs[y], mid + 1, r);
    pushup(x);
}

void dfs(int u) {
    dfn[u] = ++dfc;
    for (int v : son[u]) {
        dep[v] = dep[u] + 1;
        dfs(v);
    }
    odfn[u] = dfc;
}

void solve(int u) {
    for (int v : son[u]) {
        solve(v);
        merge(sgt[u], sgt[v], 1, 2 * n);
    }
    update(sgt[u], 1, 2 * n, dep[u], stcnt[u]);
    for (auto v : damn[u])
        update(sgt[u], 1, 2 * n, dep[v], -1);
    ans = max(ans, mx[sgt[u]] - dep[u]);
}

void addPath(int st, int ed) {
    stcnt[st]++;
    damn[ed].push_back(st);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    iota(dsu + 1, dsu + n + 1, 1);
    for (int i = 1; i <= n; i++) {
        cin >> fa[i];
        fa[n + i] = fa[i] + n; // 复制一棵一样的树
        if (find(i) != find(fa[i]))
            dsu[find(i)] = find(fa[i]);
    }

    for (int i = 1; i <= n; i++) {
        root[i] = root[i + n] = find(i);
        if (find(i) != i) continue;
        // 这时候 i 一定是基环上的点，断环为链
        fa[i + n] = fa[i];
        fa[i] = 0;
    }
    for (int i = 1; i <= 2 * n; i++)
        if (fa[i]) son[fa[i]].push_back(i);
    for (int i = 1; i <= n; i++)
        if (root[i] == i) dep[i] = 1, dfs(i);
    
    int m, st, ed;
    cin >> m;
    while (m--) {
        cin >> st >> ed;
        if (dfn[st] >= dfn[ed] && dfn[st] <= odfn[ed]) {
            addPath(st, ed);
        } else if (dfn[st + n] >= dfn[ed] && dfn[st + n] <= odfn[ed]) {
            addPath(st + n, ed), addPath(st, root[st]);
        } else {
            cout << -1 << endl;
            return 0;
        }
    }

    for (int i = 1; i <= n; i++)
        if (root[i] == i) solve(i);
    cout << ans << endl;
    
    return 0;
}