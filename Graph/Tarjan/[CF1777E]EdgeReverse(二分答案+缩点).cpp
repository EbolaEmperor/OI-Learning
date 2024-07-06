#include <bits/stdc++.h>
using namespace std;

const int N = 200010;
struct Edge{int u, v, w;} e[N];
vector<int> g[N];
int n, m;
int dfn[N], low[N], dfc = 0;
int scc[N], cnt = 0;
stack<int> sta;
int indeg[N];

void Tarjan(int u){
	dfn[u] = low[u] = ++dfc;
	sta.push(u);
	for(int v : g[u]){
		if(!dfn[v]) Tarjan(v), low[u] = min(low[u], low[v]);
		else if(!scc[v]) low[u] = min(low[u], dfn[v]);
    }
	if(dfn[u] == low[u]){
		int o; ++cnt;
		do{
			o = sta.top();
			scc[o] = cnt;
			sta.pop();
		}while(o != u);
	}
}

bool check(int x){
    for(int i = 1; i <= n; ++i) g[i].clear();
    for(int i = 1; i <= m; ++i){
        g[e[i].u].push_back(e[i].v);
        if(e[i].w <= x) g[e[i].v].push_back(e[i].u);
    }
    dfc = cnt = 0;
    assert(sta.empty());
    memset(dfn, 0, sizeof(int) * (n+1));
    memset(low, 0, sizeof(int) * (n+1));
    memset(scc, 0, sizeof(int) * (n+1));
    for(int i = 1; i <= n; ++i)
        if(!dfn[i]) Tarjan(i);
    memset(indeg, 0, sizeof(int) * (n+1));
    for(int i = 1; i <= m; ++i){
        int u = e[i].u, v = e[i].v;
        if(scc[u] != scc[v]) ++indeg[scc[v]];
    }
    int zero = 0;
    for(int i = 1; i <= cnt; ++i)
        if(!indeg[i]) ++zero;
    return zero == 1;
}

int main(){
    int t; scanf("%d", &t);
    while(t--){
        scanf("%d%d", &n, &m);
        for(int i = 1; i <= m; ++i)
            scanf("%d%d%d", &e[i].u, &e[i].v, &e[i].w);
        int l = 0, r = 1e9, mid, ans = -1;
        while(l <= r){
            mid = (l + r) / 2;
            if(check(mid)) r = mid - 1, ans = mid;
            else l = mid + 1;
        }
        printf("%d\n", ans);
    }
    return 0;
}