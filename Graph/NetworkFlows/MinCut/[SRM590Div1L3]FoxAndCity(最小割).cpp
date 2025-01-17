#include <bits/stdc++.h>
using namespace std;

const int L = 45;
const int N = L * L, M = N * N;
const int inf = 0x3f3f3f3f;

class Flow {
public:
    struct Edge {
        int v, capa, next;
    } e[M];
    int n, source, sink, level[N], head[N], cur[N], ecnt;

    void init(int _n) {
        n = _n;
        source = 0; sink = n + 1;
        memset(head, -1, sizeof(head));
        ecnt = 0;
    }

    void addEdge(int u, int v, int w, int antiw = 0) {
        e[ecnt] = {v, w, head[u]};
        head[u] = ecnt++;
        e[ecnt] = {u, antiw, head[v]};
        head[v] = ecnt++;
    }

    bool bfs() {
        memset(level, -1, sizeof(level));
        queue<int> q;
        q.push(source);
        level[source] = 0;
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            for (int i = head[u]; ~i; i = e[i].next) {
                int v = e[i].v;
                if (level[v] == -1 && e[i].capa > 0) {
                    level[v] = level[u] + 1;
                    q.push(v);
                }
            }
        }
        return level[sink] != -1;
    }

    int dfs(int u, int a) {
        if(u == sink || a == 0) return a;
        int flow = 0, f;
        for (int &i = cur[u]; ~i; i = e[i].next) {
            int v = e[i].v;
            if (level[v] == level[u] + 1 && (f = dfs(v, min(a, e[i].capa))) > 0) {
                e[i].capa -= f;
                e[i ^ 1].capa += f;
                flow += f;
                a -= f;
                if (a == 0) break;
            }
        }
        return flow;
    }

    int maxFlow() {
        int flow = 0;
        while (bfs()) {
            memcpy(cur, head, sizeof(head));
            flow += dfs(source, INT_MAX);
        }
        return flow;
    }

    int minCut() {return maxFlow();}

    void printEdge(){
        for(int u = 0; u <= n + 1; u++)
            for(int i = head[u]; ~i; i = e[i].next)
                if(e[i].capa) cout << u << " " << e[i].v << " " << e[i].capa << endl;
    }
} g;

int n, want[L], dis[L];
char G[L][L];

void bfs(){
    memset(dis, -1, sizeof(dis));
    queue<int> q;
    q.push(1);
    dis[1] = 0;
    while(!q.empty()){
        int u = q.front(); q.pop();
        for(int v = 1; v <= n; v++)
            if(G[u][v] == 'Y' && dis[v] == -1){
                dis[v] = dis[u] + 1;
                q.push(v);
            }
    }
    for(int i = 1; i <= n; i++)
        assert(dis[i] != -1);
}

void read(){
    // 以下文件读写用于 2025 青岛寒假集训 Contest 1
    // freopen("westeros.in", "r", stdin);
    // freopen("westeros.out", "w", stdout);
    scanf("%d", &n);
    for(int i = 1; i <= n; i++)
        scanf("%s", G[i] + 1);
    for(int i = 1; i <= n; i++)
        scanf("%d", want + i);
}

inline int idx(int i, int d){
    return (i - 1) * n + d + 1;
}

inline int sqr(int x){
    return x * x;
}

void build(){
    g.init(n * n);
    for(int i = 1; i <= n; i++){
        if(i > 1) g.addEdge(g.source, idx(i, 0), inf);
        for(int d = 1; d <= n - 1; d++){
            g.addEdge(idx(i, d - 1), idx(i, d), 
                      ((d > dis[i]) ? inf : sqr(d - want[i])), inf);
        }
        g.addEdge(idx(i, n - 1), g.sink, inf);
    }
    for(int i = 1; i <= n; i++)
        for(int j = 1; j <= n; j++)
            if(G[i][j] == 'Y'){
                for(int d = 1; d <= n - 1; d++)
                    // 如果 dis'[j] <= d 为 false，则 dis'[i] <= d-1 必为 false
                    g.addEdge(idx(j, d), idx(i, d - 1), inf);
            }
    // g.printEdge();
}

int main(){
    read();
    bfs();
    build();
    cout << g.minCut() << endl;
    return 0;
}