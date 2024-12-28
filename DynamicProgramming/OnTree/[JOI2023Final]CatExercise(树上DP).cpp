#include <bits/stdc++.h>
using namespace std;

const int N = 2e5 + 5;
int top[N], hson[N], sz[N], dep[N], trfa[N];
int fa[N], a[N], n;
long long dp[N];
vector<int> g[N];

int find(int x){
    return fa[x] == x ? x : fa[x] = find(fa[x]);
}

void dfs1(int u, int p){
    sz[u] = 1;
    for(int v : g[u]){
        if(v == p) continue;
        dep[v] = dep[u] + 1;
        trfa[v] = u;
        dfs1(v, u);
        sz[u] += sz[v];
        if(sz[v] > sz[hson[u]]) hson[u] = v;
    }
}

void dfs2(int u, int p){
    if(hson[u]){
        top[hson[u]] = top[u];
        dfs2(hson[u], u);
    }
    for(int v : g[u]){
        if(v == p || v == hson[u]) continue;
        top[v] = v;
        dfs2(v, u);
    }
}

int lca(int u, int v){
    while(top[u] != top[v]){
        if(dep[top[u]] < dep[top[v]]) swap(u, v);
        u = trfa[top[u]];
    }
    return dep[u] < dep[v] ? u : v;
}

inline int dis(int u, int v){
    return dep[u] + dep[v] - 2 * dep[lca(u, v)];
}

int main(){
    scanf("%d", &n);
    for(int i = 1; i <= n; i++){
        scanf("%d", &a[i]);
        fa[i] = i;
    }
    for(int i = 1; i < n; i++){
        int u, v;
        scanf("%d%d", &u, &v);
        g[a[u]].push_back(a[v]);
        g[a[v]].push_back(a[u]);
    }
    dep[1] = 1;
    dfs1(1, 0);
    dfs2(1, 0);
    for(int u = 1; u <= n; u++){
        for(int v : g[u]){
            v = find(v);
            if(v > u) continue;
            dp[u] = max(dp[u], dp[v] + dis(u, v));
            fa[v] = u;
        }
    }
    cout << dp[n] << endl;
    return 0;
}