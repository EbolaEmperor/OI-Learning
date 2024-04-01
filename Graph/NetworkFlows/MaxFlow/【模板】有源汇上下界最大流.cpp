// Luogu P5192
#include <bits/stdc++.h>
using namespace std;

const int N = 1400;
const int M = 1001000;
const long long INF = 1ll<<50;

struct Edge{
    int v, next;
    long long w, flow;
} e[M];
int h[N], cur[N], tot = 0, s, t;
int inflow[N], outflow[N];
int dep[N];

void add_edge_(int u, int v, long long f, long long w){
    e[tot].v = v;
    e[tot].w = w;
    e[tot].flow = f;
    e[tot].next = h[u];
    h[u] = tot;
    tot++;
}

void add_edge(int u, int v, long long l, long long r){
    add_edge_(u, v, l, r);
    add_edge_(v, u, -l, -l);
    inflow[v] += l;
    outflow[u] += l;
}

long long dfs(int u, long long maxflow){
    // multi-path augmentation, u : the current node, maxflow : the bottleneck
    if(u == t) return maxflow;
    long long flow = 0;
    for(int &i = cur[u]; i != -1; i = e[i].next)
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
    return flow;
}

bool bfs(){
    // return : whether s can reach t in the residule-net
    memset(dep, 0, sizeof(dep));
    queue<int> q;
    dep[s] = 1;
    q.push(s);
    while(!q.empty()){
        int u = q.front(); q.pop();
        for(int i = h[u]; i != -1; i = e[i].next){
            if(e[i].flow >= e[i].w || dep[e[i].v]) continue;
            dep[e[i].v] = dep[u] + 1;
            q.push(e[i].v);
        }
    }
    return dep[t] != 0;
}

long long Dinic(){
    long long ans = 0;
    while(bfs()){
        memcpy(cur, h, sizeof(h));
        ans += dfs(s, INF);
    }
    return ans;
}

long long max_feasible_flow(int my_s, int my_t){
    // link the flow-balance edges
    for(int i = 1; i <= my_t; i++){
        if(inflow[i] > outflow[i])
            add_edge(s, i, 0, inflow[i] - outflow[i]);
        if(inflow[i] < outflow[i])
            add_edge(i, t, 0, outflow[i] - inflow[i]);
    }
    add_edge(my_t, my_s, 0, INF);

    // compute feasible flow and check
    bool feasible = true;
    long long feasible_flow = Dinic();
    for(int i = h[s]; i != -1; i = e[i].next)
        if(e[i].flow < e[i].w){
            feasible = false;
            break;
        }
    if(!feasible) return -1;

    // delete the edge : t->s (0,inf)
    h[my_s] = e[h[my_s]].next;
    h[my_t] = e[h[my_t]].next;
    tot -= 2;

    // compute the max increasement flow
    s = my_s;
    t = my_t;
    long long incr_flow = Dinic();
    
    return feasible_flow + incr_flow;
}

int main(){
    int n, m;
    while(~scanf("%d%d", &n, &m)){
        memset(inflow, 0, sizeof(inflow));
        memset(outflow, 0, sizeof(outflow));
        memset(h, -1, sizeof(h));
        tot = 0;
        int my_s = n + m + 1;
        int my_t = n + m + 2;
        s = 0;
        t = my_t + 1;
        for(int i = 1, G; i <= m; i++){
            scanf("%d", &G);
            add_edge(n+i, my_t, G, INF);
        }
        for(int i = 1, C, D, T, L, R; i <= n; i++){
            scanf("%d%d", &C, &D);
            add_edge(my_s, i, 0, D);
            for(int j = 1; j <= C; j++){
                scanf("%d%d%d", &T, &L, &R);
                ++T;
                add_edge(i, n+T, L, R);
            }
        }
        printf("%lld\n\n", max_feasible_flow(my_s, my_t));
    }
    return 0;
}
