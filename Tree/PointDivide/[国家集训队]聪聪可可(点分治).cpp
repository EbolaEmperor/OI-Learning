#include <bits/stdc++.h>
using namespace std;

long long gcd(long long a, long long b) {
    return b == 0 ? a : gcd(b, a % b);
}

const int N = 40010;
int n, k, done[N];
vector<pair<int, int>> G[N];
int root = 0, sum = 0, sz[N], mxsz[N];
int cnt[3], tmpcnt[3];
long long ans = 0;

void dfs(int u, int fa, int dis) {
    tmpcnt[dis]++;
    for(auto [v, w] : G[u]) {
        if(done[v] || v == fa) continue;
        dfs(v, u, (dis + w) % 3);
    }
}

void upans(int u) {
    memset(cnt, 0, sizeof(cnt));
    cnt[0] = 1;
    for(auto [v, w] : G[u]){
        if(done[v]) continue;
        memset(tmpcnt, 0, sizeof(tmpcnt));
        dfs(v, u, w % 3);
        for (int i = 0; i < 3; i++)
            ans += 2ll * cnt[i] * tmpcnt[(3 - i) % 3];
        for (int i = 0; i < 3; i++)
            cnt[i] += tmpcnt[i];
    }
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
    cin >> n;
    for(int i = 1; i < n; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        G[u].emplace_back(v, w);
        G[v].emplace_back(u, w);
    }
    root = -1; sum = n;
    findroot(1, 0); solve(root);
    ans += n;
    long long all = 1ll * n * n;
    long long g = gcd(ans, all);
    cout << ans / g << '/' << all / g << endl;
    return 0;
}