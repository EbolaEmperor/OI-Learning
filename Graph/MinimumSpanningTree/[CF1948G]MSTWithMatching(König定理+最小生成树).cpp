#include <bits/stdc++.h>
using namespace std;

struct Edge{
    int u, v, w;
    bool operator < (const Edge &rhs) const{
        return w < rhs.w;
    }
};

const int N = 20;
int w[N][N], n, m, c, fa[N];
Edge egs[N*N];

int find(int x){return x==fa[x] ? x : fa[x]=find(fa[x]);}

int kruskal(int s){
    int ans = 0, cnt = 0;
    for(int i = 0; i < n; ++i) fa[i] = i;
    for(int i = 0; i < m; ++i){
        auto& e = egs[i];
        if(!(s >> e.u & 1) && !(s >> e.v & 1)) continue;
        int u = find(e.u), v = find(e.v);
        if(u != v) fa[u] = v, ans += e.w, ++cnt;
    }
    return (cnt==n-1) ? ans : 1e9;
}

int main(){
    freopen("gaycows.in", "r", stdin);
    freopen("gaycows.out", "w", stdout);
    scanf("%d%d", &n, &c);
    for(int i = 0; i < n; ++i)
        for(int j = 0; j < n; ++j){
            scanf("%d", w[i] + j);
            if(w[i][j]) egs[m++] = (Edge){i, j, w[i][j]};
        }
    sort(egs, egs + m);
    int ans = 1e9;
    for(int s = 0; s < 1<<n; ++s)
        ans = min(ans, kruskal(s) + __builtin_popcount(s) * c);
    cout << ans << endl;
    return 0;
}