#include <bits/stdc++.h>
using namespace std;

const int inf = 0x3f3f3f3f;
const int N = 200010;
vector<int> g[N];
int fa[N], n, k;

void dfs(int u){
    for(int v : g[u])
        if(v != fa[u]){
            fa[v] = u;
            dfs(v);
        } 
}

// pre[i]: i 前面第一个 fa[j] > i 的位置 j
// pre2[i]: 第二个
// nxt[i]: i 后面第一个 fa[j] < i 的位置 j
// nxt2[i]: 第二个
int pre[N], pre2[N], nxt[N], nxt2[N];

struct node{
    int maxv, submax;
    node(int maxv = 0, int submax = 0) : maxv(maxv), submax(submax) {}
    node operator + (const node &rhs) const{
        node res;
        res.maxv = max(maxv, rhs.maxv);
        if(maxv > rhs.maxv) res.submax = max(submax, rhs.maxv);
        else res.submax = max(maxv, rhs.submax);
        return res;
    }
} tr[N << 2];

void insert(int o, int l, int r, int x, int v){
    if(l == r){
        tr[o] = tr[o] + node(v, -inf);
        return;
    }
    int mid = (l + r) / 2;
    if(x <= mid) insert(o<<1, l, mid, x, v);
    else insert(o<<1|1, mid+1, r, x, v);
    tr[o] = tr[o<<1] + tr[o<<1|1];
}

node query(int o, int l, int r, int nl, int nr){
    if(l >= nl && r <= nr) return tr[o];
    int mid = (l + r) / 2;
    if(nr <= mid) return query(o<<1, l, mid, nl, nr);
    else if(nl > mid) return query(o<<1|1, mid+1, r, nl, nr);
    else return query(o<<1, l, mid, nl, mid) + query(o<<1|1, mid+1, r, mid+1, nr);
}

void prework(){
    for(int i = 1; i < n; ++i){
        insert(1, 0, n, fa[i], i);
        auto tmp = query(1, 0, n, i+1, n);
        pre[i] = tmp.maxv;
        pre2[i] = tmp.submax;
    }
    memset(tr, -0x3f, sizeof(tr));
    for(int i = n; i >= 1; --i){
        insert(1, 0, n, fa[i], -i);
        auto tmp = query(1, 0, n, 0, i-1);
        nxt[i] = -tmp.maxv;
        nxt2[i] = -tmp.submax;
    }
}

const int ha = 998244353;
inline void upadd(int &x, const int &y){
    x += y;
    if(x > ha) x -= ha;
}

struct Sgt{
    int sum[N << 2];
    vector<pair<int,int>> hang[N];
    void add(int o, int l, int r, int x, int v){
        upadd(sum[o], v);
        if(l == r) return;
        int mid = (l + r) / 2;
        if(x <= mid) add(o<<1, l, mid, x, v);
        else add(o<<1|1, mid+1, r, x, v);
    }
    int qsum(int o, int l, int r, int nl, int nr){
        if(nl > nr) return 0;
        if(l >= nl && r <= nr) return sum[o];
        int mid = (l + r) / 2, ans = 0;
        if(nl <= mid) upadd(ans, qsum(o<<1, l, mid, nl, nr));
        if(nr > mid) upadd(ans, qsum(o<<1|1, mid+1, r, nl, nr));
        return ans;
    }
    void erase(int i){
        for(auto p : hang[i])
            add(1, 0, n, p.first, -p.second);
        hang[i].clear();
    }
} tr1, tr2;

// dp[s][i]: 在前 i 个点里分 s 段的方案数
int dp[405][N];

int main(){
    scanf("%d%d", &n, &k);
    for(int i = 1, u, v; i < n; ++i){
        scanf("%d%d", &u, &v);
        g[u].push_back(v);
        g[v].push_back(u);
    }
    dfs(1);
    prework();
    dp[0][0] = 1;
    for(int s = 1; s <= k; ++s){
        memset(tr1.sum, 0, sizeof(tr1.sum));
        memset(tr2.sum, 0, sizeof(tr2.sum));
        for(int i = 1; i <= n; ++i){
            tr1.add(1, 0, n, i, dp[s-1][i-1]);
            tr2.add(1, 0, n, i, dp[s-1][i-1]);
            if(nxt[i] <= n) tr1.hang[nxt[i]].push_back(make_pair(i, dp[s-1][i-1]));
            if(nxt2[i] <= n) tr2.hang[nxt2[i]].push_back(make_pair(i, dp[s-1][i-1]));
            // 因为要保证 nxt[j] > i, 所以当 i >= nxt[j] 时, 不再能从 j 转移, 需要抹除
            tr1.erase(i);
            tr2.erase(i);
            if(pre[i]) upadd(dp[s][i], tr1.qsum(1, 0, n, pre2[i] + 1, i));
            upadd(dp[s][i], tr2.qsum(1, 0, n, pre[i] + 1, i));
        }
        cout << dp[s][n] << endl;
    }
    return 0;
}