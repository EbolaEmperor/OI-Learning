#include <bits/stdc++.h>
using namespace std;

const int N = 500010;
// f[u]: 使 u 一定不叛变的最小 x (等价于可能使 u 叛变的最大 x)
// ans: 使一定不超过 k 个人叛变的最小 x (等价于可能使超过 k 个人叛变的最大 x)
double f[N], ans;
vector<int> son[N];
int sz[N], n, k;

void dfs(int u){
    sz[u] = 1;
    for(int v : son[u])
        dfs(v), sz[u] += sz[v];
    if(sz[u] == 1) f[u] = 1;
    for(int v : son[u])
        f[u] = max(f[u], min(f[v], (double)sz[v] / (sz[u] - 1)));
    if(sz[u] > k)
        ans = max(ans, f[u]);
}

int main(){
    scanf("%d%d", &n, &k);
    for(int i = 2, fa; i <= n; i++)
        scanf("%d", &fa), son[fa].push_back(i);
    dfs(1);
    printf("%.8lf\n", ans);
    return 0;
}