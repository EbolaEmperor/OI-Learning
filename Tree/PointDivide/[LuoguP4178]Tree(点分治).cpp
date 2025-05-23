#include <bits/stdc++.h>
using namespace std;

const int N = 40010;
int n, k, done[N];
vector<pair<int, int>> G[N];
int ans = 0, root = 0, sum = 0, sz[N], mxsz[N];

void dfs(int u, int fa, int dis, vector<int> &a) {
    if(dis > k) return;
    a.push_back(dis);
    for(auto [v, w] : G[u]) {
        if(done[v] || v == fa) continue;
        dfs(v, u, dis + w, a);
    }
}

int getans(int u, int www = 0) {
    int ans_u = 0;
    vector<int> alldis;
    alldis.push_back(www);
    for(auto [v, w] : G[u])
        if(!done[v]) dfs(v, u, www + w, alldis);
    sort(alldis.begin(), alldis.end());
    for (int x : alldis) {
        auto it = upper_bound(alldis.begin(), alldis.end(), k - x);
        ans_u += it - alldis.begin();
	}
    return ans_u;
}

void findroot(int u,int fa) {
    sz[u] = 1;
    mxsz[u] = 0;
    for(auto [v, w] : G[u]) {
        if(v == fa || done[v]) continue;
        findroot(v, u);
        sz[u] += sz[v];
        mxsz[u] = max(mxsz[u], sz[v]);
    }
    mxsz[u] = max(mxsz[u], sum - sz[u]);
    if(root == -1 || mxsz[u] < mxsz[root]) root = u;
}

void solve(int u) {
	done[u] = 1;
	ans += getans(u);
	for(auto [v, w] : G[u]) {
		if(done[v]) continue;
        ans -= getans(v, w);
		root = -1;
		sum = sz[v];
		findroot(v, 0);
		solve(root);
	}
}

int main() {
	ios::sync_with_stdio(0);
	cin >> n;
	for(int i = 1; i < n; i++) {
		int u, v, w;
		cin >> u >> v >> w;
		G[u].emplace_back(v, w);
		G[v].emplace_back(u, w);
	}
	cin >> k;
	root = -1; sum = n;
	findroot(1, 0); solve(root);
	cout << (ans - n) / 2 << endl;
	return 0;
}