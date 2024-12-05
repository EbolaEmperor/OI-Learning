#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <set>
#include <unordered_map>
#include <algorithm>
using namespace std;

namespace IO
{
    const int S=(1<<20)+5;
    //Input Correlation
    char buf[S],*H,*T;
    inline char Get()
    {
        if(H==T) T=(H=buf)+fread(buf,1,S,stdin);
        if(H==T) return -1;return *H++;
    }
    inline int read()
    {
        int x=0,fg=1;char c=Get();
        while(!isdigit(c)&&c!='-') c=Get();
        if(c=='-') fg=-1,c=Get();
        while(isdigit(c)) x=x*10+c-'0',c=Get();
        return x*fg;
    }
    //Output Correlation
    char obuf[S],*oS=obuf,*oT=oS+S-1,c,qu[55];int qr;
    inline void flush(){fwrite(obuf,1,oS-obuf,stdout);oS=obuf;}
    inline void putc(char x){*oS++ =x;if(oS==oT) flush();}
    struct END{~END(){flush();} } EENNDD;
    template <class I>inline void println(I x)
    {
        if(!x) putc('0');
        if(x<0) putc('-'),x=-x;
        while(x) qu[++qr]=x%10+'0',x/=10;
        while(qr) putc(qu[qr--]);
        putc('\n');
    }
}

const int N = 500010, K = 19;
vector<int> g[N];
int sz[N], hson[N], top[N], fa[N];
int dfn[N], odfn[N], dfc = 0;
int mindfn[20][N], maxdfn[20][N], dep[N];
struct Interval{int l, r, d;} intv[N << 1];
struct Query{int l, r, k, id;} qry[N];
int ans[N], n, m, q;

void dfs1(int u){
    sz[u] = 1;
    mindfn[0][u] = maxdfn[0][u] = dfn[u] = ++dfc;
    for(int v : g[u]){
        if(v == fa[u]) continue;
        dep[v] = dep[u] + 1;
        fa[v] = u;
        dfs1(v);
        if(!hson[u] || sz[v] > sz[hson[u]]) hson[u] = v;
        sz[u] += sz[v];
    }
    odfn[u] = dfc;
}

void dfs2(int u){
    if(hson[u]){
        top[hson[u]] = top[u];
        dfs2(hson[u]);
    }
    for(int v : g[u]){
        if(v == fa[u] || v == hson[u]) continue;
        top[v] = v;
        dfs2(v);
    }
}

int lca(int u, int v){
    while(top[u] != top[v]){
        if(dep[top[u]] > dep[top[v]]) u = fa[top[u]];
        else v = fa[top[v]];
    }
    return dep[u] < dep[v] ? u : v;
}

void getExtremeIntervals(){
    for(int i = 1; i <= n; i++)
        intv[i] = (Interval){i, i, dep[i]};
    m = n;
    unordered_map<unsigned long long, bool> have;
    for(int i = 1; i < n; i++){
        int c = lca(i, i + 1), l = i, r = i + 2;
        // 找极大区间的左端点
        for(int k = K; k >= 0; k--)
            if(l > (1<<k) && mindfn[k][l-(1<<k)] >= dfn[c] && maxdfn[k][l-(1<<k)] <= odfn[c])
                l -= 1<<k;
        // 找极大区间的右端点
        for(int k = K; k >= 0; k--)
            if(r + (1<<k) - 1 <= n && mindfn[k][r] >= dfn[c] && maxdfn[k][r] <= odfn[c])
                r += 1<<k;
        --r;
        unsigned long long hval = 1ull * l * (n + 1) + r;
        if(!have.count(hval)){
            intv[++m] = (Interval){l, r, dep[c]};
            have[hval] = 1;
        }
    }
}

int trmax[N << 2];
multiset<int> alld[N];

void upmax_cover(int o, int l, int r, int pos, int d){
    if(l == r){
        trmax[o] = max(trmax[o], d);
        return;
    }
    int mid = (l + r) / 2;
    if(pos <= mid) upmax_cover(o<<1, l, mid, pos, d);
    else upmax_cover(o<<1|1, mid+1, r, pos, d);
    trmax[o] = max(trmax[o<<1], trmax[o<<1|1]);
}

void upmax(int o, int l, int r, int pos, int d){
    if(l == r){
        alld[l].insert(d);
        trmax[o] = alld[l].empty() ? 0 : *(--alld[l].end());
        return;
    }
    int mid = (l + r) / 2;
    if(pos <= mid) upmax(o<<1, l, mid, pos, d);
    else upmax(o<<1|1, mid+1, r, pos, d);
    trmax[o] = max(trmax[o<<1], trmax[o<<1|1]);
}

void delmax(int o, int l, int r, int pos, int d){
    if(l == r){
        alld[l].erase(d);
        trmax[o] = alld[l].empty() ? 0 : *(--alld[l].end());
        return;
    }
    int mid = (l + r) / 2;
    if(pos <= mid) delmax(o<<1, l, mid, pos, d);
    else delmax(o<<1|1, mid+1, r, pos, d);
    trmax[o] = max(trmax[o<<1], trmax[o<<1|1]);
}

int qmax(int o, int l, int r, int nl, int nr){
    if(l >= nl && r <= nr) return trmax[o];
    int mid = (l + r) / 2, ans = 0;
    if(nl <= mid) ans = max(ans, qmax(o<<1, l, mid, nl, nr));
    if(nr > mid) ans = max(ans, qmax(o<<1|1, mid+1, r, nl, nr));
    return ans;
}

// qry.l <= intv.l <= qry.r <= intv.r
// 发现 scan3 完全覆盖了 scan1 的情况，故删去
// void scan1(){
//     struct Event{
//         int type; // 1: add; 2: del; 3: qry;
//         int arg1, arg2;
//     };
//     static vector<Event> eve[N];
//     for(int i = n+1; i < 2*n; i++)
//         eve[intv[i].l].push_back((Event){1, intv[i].l, intv[i].d});
//     for(int i = 1; i <= q; i++)
//         eve[qry[i].r].push_back((Event){3, qry[i].r - qry[i].k + 1, qry[i].id});
//     for(int i = n+1; i < 2*n; i++)
//         eve[intv[i].r].push_back((Event){2, intv[i].l, intv[i].d});
//     for(int i = 1; i <= n; i++){
//         for(auto e : eve[i]){
//             if(e.type == 1) upmax(1, 1, n, e.arg1, e.arg2);
//             else if(e.type == 2) delmax(1, 1, n, e.arg1, e.arg2);
//             else ans[e.arg2] = max(ans[e.arg2], qmax(1, 1, n, 1, e.arg1));
//         }
//     }
//     memset(trmax, 0, sizeof(trmax));
//     for(int i = 1; i <= n; i++) alld[i].clear();
// }

// intv.l <= qry.l <= intv.r <= qry.r
void scan2(){
    struct Event{
        int type; // 1: add; 2: del; 3: qry;
        int arg1, arg2;
    };
    static vector<Event> eve[N];
    for(int i = n+1; i <= m; i++)
        eve[intv[i].r].push_back((Event){1, intv[i].r, intv[i].d});
    for(int i = 1; i <= q; i++)
        eve[qry[i].l].push_back((Event){3, qry[i].l + qry[i].k - 1, qry[i].id});
    for(int i = n+1; i <= m; i++)
        eve[intv[i].l].push_back((Event){2, intv[i].r, intv[i].d});
    for(int i = n; i >= 1; i--){
        for(auto e : eve[i]){
            if(e.type == 1) upmax(1, 1, n, e.arg1, e.arg2);
            else if(e.type == 2) delmax(1, 1, n, e.arg1, e.arg2);
            else ans[e.arg2] = max(ans[e.arg2], qmax(1, 1, n, e.arg1, n));
        }
    }
    memset(trmax, 0, sizeof(trmax));
    for(int i = 1; i <= n; i++) alld[i].clear();
}

// qry.l <= intv.l <= intv.r <= qry.r
// 实际上，按 scan3 的写法，intv.r > qry.r 且 qry.r - intv.l + 1 >= k 的情况，也会被统计进去
void scan3(){
    struct Event{
        int k, pos;
        int type; // 1: add; 2: qry;
        int idx;
        bool operator < (const Event &rhs) const{
            return k > rhs.k || 
                   k == rhs.k && pos < rhs.pos ||
                   k == rhs.k && pos == rhs.pos && type < rhs.type;
        }
    };
    vector<Event> eve;
    for(int i = 1; i <= m; i++)
        eve.push_back((Event){intv[i].r - intv[i].l + 1, 
                              intv[i].r,
                              1, i});
    for(int i = 1; i <= q; i++)
        eve.push_back((Event){qry[i].k, 
                              qry[i].r, 
                              2, i});
    sort(eve.begin(), eve.end());
    for(auto e : eve){
        int id = e.idx;
        if(e.type == 1)
            upmax_cover(1, 1, n, intv[id].l, intv[id].d);
        else
            ans[id] = max(ans[id], qmax(1, 1, n, qry[id].l, qry[id].r - qry[id].k + 1));
    }
    memset(trmax, 0, sizeof(trmax));
    for(int i = 1; i <= n; i++) alld[i].clear();
}

int main(){
    using IO::read;
    using IO::println;
    n = read();
    for(int i = 1, u, v; i < n; i++){
        u = read(); v = read();
        g[u].push_back(v);
        g[v].push_back(u);
    }
    dep[1] = 1;
    dfs1(1); top[1] = 1; dfs2(1);
    for(int k = 1; k <= K; k++)
        for(int i = 1; i + (1<<k) - 1 <= n; i++){
            mindfn[k][i] = min(mindfn[k-1][i], mindfn[k-1][i+(1<<(k-1))]);
            maxdfn[k][i] = max(maxdfn[k-1][i], maxdfn[k-1][i+(1<<(k-1))]);
        }
    getExtremeIntervals();
    q = read();
    for(int i = 1; i <= q; i++){
        qry[i].l = read();
        qry[i].r = read();
        qry[i].k = read();
        qry[i].id = i;
    }
    scan2(); scan3();
    for(int i = 1; i <= q; i++)
        println(ans[i]);
    return 0;
}