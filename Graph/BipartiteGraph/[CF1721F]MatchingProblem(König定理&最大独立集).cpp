#include <bits/stdc++.h>
using namespace std;

const int N = 4e5 + 5;
const int M = 1.2e6 + 5;

inline int sgn(int x) {
    return x > 0 ? 1 : -1;
}

class Flow {
public:
    struct Edge {
        int v, capa, next;
    } e[M];
    int n1, n2, source, sink, level[N], head[N], cur[N], ecnt;
    
    void init(int _n1, int _n2) {
        n1 = _n1; n2 = _n2;
        source = 0; sink = n1 + n2 + 1;
        memset(head, -1, sizeof(head));
        ecnt = 0;
    }

    void addEdge(int u, int v, int w) {
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
        return flow;
    }

    // Konig 分解：将点集划分成 最大独立集 + 最小点覆盖集
    void decompKonig(vector<int> &indep, vector<int> &key, int *reIndex){
        int match = maxFlow();
        for(int i = 1; i <= n1; i++){
            if(level[i] != -1){
                indep.push_back(i);
                reIndex[i] = -indep.size();
            } else {
                key.push_back(i);
                reIndex[i] = key.size();
            }
        }
        for(int i = 1; i <= n2; i++){
            if(level[i + n1] == -1){
                indep.push_back(-i);
                reIndex[i + n1] = -indep.size();
            } else {
                key.push_back(-i);
                reIndex[i + n1] = key.size();
            }
        }
    }
};

int main(){
    int n1, n2, m, q;
    map<pair<int,int>, int> edgeIndex;
    scanf("%d %d %d %d", &n1, &n2, &m, &q);
    Flow g;
    g.init(n1, n2);
    for(int i = 1; i <= m; i++){
        int u, v;
        scanf("%d %d", &u, &v);
        edgeIndex[{u, -v}] = i;
        g.addEdge(u, v + n1, 1);
    }
    for(int i = 1; i <= n1; i++){
        g.addEdge(g.source, i, 1);
    }
    for(int i = 1; i <= n2; i++){
        g.addEdge(i + n1, g.sink, 1);
    }

    vector<int> indep, key;
    static int reIndex[N];
    g.decompKonig(indep, key, reIndex);
    // for(int x : key) printf("%d%c", x, " \n"[x == key.back()]);
    // for(int x : indep) printf("%d%c", x, " \n"[x == indep.back()]);

    Flow g2;
    g2.init(key.size(), indep.size());
    for(int u = 1; u <= n1; u++){
        for(int i = g.head[u]; ~i; i = g.e[i].next){
            int v = g.e[i].v;
            if(v > n1 && sgn(reIndex[u]) != sgn(reIndex[v])){
                int x = reIndex[u] > 0 ? reIndex[u] : key.size() - reIndex[u];
                int y = reIndex[v] > 0 ? reIndex[v] : key.size() - reIndex[v];
                if(x > y) swap(x, y);
                g2.addEdge(x, y, 1);
            }
        }
    }
    for(int i = 1; i <= key.size(); i++){
        g2.addEdge(g2.source, i, 1);
    }
    for(int i = 1; i <= indep.size(); i++){
        g2.addEdge(i + key.size(), g2.sink, 1);
    }
    assert(g2.maxFlow() == key.size());

    vector<int> matchEdge(key.size() + 1, -1);
    vector<long long> indexSum(key.size() + 1, 0);
    for(int i = 1; i <= key.size(); i++){
        for(int j = g2.head[i]; ~j; j = g2.e[j].next){
            int v = g2.e[j].v;
            if(v > key.size() && g2.e[j].capa == 0){
                int x = key[i - 1], y = indep[v - key.size() - 1];
                if(x < 0) swap(x, y);
                assert(edgeIndex.count({x, y}));
                matchEdge[i] = edgeIndex[{x, y}];
                break;
            }
        }
        assert(matchEdge[i] != -1);
        // printf("%d%c", matchEdge[i], " \n"[i == key.size()]);
        indexSum[i] = indexSum[i - 1] + matchEdge[i];
    }

    int cnt = key.size();
    while(q--){
        int x;
        scanf("%d", &x);
        if(x == 1){
            printf("1\n");
            printf("%d\n", key[cnt - 1]);
            printf("%lld\n", indexSum[--cnt]);
        } else {
            printf("%d\n", cnt);
            for(int i = 1; i <= cnt; i++){
                printf("%d ", matchEdge[i]);
            }
            printf("\n");
        }
        // printf("===\n");
        fflush(stdout);
    }
    return 0;
}