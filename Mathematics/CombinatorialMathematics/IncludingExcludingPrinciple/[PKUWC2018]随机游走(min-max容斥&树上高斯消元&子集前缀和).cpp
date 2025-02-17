#include <bits/stdc++.h>
#define popcnt __builtin_popcount
using namespace std;

const int ha = 998244353;
const int N = 18, S = 1 << N;
int n, source;
int E[S], SE[S];
int k[N], b[N], f[N], ideg[N];
vector<int> G[N];

int Pow(int a, int b){
    int ans = 1;
    for(; b; b >>= 1, a = 1ll * a * a % ha)
        if(b & 1) ans = 1ll * ans * a % ha;
    return ans;
}

inline void add(int &x, int y){
    x = (x + y >= ha) ? (x + y - ha) : x + y;
}
inline void mns(int &x, int y){
    x = (x - y < 0) ? (x - y + ha) : x - y;
}

void dfs(int u, int fa, int T){
    if((T >> u) & 1){
        k[u] = b[u] = 0;
        return;
    }
    int lhs = 1, rhs = 1;
    for(int v : G[u]){
        if(v == fa) continue;
        dfs(v, u, T);
        mns(lhs, 1ll * k[v] * ideg[u] % ha);
        add(rhs, 1ll * b[v] * ideg[u] % ha);
    }
    lhs = Pow(lhs, ha - 2);
    k[u] = 1ll * ideg[u] * lhs % ha;
    b[u] = 1ll * rhs * lhs % ha;
}

int main(){
    int Q;
    scanf("%d%d%d", &n, &Q, &source);
    --source;
    for(int i = 1, u, v; i < n; i++){
        scanf("%d%d", &u, &v);
        --u; --v;
        G[u].push_back(v);
        G[v].push_back(u);
    }
    for(int i = 0; i < n; i++)
        ideg[i] = Pow(G[i].size(), ha - 2);
    for(int s = 0; s < (1 << n); s++){
        dfs(source, source, s);
        E[s] = b[source];
        if(popcnt(s) & 1) SE[s] = E[s];
        else mns(SE[s], E[s]);
    }
    for(int i = 0; i < n; i++)
        for(int s = 0; s < (1 << n); s++)
            if(s & (1 << i)) add(SE[s], SE[s ^ (1 << i)]);
    while(Q--){
        int s = 0, k, x;
        scanf("%d", &k);
        for(int i = 1; i <= k; i++){
            scanf("%d", &x);
            s |= 1 << (x - 1);
        }
        printf("%d\n", SE[s]);
    }
    return 0;
}