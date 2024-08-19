#include <bits/stdc++.h>
using namespace std;

typedef long long LL;
const int N = 100010;
struct Edge{
    int v; LL w;
    bool operator < (const Edge &rhs) const{
        return w > rhs.w;
    }
};
vector<Edge> g[N];
struct Edge2{
    int u, v; LL w;
    bool operator < (const Edge2 &rhs) const{
        return w < rhs.w;
    }
};
Edge2 e[N << 1];
int fa[N];
int n, m, k, ptl[N];
bool vis[N];
int p[N];
LL dis[N];

int find(int x){
    return x == fa[x] ? x : fa[x] = find(fa[x]);
}

void dijkstra(){
    memset(dis, 0x3f, sizeof(dis));
    priority_queue<Edge> pq;
    for(int i = 1; i <= k; ++i){
        dis[ptl[i]] = 0;
        p[ptl[i]] = ptl[i];
        pq.push((Edge){ptl[i], 0});
    }
    while(!pq.empty()){
        int u = pq.top().v; pq.pop();
        if(vis[u]) continue;
        vis[u] = 1;
        for(auto eg : g[u])
            if(dis[u] + eg.w < dis[eg.v]){
                dis[eg.v] = dis[u] + eg.w;
                p[eg.v] = p[u];
                pq.push((Edge){eg.v, dis[eg.v]});
            }
    }
}

int main(){
    scanf("%d%d", &n, &m);
    for(int i = 1; i <= m; ++i){
        int u, v, w;
        scanf("%d%d%d", &u, &v, &w);
        g[u].push_back((Edge){v, w});
        g[v].push_back((Edge){u, w});
    }
    scanf("%d", &k);
    for(int i = 1; i <= k; i++)
        scanf("%d", ptl + i);
    dijkstra();
    LL ans = dis[1];
    int ecnt = 0;
    for(int u = 1; u <= n; u++)
        for(auto eg : g[u])
            if(p[u] != p[eg.v]){
                e[++ecnt] = (Edge2){p[u], p[eg.v], dis[u]+eg.w+dis[eg.v]};
            }
    sort(e + 1, e + 1 + ecnt);
    for(int i = 1; i <= n; i++) fa[i] = i;
    for(int i = 1; i <= ecnt; i++){
        if(find(e[i].u) == find(e[i].v)) continue;
        fa[find(e[i].u)] = find(e[i].v);
        ans += e[i].w;
    }
    cout << ans << endl;
    return 0;
}
