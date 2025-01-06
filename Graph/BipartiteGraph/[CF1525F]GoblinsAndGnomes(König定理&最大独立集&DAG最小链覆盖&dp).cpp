#include <bits/stdc++.h>
using namespace std;

const int N = 110;
const int M = 1e5;

inline int sgn(int x) {
    return x > 0 ? 1 : -1;
}

class Flow {
public:
    struct Edge {
        int v, capa, next;
    } e[M];
    int n1, n2, source, sink, level[N], head[N], cur[N], ecnt;

    void addEdge(int u, int v, int w) {
        e[ecnt] = {v, w, head[u]};
        head[u] = ecnt++;
        e[ecnt] = {u, 0, head[v]};
        head[v] = ecnt++;
    }
    
    void init(int _n1, int _n2) {
        n1 = _n1; n2 = _n2;
        source = 0; sink = n1 + n2 + 1;
        memset(head, -1, sizeof(head));
        ecnt = 0;
        for(int i = 1; i <= n1; i++) addEdge(source, i, 1);
        for(int i = 1; i <= n2; i++) addEdge(n1 + i, sink, 1);
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
    void decompKonig(vector<int> &indep, vector<int> &key){
        int match = maxFlow();
        for(int i = 1; i <= n1; i++){
            if(level[i] != -1) indep.push_back(i);
            else key.push_back(i);
        }
        for(int i = 1; i <= n2; i++){
            if(level[i + n1] == -1) indep.push_back(-i);
            else key.push_back(-i);
        }
    }
} g;

// 思路：DAG 最小链覆盖 = n - 对应二分图的最大匹配
// “对应二分图” 是指：拆点，出点在左边，入点在右边，连边得到二分图
// 对于第 i 波，要让最小链覆盖 > i，也即是二分图最大匹配 < n-i
// 根据 DM 分解，只要删一个点，就能让最大匹配减一

int n, k, x[N], y[N];
long long dp[N][N];
int pre[N][N];
// dp[i][j]: 当前处理到第 i 波，已经减少了 j 对匹配，已获得的最大收益
// pre[i][j]: 记录 dp[i-1][j-t] -> dp[i][j] 时的 t，以便输出方案

vector<int> getVertices(){
    int m;
    scanf("%d%d%d", &n, &m, &k);
    g.init(n, n);
    for(int i = 1; i <= m; i++){
        int u, v;
        scanf("%d%d", &u, &v);
        g.addEdge(u, v + n, 1);
    }
    vector<int> indep, key;
    g.decompKonig(indep, key);
    return key;
}

int main(){
    auto key = getVertices();
    for(int i = 1; i <= k; i++)
        scanf("%d%d", &x[i], &y[i]);
    memset(dp, -0x3f, sizeof(dp));
    dp[0][0] = 0;
    int p = -1;
    for(int i = 1; i <= k; i++){
        for(int j = 0; j <= key.size(); j++){
            if(key.size() - j >= n - i) continue;
            for(int t = 0; t <= j; t++)
                if(dp[i - 1][j - t] + max(0ll, x[i] - 1ll * t * y[i]) >= dp[i][j]){
                    dp[i][j] = dp[i - 1][j - t] + max(0ll, x[i] - 1ll * t * y[i]);
                    pre[i][j] = t;
                }
            if(i == k && (p == -1 || dp[i][j] > dp[i][p])) p = j;
        }
    }
    assert(p != -1 && p <= key.size());
    printf("%d\n", p + k);
    vector<int> cnt(k + 1);
    for(int i = k; i >= 1; i--){
        cnt[i] = pre[i][p];
        p -= pre[i][p];
    }
    assert(p == 0);
    for(int i = 1; i <= k; i++){
        for(int j = 0; j < cnt[i]; j++)
            printf("%d ", key[p++]);
        printf("0%c", " \n"[i == k]);
    }
    return 0;
}