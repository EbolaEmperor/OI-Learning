#include <iostream>
#include <vector>
#include <cstring>
using namespace std;

const int N = 100010, P = 60 * N;
int rt[N], lson[P], rson[P], mxv[P], maxid[P], cnt;
int hson[N], top[N], dep[N], siz[N], fa[N];
vector<int> G[N];
int ans[N], n;

//------------------- 树剖 LCA --------------------------

void dfs1(int u) {
    dep[u] = dep[fa[u]] + 1;
    siz[u] = 1;
    for (int v : G[u]) {
        if (v == fa[u]) continue;
        fa[v] = u;
        dfs1(v);
        siz[u] += siz[v];
        if (siz[hson[u]] < siz[v]) hson[u] = v;
    }
}

void dfs2(int u, int tp) {
    top[u] = tp;
    if (hson[u]) dfs2(hson[u], tp);
    for (int v : G[u]) {
        if (v == fa[u] || v == hson[u]) continue;
        dfs2(v, v);
    }
}

int lca(int u, int v) {
    while (top[u] != top[v]) {
        if (dep[top[u]] < dep[top[v]]) swap(u, v);
        u = fa[top[u]];
    }
    return dep[u] < dep[v] ? u : v;
}

//------------------- 线段树合并 -------------------------

void pushup(int o) {
    if (mxv[lson[o]] >= mxv[rson[o]]) {
        mxv[o] = mxv[lson[o]];
        maxid[o] = maxid[lson[o]];
    } else {
        mxv[o] = mxv[rson[o]];
        maxid[o] = maxid[rson[o]];
    }
}

void insert(int &o, int l, int r, int z, int v) {
    if (!o) o = ++cnt;
    if (l == r) {
        mxv[o] += v;
        maxid[o] = z;
        return;
    }
    int mid = (l + r) >> 1;
    if (z <= mid) insert(lson[o], l, mid, z, v);
    else insert(rson[o], mid + 1, r, z, v);
    pushup(o);
}

int merge(int a, int b, int l, int r) {
    if (!a) return b;
    if (!b) return a;
    if (l == r) {
        mxv[a] += mxv[b];
        return a;
    }
    int mid = (l + r) >> 1;
    lson[a] = merge(lson[a], lson[b], l, mid);
    rson[a] = merge(rson[a], rson[b], mid + 1, r);
    pushup(a);
    return a;
}

void dfsmerge(int u) {
    for (int v : G[u]) {
        if (v == fa[u]) continue;
        dfsmerge(v);
        rt[u] = merge(rt[u], rt[v], 1, 1e5);
    }
    ans[u] = mxv[rt[u]] ? maxid[rt[u]] : 0;
}

//--------------------- 主程序 ---------------------------

int main() {
    int q;
    cin >> n >> q;
    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        G[u].push_back(v);
        G[v].push_back(u);
    }
    dfs1(1);
    dfs2(1, 1);
    int x, y, z;
    while (q--) {
        cin >> x >> y >> z;
        int l = lca(x, y);
        insert(rt[x], 1, 1e5, z, 1);
        insert(rt[y], 1, 1e5, z, 1);
        insert(rt[l], 1, 1e5, z, -1);
        if(fa[l]) insert(rt[fa[l]], 1, 1e5, z, -1);
    }
    dfsmerge(1);
    for (int i = 1; i <= n; i++) {
        cout << ans[i] << "\n";
    }
    return 0;
}