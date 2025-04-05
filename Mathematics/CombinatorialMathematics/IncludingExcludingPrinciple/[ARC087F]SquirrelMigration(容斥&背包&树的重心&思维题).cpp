#include <bits/stdc++.h>
using namespace std;

const int mod = 1e9 + 7;
const int N = 5010, M = N / 2;
vector<int> G[N];
int n, sz[N], maxsz[N], root = 0;
int C[M][M], fac[N], g[N];

void dfs(int u, int p){
    sz[u] = 1;
    maxsz[u] = 0;
    for(int v : G[u]){
        if(v == p) continue;
        dfs(v, u);
        sz[u] += sz[v];
        maxsz[u] = max(maxsz[u], sz[v]);
    }
    maxsz[u] = max(maxsz[u], n - sz[u]);
    if(!root || maxsz[u] < maxsz[root]) root = u;
}

void init_C(){
    fac[0] = 1;
    for(int i = 1; i < N; i++)
        fac[i] = (1LL * fac[i - 1] * i) % mod;
    C[0][0] = 1;
    for(int i = 1; i < M; i++){
        C[i][0] = C[i][i] = 1;
        for(int j = 1; j < i; j++)
            C[i][j] = (C[i - 1][j - 1] + C[i - 1][j]) % mod;
    }
}

int main(){
    cin >> n;
    for(int i = 1; i < n; i++){
        int u, v;
        cin >> u >> v;
        G[u].push_back(v);
        G[v].push_back(u);
    }
    dfs(1, 0);
    dfs(root, 0);
    init_C();
    g[0] = 1;
    int sum = 0;
    for(int v : G[root]){
        for(int i = sum + sz[v]; i >= 0; i--)
            for(int j = max(1, i - sum); j <= i && j <= sz[v]; j++)
                g[i] = (g[i] + 1LL * C[sz[v]][j] * C[sz[v]][j] % mod * fac[j] % mod * g[i - j]) % mod;
        sum += sz[v];
    }
    int ans = 0;
    for(int i = 0; i <= n; i++){
        int tmp = 1LL * g[i] * fac[n - i] % mod;
        if(i & 1) tmp = (mod - tmp) % mod;
        ans = (ans + tmp) % mod;
    }
    cout << ans << endl;
    return 0;
}