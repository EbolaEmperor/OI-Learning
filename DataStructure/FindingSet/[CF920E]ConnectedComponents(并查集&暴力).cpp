#include <iostream>
#include <numeric>
#include <vector>
#include <algorithm>
#include <unordered_map>
using namespace std;

const int N = 200010;
unordered_map<int, bool> g[N];
int n, m, deg[N], fa[N], siz[N];

int find(int x){
    return fa[x] == x ? x : fa[x] = find(fa[x]);
}

void merge(int u, int v){
    u = find(u); v = find(v);
    if(u == v) return;
    fa[u] = v;
    siz[v] += siz[u];
}

int main(){
    cin >> n >> m;
    for(int i = 1, u, v; i <= m; i++){
        cin >> u >> v;
        deg[u]++; deg[v]++;
        g[u][v] = g[v][u] = 1;
    }
    iota(fa + 1, fa + 1 + n, 1);
    for(int i = 1; i <= n; i++) siz[i] = 1;
    // Step 1. 找到度数最小的点 u，将补图中与 u 相邻的点合并入 u
    int u = -1;
    for(int i = 1; i <= n; i++)
        if(u == -1 || deg[i] < deg[u]) u = i;
    for(int i = 1; i <= n; i++)
        if(!g[u].count(i)) merge(i, u);
    // Step 2. 枚举原图与 u 连通的点 v，将补图中与 v 相邻的点合并入 v
    for(auto it : g[u]){
        int v = it.first;
        for(int x = 1; x <= n; x++)
            if(!g[v].count(x)) merge(x, v);
    }
    // Output
    vector<int> s;
    for(int i = 1; i <= n; i++)
        if(fa[i] == i) s.push_back(siz[i]);
    sort(s.begin(), s.end());
    cout << s.size() << endl;
    for(int x : s) cout << x << " ";
    cout << endl;
    return 0;
}