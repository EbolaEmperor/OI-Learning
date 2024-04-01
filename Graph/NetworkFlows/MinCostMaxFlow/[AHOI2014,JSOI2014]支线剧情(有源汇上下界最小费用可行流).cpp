#include <bits/stdc++.h>
using namespace std;

const int N = 310;
const int M = 12000;
const int INF = 1<<29;

struct Edge{
    int v, next;
    int w, flow, cost;
} e[M];
int h[N], cur[N], tot = 0, s, t;
int inflow[N], outflow[N];
int dep[N];
int dis[N];
bool inq[N];
long long ans = 0;

void add_edge_(int u, int v, int f, int w, int c){
    e[tot].v = v;
    e[tot].w = w;
    e[tot].flow = f;
    e[tot].cost = c;
    e[tot].next = h[u];
    h[u] = tot;
    tot++;
}

void add_edge(int u, int v, int l, int r, int c){
    add_edge_(u, v, l, r, c);
    add_edge_(v, u, -l, -l, -c);
    inflow[v] += l;
    outflow[u] += l;
}

bool spfa(){
    memset(dis,0x3f,sizeof(dis));
    queue<int> q;q.push(s);
    inq[s]=1;dis[s]=0;
    while(!q.empty()){
        int u=q.front();
        for(int tmp=h[u];~tmp;tmp=e[tmp].next){
            int v=e[tmp].v;
            if(e[tmp].flow<e[tmp].w && dis[u]+e[tmp].cost<dis[v]){
                dis[v]=dis[u]+e[tmp].cost;
                if(inq[v]) continue;
                inq[v]=1;q.push(v);
            }
        }
        q.pop();inq[u]=0;
    }
    return dis[t]<INF;
}

int dfs(int u,int a)
{
    if(u==t||a==0) return a;
    int flow=0;inq[u]=1;
    for(int &tmp=cur[u];~tmp;tmp=e[tmp].next){
        int v=e[tmp].v;
        if(inq[v]) continue;
        if(dis[u]+e[tmp].cost==dis[v]){
            int f=dfs(v,min(a,e[tmp].w-e[tmp].flow));
            if(!f) continue;
            e[tmp].flow+=f;
            e[tmp^1].flow-=f;
            a-=f;flow+=f;
            ans+=(long long)f*e[tmp].cost;
            if(a==0) break;
        }
    }
    inq[u]=0;
    return flow;
}

int ZkwCostFlow(){
    int flow=0;
    while(spfa()){
        memcpy(cur,h,sizeof(h));
        flow+=dfs(s,INF);
    }
    return flow;
}

int feasible_flow(int my_s, int my_t){
    // link the flow-balance edges
    for(int i = 1; i <= my_t; i++){
        if(inflow[i] > outflow[i])
            add_edge(s, i, 0, inflow[i] - outflow[i], 0);
        if(inflow[i] < outflow[i])
            add_edge(i, t, 0, outflow[i] - inflow[i], 0);
    }
    add_edge(my_t, my_s, 0, INF, 0);

    // compute feasible flow and check
    bool feasible = true;
    return ZkwCostFlow();
}

int main(){
    int n;
    scanf("%d", &n);
    memset(inflow, 0, sizeof(inflow));
    memset(outflow, 0, sizeof(outflow));
    memset(h, -1, sizeof(h));
    tot = 0;

    int my_s = 1;
    int my_t = n + 1;
    s = 0;
    t = my_t + 1;
    int initcost = 0;

    for(int i = 1, K, b, ti; i <= n; i++){
        scanf("%d", &K);
        add_edge(i, my_t, 0, INF, 0);
        for(int j = 1; j <= K; j++){
            scanf("%d%d", &b, &ti);
            add_edge(i, b, 1, INF, ti);
            initcost += ti;
        }
    }

    int flow = feasible_flow(my_s, my_t);
    printf("%lld\n", initcost + ans);
    return 0;
}