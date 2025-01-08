#include <bits/stdc++.h>
#define int long long
using namespace std;

const int N = 2e5 + 5;
const int M = 10 * N;
const int bigM = 1e6;

class Flow {
public:
    struct Edge {
        int v, capa, next;
    } e[M];
    int n1, n2, source, sink, level[N], head[N], cur[N], ecnt, lackflow;
    map<pair<int,int>, int> edmap;

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
        if(edmap.count({u, v})){
            int tmp = edmap[{u, v}];
            e[tmp].capa += w;
            return;
        }
        e[ecnt] = {v, w, head[u]};
        edmap[{u, v}] = ecnt;
        head[u] = ecnt++;
        e[ecnt] = {u, 0, head[v]};
        edmap[{v, u}] = ecnt;
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
            flow += dfs(source, LLONG_MAX);
        }
        return flow + lackflow;
    }

    int minCut() {return maxFlow();}

    void printEdge(){
        for(int u = 0; u <= n1 + n2 + 1; u++)
            for(int i = head[u]; ~i; i = e[i].next)
                if(e[i].capa) cout << u << " " << e[i].v << " " << e[i].capa << endl;
    }
} g;

class DSU{
public:
    vector<int> fa, siz;
    DSU(int n) : fa(n + 1), siz(n + 1){
        iota(fa.begin(), fa.end(), 0);
        fill(siz.begin(), siz.end(), 1);
    }
    int find(int x){
        return fa[x] == x ? x : fa[x] = find(fa[x]);
    }
    bool isRoot(int x){
        return find(x) == x;
    }
    void merge(int x, int y){
        x = find(x); y = find(y);
        if(x == y) return;
        if(siz[x] < siz[y]) swap(x, y);
        fa[y] = x; siz[x] += siz[y];
    }
};

int n, p[N], q[N];

signed main(){
    scanf("%lld", &n);
    DSU dsuP(n), dsuQ(n);
    for(int i = 1; i <= n; i++){
        scanf("%lld", p + i); ++p[i];
        dsuP.merge(i, p[i]);
    }
    for(int i = 1; i <= n; i++){
        scanf("%lld", q + i); ++q[i];
        dsuQ.merge(i, q[i]);
    }
    g.init(n, n);
    int cnt = 0;
    for(int i = 1; i <= n; i++){
        if(dsuP.isRoot(i) && dsuP.siz[i] > 1){
            ++cnt;
            g.addEdge(g.source, i, bigM);
            g.addEdge(i, g.sink, bigM);
        }
        if(dsuQ.isRoot(i) && dsuQ.siz[i] > 1){
            ++cnt;
            g.addEdge(g.source, i + n, bigM);
            g.addEdge(i + n, g.sink, bigM);
        }
    }
    for(int i = 1; i <= n; i++){
        if(p[i] == i && q[i] == i) g.lackflow++;
        else if(p[i] != i && q[i] == i) g.addEdge(g.source, dsuP.find(i), 1); // 拆 p 的代价
        else if(p[i] == i && q[i] != i) g.addEdge(dsuQ.find(i) + n, g.sink, 1); // 拆 q 的代价
        else if(p[i] != q[i]) g.addEdge(dsuQ.find(i) + n, dsuP.find(i), 1); // 都拆的额外代价
        else { // 都留、都拆均有额外代价
            g.addEdge(dsuP.find(i), dsuQ.find(i) + n, 1);
            g.addEdge(dsuQ.find(i) + n, dsuP.find(i), 1);
        }
    }
    cout << n + cnt * bigM - g.minCut() << endl;
    return 0;
}

// 下面也是一种正确的建模方法，它就是把所有的 bigM 边都删掉了，我暂时想不到怎么解释。
// signed main(){
//     scanf("%lld", &n);
//     DSU dsuP(n), dsuQ(n);
//     for(int i = 1; i <= n; i++){
//         scanf("%lld", p + i); ++p[i];
//         dsuP.merge(i, p[i]);
//     }
//     for(int i = 1; i <= n; i++){
//         scanf("%lld", q + i); ++q[i];
//         dsuQ.merge(i, q[i]);
//     }
//     g.init(n, n);
//     int cnt = 0;
//     for(int i = 1; i <= n; i++){
//         if(dsuP.isRoot(i) && dsuP.siz[i] > 1) ++cnt;
//         if(dsuQ.isRoot(i) && dsuQ.siz[i] > 1) ++cnt;
//     }
//     for(int i = 1; i <= n; i++){
//         if(p[i] == i && q[i] == i) g.lackflow++;
//         else if(p[i] != i && q[i] == i) g.addEdge(g.source, dsuP.find(i), 1); // 拆 p 的代价
//         else if(p[i] == i && q[i] != i) g.addEdge(dsuQ.find(i) + n, g.sink, 1); // 拆 q 的代价
//         else if(p[i] != q[i]) g.addEdge(dsuQ.find(i) + n, dsuP.find(i), 1); // 都拆的额外代价
//         else { // 都留、都拆均有额外代价
//             g.addEdge(dsuP.find(i), dsuQ.find(i) + n, 1);
//             g.addEdge(dsuQ.find(i) + n, dsuP.find(i), 1);
//         }
//     }
//     cout << n - g.minCut() << endl;
//     return 0;
// }