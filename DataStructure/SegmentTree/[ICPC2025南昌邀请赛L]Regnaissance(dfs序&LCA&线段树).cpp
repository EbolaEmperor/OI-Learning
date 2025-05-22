#include <bits/stdc++.h>
using namespace std;
const int N = 300005, INF = 1e9;

struct Seg {
    struct Node { int mn, mx; };
    int n; vector<Node> st;
    Seg(int _n = 0) { init(_n); }
    void init(int _n) { n = _n; st.assign(n << 2, {INF, -INF}); }
    static Node merge(const Node &a, const Node &b) {
        return (Node) {min(a.mn, b.mn), max(a.mx, b.mx)};
    }
    void build(int p, int l, int r, const vector<int> &val) {
        if (l == r) {
            st[p] = (val[l] == -1 ? Node{INF, -INF} : Node{val[l], val[l]});
            return;
        }
        int m = (l + r) >> 1;
        build(p << 1, l, m, val); build(p << 1 | 1, m + 1, r, val);
        st[p] = merge(st[p << 1], st[p << 1 | 1]);
    }
    void build(const vector<int> &val) { build(1, 1, n, val); }
    void upd(int p, int l, int r, int pos, int v) {
        if (l == r) {
            st[p] = (v == -1 ? Node{INF, -INF} : Node{v, v});
            return;
        }
        int m = (l + r) >> 1;
        (pos <= m ? upd(p << 1, l, m, pos, v) : upd(p << 1 | 1, m + 1, r, pos, v));
        st[p] = merge(st[p << 1], st[p << 1 | 1]);
    }
    void upd(int pos, int v) { upd(1, 1, n, pos, v); }
    Node qry(int p, int l, int r, int L, int R) {
        if (L <= l && r <= R) return st[p];
        int m = (l + r) >> 1;
        if (R <= m) return qry(p << 1, l, m, L, R);
        if (L >  m) return qry(p << 1 | 1, m + 1, r, L, R);
        return merge(qry(p << 1, l, m, L, R), qry(p << 1 | 1, m + 1, r, L, R));
    }
    Node qry(int l, int r) { return qry(1, 1, n, l, r); }
};

int n, q;
vector<int> g[N];
int hson[N], top[N], dep[N], dfn[N], rid[N], siz[N], fa[N], tim;

void dfs1(int u) {
    siz[u] = 1; hson[u] = 0;
    for (int v : g[u]) {
        if (v == fa[u]) continue;
        fa[v] = u; dep[v] = dep[u] + 1;
        dfs1(v); siz[u] += siz[v];
        if (hson[u] == 0 || siz[hson[u]] < siz[v]) hson[u] = v;
    }
}
void dfs2(int u, int tp) {
    dfn[u] = ++tim; rid[tim] = u; top[u] = tp;
    if (hson[u]) dfs2(hson[u], tp);
    for (int v : g[u])
        if (v != fa[u] && v != hson[u])
            dfs2(v, v);
}
int lca(int u, int v) {
    while (top[u] != top[v]) {
        if (dep[top[u]] < dep[top[v]]) swap(u, v);
        u = fa[top[u]];
    }
    return dep[u] < dep[v] ? u : v;
}

struct Query { int l,r,x,id,dfnx; };
int ans[N];

int main(){
    ios::sync_with_stdio(false); cin.tie(nullptr);
    cin >> n >> q;
    for (int i=1,x,y;i<n;++i){
        cin >> x >> y;
        g[x].push_back(y); g[y].push_back(x);
    }
    dep[1] = 1; dfs1(1); dfs2(1, 1);

    vector<Query> qs(q);
    for (int i=0;i<q;++i){
        cin >> qs[i].l >> qs[i].r >> qs[i].x;
        qs[i].id=i; qs[i].dfnx=dfn[qs[i].x];
    }
    sort(qs.begin(),qs.end(),[](const Query&a,const Query&b){return a.dfnx<b.dfnx;});

    vector<int> valPre(n+1,-1), valNxt(n+1);
    for(int i=1;i<=n;++i) valNxt[i]=dfn[i];
    Seg pre(n), nxt(n);
    pre.build(valPre); nxt.build(valNxt);

    int ptr = 1;                 // 当前已经搬到 pre 的 dfn 上界 +1
    for (auto &qq: qs){
        /* 把 dfn < dfn(rt) 的点整体搬到 pre */
        while (ptr < qq.dfnx){
            int u = rid[ptr];
            pre.upd(u, dfn[u]);
            nxt.upd(u, -1);
            ++ptr;
        }

        auto A = pre.qry(qq.l, qq.r);
        auto B = nxt.qry(qq.l, qq.r);

        int u_dfn, v_dfn;
        if (A.mn == INF) u_dfn = B.mn, v_dfn = B.mx;
        else if (B.mn == INF) u_dfn = A.mn, v_dfn = A.mx;
        else u_dfn = B.mn, v_dfn = A.mx;

        int u = rid[u_dfn], v = rid[v_dfn], rt = qq.x;
        int res = lca(u,v), t;
        if (dep[t = lca(u,rt)] > dep[res]) res = t;
        if (dep[t = lca(v,rt)] > dep[res]) res = t;
        ans[qq.id]=res;
    }
    for (int i=0;i<q;++i) cout<<ans[i]<<'\n';
    return 0;
}