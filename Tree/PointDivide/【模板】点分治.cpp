#include <bits/stdc++.h>
using namespace std;

const int N = 40010, Q = 105, M = 1e7 + 5;
int n, done[N];
vector<pair<int, int>> G[N];
int root = 0, sum = 0, sz[N], mxsz[N];
bool exist[M], qans[Q];
int q, qk[Q];

void dfs(int u, int fa, int dis, vector<int> &a) {
    if(dis > 1e7) return;
    a.push_back(dis);
    for(auto [v, w] : G[u]) {
        if(done[v] || v == fa) continue;
        dfs(v, u, dis + w, a);
    }
}

void upans(int u) {
    vector<int> alldis;
    alldis.push_back(0);
    exist[0] = 1;
    for(auto [v, w] : G[u]) {
        if(done[v]) continue;
        int cur = alldis.size();
        dfs(v, u, w, alldis);
        for(int i = 1; i <= q; i++) {
            if(qans[i]) continue;
            for(int j = cur; j < alldis.size(); j++) {
                int x = alldis[j];
                if(x > qk[i]) continue;
                if(exist[qk[i] - x]) {
                    qans[i] = 1;
                    break;
                }
            }
        }
        for(int i = cur; i < alldis.size(); i++)
            exist[alldis[i]] = 1;
    }
    for(int x : alldis) exist[x] = 0;
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
    upans(u);
    for(auto [v, w] : G[u]) {
        if(done[v]) continue;
        root = -1;
        sum = sz[v];
        findroot(v, 0);
        solve(root);
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin >> n >> q;
    for(int i = 1; i < n; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        G[u].emplace_back(v, w);
        G[v].emplace_back(u, w);
    }
    for(int i = 1; i <= q; i++) cin >> qk[i];
    root = -1; sum = n;
    findroot(1, 0); solve(root);
    for(int i = 1; i <= q; i++)
        puts(qans[i] ? "AYE" : "NAY");
    return 0;
}