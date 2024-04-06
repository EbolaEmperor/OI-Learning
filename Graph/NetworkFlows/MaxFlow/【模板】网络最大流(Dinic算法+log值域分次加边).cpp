#include <bits/stdc++.h>
using namespace std;

const int N = 1205;
const int M = 240010;

struct EdgeStore{
    int u, v, w;
    bool operator < (const EdgeStore& rhs) const{
        return w > rhs.w;
    }
} es[M];

struct Edge{
    int v, w, flow;
} e[M];
vector<int> g[N];
int cur[N], tot = 0, n, m, s, t;
int dep[N];

void add_edge(int u, int v, int w){
    e[tot].v = v;
    e[tot].w = w;
    e[tot].flow = 0;
    tot++;
}

int dfs(int u, int maxflow){
    // 多路增广, u 是当前节点, maxflow 是当前路径的瓶颈流量
    if(u == t) return maxflow;
    int flow = 0, i;
    for(int &j = cur[u]; j < g[u].size(); ++j){
        i = g[u][j];
        if(dep[e[i].v] == dep[u] + 1){
            if(e[i].flow < e[i].w){
                int a = dfs(e[i].v, min(maxflow, e[i].w-e[i].flow));
                flow += a;
                maxflow -= a;
                e[i].flow += a;
                e[i^1].flow -= a;
                if(maxflow == 0) break;
            }
        }
    }
    return flow;
}

bool bfs(){
    // 返回值表示残量网络中 s 能否到达 t
    memset(dep, 0, sizeof(dep));
    queue<int> q;
    dep[s] = 1;
    q.push(s);
    while(!q.empty()){
        int u = q.front(); q.pop();
        for(int i : g[u]){
            if(e[i].flow >= e[i].w || dep[e[i].v]) continue;
            dep[e[i].v] = dep[u] + 1;
            q.push(e[i].v);
        }
    }
    return dep[t] != 0;
}

int Dinic(){
    int ans = 0;
    while(bfs()){
        memset(cur, 0, sizeof(cur));
        ans += dfs(s, 0x7fffffff);
    }
    return ans;
}

int main(){
    scanf("%d%d%d%d", &n, &m, &s, &t);
    for(int i = 1; i <= m; i++){
        scanf("%d%d%d", &es[i].u, &es[i].v, &es[i].w);
    }
    sort(es + 1, es + 1 + m);
    int p = 1;
    int ans = 0;

    for(int c = 30; c >= 0; c--){
        while(p <= m && es[p].w >= (1<<c)){
            add_edge(es[p].u, es[p].v, es[p].w);
            g[es[p].u].push_back(tot - 1);
            add_edge(es[p].v, es[p].u, 0);
            ++p;
        }
        ans += Dinic();
        if(p > m) break;
    }

    for(int c = 30; c >= 0; c--){
        for(int i = 1; i < tot; i += 2)
            if(e[i^1].w > (1<<c)) g[e[i^1].v].push_back(i);
        ans += Dinic();
    }

    cout << ans << endl;
    return 0;
}
