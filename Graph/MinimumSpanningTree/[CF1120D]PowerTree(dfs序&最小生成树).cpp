#include <bits/stdc++.h>
using namespace std;

struct Edge{
    int u, v, w, id;
    bool operator < (const Edge &rhs) const{
        return w < rhs.w;
    }
};
vector<Edge> e;

const int N = 200010;
int n, totleaf = 0;
vector<int> g[N];
int weight[N], fa[N];
bool ans[N];
long long answ = 0;
int anscnt = 0;

int find(int x){
    return x == fa[x] ? x : fa[x] = find(fa[x]);
}

void dfs(int u, int fa){
    int dfn = totleaf;
    if(u != 1 && g[u].size() == 1) ++totleaf;
    for(int v : g[u]){
        if(v == fa) continue;
        dfs(v, u);
    }
    e.push_back((Edge){dfn, totleaf, weight[u], u});
}

void kruskal(){
    for(int i = 0; i <= totleaf; ++i) fa[i] = i;
    sort(e.begin(), e.end());
    for(int i = 0, r = 0; i < e.size(); i = r){
        while(r < e.size() && e[i].w == e[r].w) ++r;
        for(int j = i; j < r; ++j){
            int u = find(e[j].u), v = find(e[j].v);
            if(u != v) ans[e[j].id] = true, ++anscnt;
        }
        for(int j = i; j < r; ++j){
            int u = find(e[j].u), v = find(e[j].v);
            if(u != v) fa[u] = v, answ += e[j].w;
        }
    }
}

int main(){
    scanf("%d", &n);
    for(int i = 1; i <= n; ++i)
        scanf("%d", weight + i);
    for(int i = 1; i < n; ++i){
        int u, v;
        scanf("%d%d", &u, &v);
        g[u].push_back(v);
        g[v].push_back(u);
    }
    dfs(1, 0);
    kruskal();
    printf("%lld %d\n", answ, anscnt);
    for(int i = 1; i <= n; ++i)
        if(ans[i]) printf("%d ", i);
    return 0;
}