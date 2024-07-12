#include <bits/stdc++.h>
using namespace std;

struct Edge{int v, w;};
const int N = 100010;
vector<Edge> g[N];
bool vis[N];
int n, m, dis[N];

bool bfs(int s){
	queue<int> q;
	q.push(s); dis[s] = 0; vis[s] = 1;
	while(!q.empty()){
		int u = q.front(); q.pop();
		for(auto& e : g[u])
			if(vis[e.v]){
				if(dis[e.v] != dis[u] + e.w) return false;
			} else {
				dis[e.v] = dis[u] + e.w;
				q.push(e.v);
				vis[e.v] = 1;
			}
	}
	return true;
}

int main(){
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= m; ++i){
		int l, r, c;
		scanf("%d%d%d", &l, &r, &c);
		g[l].push_back((Edge){r, c});
		g[r].push_back((Edge){l, -c});
	}
	for(int i = 1; i <= n; ++i)
		if(!vis[i] && !bfs(i)) return puts("No"), 0;
	puts("Yes");
	return 0;
}