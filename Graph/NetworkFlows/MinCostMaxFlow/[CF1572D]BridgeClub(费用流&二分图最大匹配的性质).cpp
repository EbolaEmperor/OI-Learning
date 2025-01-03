#include <bits/stdc++.h>
#define inf 0x3f3f3f3f
using namespace std;

const int N = (1 << 20) + 5;
bool used[N];

namespace MaxCostMaxFlow{
    struct Edge{
        int from, to, cap, next, flow, cost;
        Edge() {}
        Edge(int from, int to, int cap, int next, int flow, int cost): from(from), to(to), cap(cap), next(next), flow(flow), cost(cost){}
    };
    int n, m = 0, s, t;
    int head[N], dis[N], pre[N], avFlow[N];
    bool vis[N];
    Edge edges[5 * N];

    void init(int _n){
        n = _n;
        memset(head, -1, sizeof(head));
    }

    void addEdge(int from, int to, int cap, int cost){
        edges[m] = Edge(from, to, cap, head[from], 0, cost);
        head[from] = m++;
        edges[m] = Edge(to, from, 0, head[to], 0, -cost);
        head[to] = m++;
    }

    bool spfa(int &flow, int &cost){
        memset(dis, 0x3f, sizeof(dis));
        memset(pre, -1, sizeof(pre));
        queue<int> q;
        q.push(s);
        dis[s] = 0;
        avFlow[s] = inf;
        vis[s] = true;
        while(!q.empty()){
            int u = q.front();
            q.pop();
            vis[u] = false;
            for(int i = head[u]; ~i; i = edges[i].next){
                int v = edges[i].to;
                if(edges[i].cap > edges[i].flow && dis[v] > dis[u] + edges[i].cost){
                    dis[v] = dis[u] + edges[i].cost;
                    pre[v] = i;
                    avFlow[v] = min(avFlow[u], edges[i].cap - edges[i].flow);
                    if(!vis[v]){
                        q.push(v);
                        vis[v] = true;
                    }
                }
            }
        }
        if(dis[t] == inf) return false;
        flow += avFlow[t];
        cost += avFlow[t] * dis[t];
        for(int i = t; i != s; i = edges[pre[i]].from){
            edges[pre[i]].flow += avFlow[t];
            edges[pre[i] ^ 1].flow -= avFlow[t];
        }
        return true;
    }

    pair<int, int> maxCostMaxFlow(int _s, int _t){
        s = _s, t = _t;
        int flow = 0, cost = 0;
        while(spfa(flow, cost));
        return {flow, cost};
    }
};

int read(){
    int x = 0, f = 1;
    char ch = getchar();
    while(ch < '0' || ch > '9'){
        if(ch == '-') f = -1;
        ch = getchar();
    }
    while(ch >= '0' && ch <= '9'){
        x = x * 10 + ch - '0';
        ch = getchar();
    }
    return x * f;
}

pair<int, int> fucker[N * 20];

int main(){
    int n = read(), k = read();
    vector<int> a(1 << n), popcnt(1 << n);
    for(int i = 0; i < (1 << n); i++){
        a[i] = read();
        popcnt[i] = popcnt[i >> 1] + (i & 1);
    }
    MaxCostMaxFlow::init(1 << n);

    // 桶排序，取前 2k(n-1) 大的边建图，因为这些边已经足够形成包含 k 条边的最大匹配
    int ecnt = 0;
    for(int i = 0; i < (1 << n); i++){
        if(popcnt[i] & 1) continue;
        for(int j = 0; j < n; j++){
            fucker[ecnt++] = {a[i] + a[i ^ (1 << j)], i * 20 + j};
        }
    }
    int cnt = min(2 * k * n, ecnt);
    nth_element(fucker, fucker + cnt, fucker + ecnt, greater<pair<int, int>>());

    for(int i = 0; i < cnt; i++){
        int x = fucker[i].second;
        int u = x / 20, j = x % 20, v = u ^ (1 << j);
        MaxCostMaxFlow::addEdge(u, v, 1, -fucker[i].first);
        used[u] = used[v] = 1;
    }

    // 建立源点和汇点，利用二进制里 1 的个数把所有点分成两边
    int s = (1 << n), t = s + 1;
    for(int i = 0; i < (1 << n); i++){
        if(!used[i]) continue;
        if(popcnt[i] & 1) MaxCostMaxFlow::addEdge(i, t, 1, 0);
        else MaxCostMaxFlow::addEdge(s, i, 1, 0);
    }

    // 限制匹配不超过 k 对
    int ss = t + 1;
    MaxCostMaxFlow::addEdge(ss, s, k, 0);

    auto [flow, cost] = MaxCostMaxFlow::maxCostMaxFlow(ss, t);
    cout << -cost << endl;
    return 0;
}