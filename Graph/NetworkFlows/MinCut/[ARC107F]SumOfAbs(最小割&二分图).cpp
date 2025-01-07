#include <bits/stdc++.h>
using namespace std;

const int N = 605;
const int M = 10 * N;
const int inf = 0x3f3f3f3f;

class Flow {
public:
    struct Edge {
        int v, capa, next;
    } e[M];
    int n1, n2, source, sink, level[N], head[N], cur[N], ecnt, lackflow;
    
    void init(int _n1, int _n2) {
        n1 = _n1; n2 = _n2;
        source = 0; sink = n1 + n2 + 1;
        memset(head, -1, sizeof(head));
        ecnt = 0;
        lackflow = 0;
    }

    void addEdge(int u, int v, int w) {
        if(w < 0){
            lackflow += w;
            return;
        }
        e[ecnt] = {v, w, head[u]};
        head[u] = ecnt++;
        e[ecnt] = {u, 0, head[v]};
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
            flow += dfs(source, INT_MAX);
        }
        return flow + lackflow;
    }
} g;

int n, m, a[N], b[N];

int main(){
    cin >> n >> m;
    g.init(n, n);
    for(int i = 1; i <= n; i++) cin >> a[i];
    int sumb = 0;
    for(int i = 1; i <= n; i++){
        cin >> b[i];
        sumb += abs(b[i]);
        if(b[i] < 0) g.addEdge(g.source, i, -2 * b[i]);
        if(b[i] > 0) g.addEdge(i + n, g.sink, 2 * b[i]);
        g.addEdge(i, i + n, a[i] + abs(b[i]));
    }
    for(int i = 1, u, v; i <= m; i++){
        cin >> u >> v;
        g.addEdge(u + n, v, inf);
        g.addEdge(v + n, u, inf);
    }
    cout << sumb - g.maxFlow() << endl;
    return 0;
}

// 下面是另一种最小割建模方式
// int main(){
//     cin >> n >> m;
//     g.init(n, n);
//     int suma = 0;
//     for(int i = 1; i <= n; i++){
//         cin >> a[i];
//         suma += a[i];
//     }
//     for(int i = 1; i <= n; i++){
//         cin >> b[i];
//         g.addEdge(g.source, i, a[i] - b[i]);
//         g.addEdge(i + n, g.sink, a[i] + b[i]);
//         g.addEdge(i, i + n, inf);
//     }
//     for(int i = 1, u, v; i <= m; i++){
//         cin >> u >> v;
//         g.addEdge(u, v + n, inf);
//         g.addEdge(v, u + n, inf);
//     }
//     cout << suma - g.maxFlow() << endl;
//     return 0;
// }