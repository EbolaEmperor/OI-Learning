#include <bits/stdc++.h>
using namespace std;

const int N = 2010, M = 10010;
// dp[u][j]: 在子树 u 内做了 j 次操作，除点 u 外均已合法，此时点 u 的钱数最多是多少
int dp[N][N];
int d[N], n, siz[N], hson[N];
vector<int> g[N];

void dfs1(int u, int fa){
    siz[u] = 1;
    for(int v : g[u]){
        if(v == fa) continue;
        dfs1(v, u);
        if(!hson[u] || siz[v] > siz[hson[u]]) hson[u] = v;
        siz[u] += siz[v];
    }
}

inline void upmax(int &x, const int &y){
    if(y > x) x = y;
}

void dfs2(int u, int fa){
    if(g[u].size() == 1 && u != 1)
        dp[u][0] = d[u]; // 叶子
    if(hson[u]){
        int v = hson[u];
        dfs2(v, u);
        for(int j = 0; j < siz[v]; j++){
            upmax(dp[u][j + 1], dp[v][j] + d[u]);
            if(dp[v][j] >= 0) upmax(dp[u][j], d[u]);
        }
    }
    for(int v : g[u]){
        if(v == fa || v == hson[u]) continue;
        dfs2(v, u);
        static int tmp[N];
        memcpy(tmp, dp[u], sizeof(tmp));
        memset(dp[u], -0x3f, sizeof(dp[u]));
        for(int j = 0; j < siz[u]; j++)
            for(int k = 0; k < siz[v] && j + k <= siz[u]; k++){
                upmax(dp[u][j + k + 1], tmp[j] + dp[v][k]);
                if(dp[v][k] >= 0) upmax(dp[u][j + k], tmp[j]);
            }
    }
}

int main(){
    int x;
    scanf("%d%d", &n, &x);
    for(int i = 1; i <= n; i++)
        scanf("%d", d + i), d[i] = x - d[i];
    for(int i = 1, u, v; i < n; i++){
        scanf("%d%d", &u, &v);
        g[u].push_back(v);
        g[v].push_back(u);
    }
    memset(dp, -0x3f, sizeof(dp));
    dfs1(1, 0);
    dfs2(1, 0);
    int ans = 0;
    while(dp[1][ans] < 0) ans++;
    cout << ans << endl;
    return 0;
}