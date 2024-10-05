#include <bits/stdc++.h>
using namespace std;

const int N = 5e5 + 5;
struct Edge{int v, w;};
vector<Edge> g[N];
long long maxl[N], submaxl[N], f[N];
int cnt[N], maxid[N], n, k;

void dfs1(int u, int fa){
    for(auto e : g[u]){
        if(e.v == fa) continue;
        dfs1(e.v, u);
        cnt[u] += cnt[e.v];
        if(cnt[e.v]){
            f[u] += f[e.v] + 2 * e.w;
            if(maxl[e.v] + e.w > maxl[u])
                submaxl[u] = maxl[u], maxl[u] = maxl[e.v] + e.w, maxid[u] = e.v;
            else if(maxl[e.v] + e.w > submaxl[u])
                submaxl[u] = maxl[e.v] + e.w;
        }
    }
}

void dfs2(int u, int fa){
    for(auto e : g[u]){
        if(e.v == fa) continue;
        if(!cnt[e.v])
            f[e.v] = f[u] + 2 * e.w, maxl[e.v] = maxl[u] + e.w, maxid[e.v] = u;
        else if(cnt[e.v] < k){
            f[e.v] = f[u];
            if(maxid[u] != e.v && maxl[u] + e.w > maxl[e.v])
                submaxl[e.v] = maxl[e.v], maxl[e.v] = maxl[u] + e.w, maxid[e.v] = u;
            else if(submaxl[u] + e.w > maxl[e.v])
                submaxl[e.v] = submaxl[e.v], maxl[e.v] = submaxl[u] + e.w, maxid[e.v] = u;
            else if(maxid[u] != e.v && maxl[u] + e.w > submaxl[e.v])
                submaxl[e.v] = maxl[u] + e.w;
            else if(submaxl[u] + e.w > submaxl[e.v])
                submaxl[e.v] = submaxl[u] + e.w;
        }
        dfs2(e.v, u);
    }
}

int main(){
    scanf("%d%d", &n, &k);
    for(int i = 1, a, b, c; i < n; i++){
        scanf("%d%d%d", &a, &b, &c);
        g[a].push_back((Edge){b, c});
        g[b].push_back((Edge){a, c});
    }
    for(int i = 1, a; i <= k; i++)
        scanf("%d", &a), cnt[a] = 1;
    dfs1(1, 0); dfs2(1, 0);
    for(int i = 1; i <= n; i++)
        printf("%lld\n", f[i] - maxl[i]);
    return 0;
}