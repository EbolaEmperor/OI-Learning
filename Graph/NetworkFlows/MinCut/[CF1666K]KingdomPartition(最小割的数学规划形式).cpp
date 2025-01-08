#include <bits/stdc++.h>
#define int long long
using namespace std;

const int N = 2010;
const int M = 10 * N;

class Flow {
public:
    struct Edge {
        int v, capa, next;
    } e[M];
    int n1, n2, source, sink, level[N], head[N], cur[N], ecnt;

    void addEdge(int u, int v, int w) {
        e[ecnt] = {v, w, head[u]};
        head[u] = ecnt++;
        e[ecnt] = {u, w, head[v]};
        head[v] = ecnt++;
    }
    
    void init(int _n1, int _n2) {
        n1 = _n1; n2 = _n2;
        source = 0; sink = n1 + n2 + 1;
        memset(head, -1, sizeof(head));
        ecnt = 0;
    }

    bool bfs() {
        memset(level, -1, sizeof(level));
        queue<int> q;
        q.push(source);
        level[source] = 0;
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            for (int i = head[u]; i >= 0; i = e[i].next) {
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
            flow += dfs(source, LLONG_MAX);
        }
        return flow;
    }

    int minCut(){ return maxFlow(); }

    void getCutSet(bool *inS, int u = -1){
        if(u == -1){
            memset(inS, 0, sizeof(bool) * (n1 + n2 + 2));
            u = source;
        }
        inS[u] = 1;
        for(int i = head[u]; ~i; i = e[i].next)
            if(e[i].capa > 0 && !inS[e[i].v])
                getCutSet(inS, e[i].v);
    }
} g;

int n, m, a, b;
bool inS[N];

signed main(){
    cin >> n >> m >> a >> b;
    g.init(n, n);
    g.addEdge(g.source, a, LLONG_MAX);
    g.addEdge(a + n, g.sink, LLONG_MAX);
    g.addEdge(g.source, b + n, LLONG_MAX);
    g.addEdge(b, g.sink, LLONG_MAX);
    for(int i = 1, u, v, w; i <= m; i++){
        cin >> u >> v >> w;
        g.addEdge(u, v + n, w);
        g.addEdge(u + n, v, w);
    }
    cout << g.minCut() << endl;
    g.getCutSet(inS);
    for(int i = 1; i <= n; i++)
        if(inS[i] && !inS[i + n]) putchar('A');
        else if(!inS[i] && inS[i + n]) putchar('B');
        else putchar('C');
    return puts(""), 0;
}