#include <bits/stdc++.h>
using namespace std;

const int N = 1e4 + 5;
const int M = 1e6 + 5;

// 二分图染色（Bipartite Graph Coloring）
namespace BGC{
    struct Edge{
        int to, next;
        Edge(int to = 0, int next = 0): to(to), next(next){}
    } edge[M];
    int head[N], color[N], cnt = 0;

    void addEdge(int u, int v){
        edge[++cnt] = Edge(v, head[u]); head[u] = cnt;
        edge[++cnt] = Edge(u, head[v]); head[v] = cnt;
    }

    bool dfs(int u, int c){
        color[u] = c;
        for(int i = head[u]; i; i = edge[i].next){
            int v = edge[i].to;
            if(color[v] == c) return false;
            if(!color[v] && !dfs(v, 3 - c)) return false;
        }
        return true;
    }
    
    bool solve(int n){
        for(int i = 1; i <= n; i++){
            if(!color[i] && !dfs(i, 1)) return false;
        }
        return true;
    }
}

struct Edge{
    int to, capa, next;
    Edge(int to = 0, int capa = 0, int next = 0): 
        to(to), capa(capa), next(next){}
} edge[M];
int head[N], level[N], cur[N];
int source, sink, n, m;

void addEdge(int u, int v, int c){
    static int cnt = -1;
    edge[++cnt] = Edge(v, c, head[u]); head[u] = cnt;
    edge[++cnt] = Edge(u, 0, head[v]); head[v] = cnt;
}

bool bfs(){
    memset(level, 0, sizeof(level));
    queue<int> q;
    q.push(source);
    level[source] = 1;
    while(!q.empty()){
        int u = q.front(); q.pop();
        for(int i = head[u]; ~i; i = edge[i].next){
            int v = edge[i].to;
            if(edge[i].capa > 0 && !level[v]){
                level[v] = level[u] + 1;
                q.push(v);
            }
        }
    }
    return level[sink];
}

int dfs(int u, int flow){
    if(u == sink || !flow) return flow;
    int f = 0;
    for(int &i = cur[u]; ~i; i = edge[i].next){
        int v = edge[i].to;
        if(edge[i].capa > 0 && level[v] == level[u] + 1){
            int d = dfs(v, min(flow, edge[i].capa));
            if(d > 0){
                f += d; flow -= d;
                edge[i].capa -= d;
                edge[i ^ 1].capa += d;
                if(!flow) break;
            }
        }
    }
    return f;
}

int dinic(){
    int maxFlow = 0;
    while(bfs()){
        memcpy(cur, head, sizeof(head));
        maxFlow += dfs(source, INT_MAX);
    }
    return maxFlow;
}

int dfn[N], dfc = 0, low[N], scc[N];
stack<int> stk;

void tarjan(int u){
    dfn[u] = low[u] = ++dfc;
    stk.push(u);
    for(int i = head[u]; ~i; i = edge[i].next){
        // 因为是求残量网络的 scc，所以要跳过满流边
        if(edge[i].capa == 0) continue;
        int v = edge[i].to;
        if(!dfn[v]){
            tarjan(v);
            low[u] = min(low[u], low[v]);
        }
        else if(scc[v] == -1){
            low[u] = min(low[u], dfn[v]);
        }
    }
    if(dfn[u] == low[u]){
        int v;
        do{
            v = stk.top(); stk.pop();
            scc[v] = u;
        }while(v != u);
    }
}

int main(){
    memset(head, -1, sizeof(head));
    scanf("%d%d", &n, &m);
    source = 0; sink = n + 1;
    for(int i = 1; i <= m; i++){
        int u, v;
        scanf("%d%d", &u, &v);
        BGC::addEdge(u, v);
    }
    assert(BGC::solve(n));
    // 建立二分图匹配的网络流模型
    for(int i = 1; i <= n; i++){
        if(BGC::color[i] == 1){
            addEdge(source, i, 1);
            for(int j = BGC::head[i]; j; j = BGC::edge[j].next){
                int v = BGC::edge[j].to;
                addEdge(i, v, 1);
            }
        }
        else addEdge(i, sink, 1);
    }
    int match = dinic();
    // 寻找非必经的匹配边
    // Step 1. 寻找残量网络上的所有环
    memset(scc, -1, sizeof(scc));
    for(int i = 1; i <= n; i++)
        if(!dfn[i]) tarjan(i);
    // Step 2. 寻找不在残量网络的环里的所有满流边
    vector<pair<int, int>> ans;
    for(int u = 1; u <= n; u++)
        if(BGC::color[u] == 1){
            for(int i = head[u]; ~i; i = edge[i].next)
                if(BGC::color[edge[i].to] == 2 && edge[i].capa == 0 && scc[u] != scc[edge[i].to])
                    ans.emplace_back(min(u, edge[i].to), max(u, edge[i].to));
        }
    sort(ans.begin(), ans.end());
    int m = unique(ans.begin(), ans.end()) - ans.begin();
    printf("%d\n", m);
    for(int i = 0; i < m; i++)
        printf("%d %d\n", ans[i].first, ans[i].second);
    return 0;
}