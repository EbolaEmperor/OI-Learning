#include <bits/stdc++.h>
using namespace std;

const int mod = 998244353;
const int N = 200010;
int n, s, t, k[N], b[N], x[N];
vector<int> G[N];

int inv(int a, int b = mod - 2) {
    int ans = 1;
    for(; b; b >>= 1, a = 1LL * a * a % mod)
        if(b & 1) ans = 1LL * ans * a % mod;
    return ans;
}

// 把方程消成 x[u] = k[u] * x[fa[u]] + b[u] 的形式
void push_up(int u, int fa) {
    b[u] = (u == s || u == t);
    k[u] = 1;
    for(int v : G[u]) {
        if(v == fa) continue;
        push_up(v, u);
        if (u != t) {
            // 写一个特判，因为 x[t] = 1 是已知的
            int tmp = inv(G[v].size());
            // 当前方程形式: k[u] * x[u] = inv(deg[fa]) * x[fa] + b[u]
            // 现在右边加入: inv(deg[v]) * (k[v] * x[u] + b[v])
            // 维护系数 k[u] 以及常数 b[u]
            k[u] = (k[u] - 1LL * k[v] * tmp % mod + mod) % mod;
            b[u] = (b[u] + 1LL * b[v] * tmp % mod) % mod;
        }
    }
    if(fa) {
        // 现在得到了 k[u] * x[u] = inv(deg[fa]) * x[fa] + b[u] 的形式
        // 要把它变成 x[u] = k[u] * x[fa] + b[u]
        int iku = inv(k[u]);
        b[u] = 1LL * b[u] * iku % mod;
        // 注意 fa == t 的特判
        k[u] = (fa == t) ? 0 : 1LL * inv(G[fa].size()) * iku % mod;
    }
}

// 已知 x[root] = b[root], 一路向下代入求解
void push_down(int u, int fa) {
    x[u] = (1LL * k[u] * x[fa] + b[u]) % mod;
    for(int v : G[u])
        if(v != fa) push_down(v, u);
}

int main(){
    cin >> n >> s >> t;
    for(int i = 1, u, v; i < n; i++) {
        cin >> u >> v;
        G[u].push_back(v);
        G[v].push_back(u);
    }
    push_up(t, 0);
    push_down(t, 0);
    for(int i = 1; i <= n; i++) cout << x[i] << " ";
    return 0;
}