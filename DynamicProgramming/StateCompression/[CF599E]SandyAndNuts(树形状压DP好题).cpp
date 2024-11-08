#include <iostream>
#include <tuple>
using namespace std;
typedef long long LL;

const int N = 13, Q = 100;
int n, m, q;
tuple<int,int> edge[N];
tuple<int,int,int> lca[Q];
int lg2[1<<N];
LL dp[N][1<<N];
// dp[u][S]: 以 u 为根、由集合 S 中所有点构成的子树的方案数

inline int in(int u, int S){return S >> u & 1;}
inline int lowbit(int x){return x & (-x);}

tuple<bool,int> check(int u, int T){
    int v = -1;
    for(int i = 0; i < m; i++){
        auto [a, b] = edge[i];
        if(a == u && in(b, T) || b == u && in(a, T)){
            if(v != -1) return {false, -1};
            v = (a == u) ? b : a;
        } else if(in(a, T) ^ in(b, T)) return {false, -1};
    }
    for(int i = 0; i < q; i++){
        auto [a, b, c] = lca[i];
        if(c == u && in(a, T) && in(b, T)) return {false, -1};
        if(in(c, T) && (!in(a, T) || !in(b, T))) return {false, -1};
    }
    return {true, v};
};

LL solve(){
    for(int S = 0; S < (1 << n); S++)
        for(int u = 0; u < n; u++) if(in(u, S)){
            if(S == (1 << u)) {dp[u][S] = 1; break;}
            int p = lg2[lowbit(S ^ (1 << u))];
            // 为避免因子树顺序导致的重复转移，我们要求 u 的第一棵子树必须包含 p
            for(int T = S & (S - 1); T; T = S & (T - 1))
                if(!in(u, T) && in(p, T)){
                    auto [flag, v] = check(u, T);
                    if(!flag) continue;
                    if(v != -1)
                        dp[u][S] += dp[v][T] * dp[u][S ^ T];
                    else{
                        for(v = 0; v < n; v++)
                            if(in(v, T)) dp[u][S] += dp[v][T] * dp[u][S ^ T];
                    }
                }
        }
    return dp[0][(1 << n) - 1];
}

int main(){
    cin >> n >> m >> q;
    for(int i = 0, a, b; i < m; i++){
        cin >> a >> b;
        edge[i] = make_tuple(a - 1, b - 1);
    }
    for(int i = 0, a, b, c; i < q; i++){
        cin >> a >> b >> c;
        lca[i] = make_tuple(a - 1, b - 1, c - 1);
    }
    for(int k = 0; k < N; k++) lg2[1<<k] = k;
    cout << solve() << endl;
    return 0;
}