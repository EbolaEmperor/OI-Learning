#include <bits/stdc++.h>
using namespace std;

const int N = 1010;
vector<int> g[N];

int dfs(int u){
    static int f[N];
    if(f[u]) return f[u];
    f[u] = 1;
    for(int v : g[u])
        f[u] = max(f[u], dfs(v) + 1);
    return f[u];
}

int n, k;
int pos[5][N];

int main(){
    scanf("%d%d", &n, &k);
    for(int i = 0, x; i < k; ++i)
        for(int j = 1; j <= n; ++j){
            scanf("%d", &x);
            pos[i][x] = j;
        }
    for(int i = 1; i <= n; ++i)
        for(int j = 1; j <= n; ++j){
            bool can = true;
            for(int s = 0; s < k; ++s)
                if(pos[s][j] <= pos[s][i]) can = false;
            if(can) g[i].push_back(j);
        }
    int ans = 0;
    for(int i = 1; i <= n; ++i)
        ans = max(ans, dfs(i));
    cout << ans << endl;
    return 0;
}