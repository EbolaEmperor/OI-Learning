#include <bits/stdc++.h>
using namespace std;

const int N = 200010;
vector<int> g[N];
int w[N], lson[N], n, k;
long long val[N];
bool istop[N];

void dfs(int u, int fa){
    for(int v : g[u]){
        if(v == fa) continue;
        dfs(v, u);
        if(val[v] > val[lson[u]]){
            istop[lson[u]] = true;
            lson[u] = v;
        } else istop[v] = true;
    }
    val[u] = val[lson[u]] + w[u];
}

int main(){
    scanf("%d%d", &n, &k);
    for(int i = 1; i <= n; i++)
        scanf("%d", w + i);
    for(int i = 1, u ,v; i < n; i++){
        scanf("%d%d", &u, &v);
        g[u].push_back(v);
        g[v].push_back(u);
    }
    istop[1] = true;
    dfs(1, 0);
    vector<long long> ans;
    for(int i = 1; i <= n; i++)
        if(istop[i]) ans.push_back(val[i]);
    sort(ans.begin(), ans.end(), greater<long long>());
    long long sum = 0;
    for(int i = 0; i < min(k, (int)ans.size()); i++)
        sum += ans[i];
    cout << sum << endl;
    return 0;
}