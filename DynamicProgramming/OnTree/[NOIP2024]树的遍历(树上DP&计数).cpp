#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;

const int N = 100010;
const int ha = 1e9 + 7;
int fac[N], inv[N];
int f[N], deg[N];
struct Edge{
    int v, next;
    bool red;
} e[N << 1];
int h[N], sum;
int ans;

void add_edge(int u, int v){
    e[++sum] = (Edge){v, h[u], false}; h[u] = sum;
    e[++sum] = (Edge){u, h[v], false}; h[v] = sum;
}

void init(){
    fac[0] = 1;
    for(int i = 1; i < N; i++)
        fac[i] = (long long) fac[i-1] * i % ha;
    inv[0] = inv[1] = 1;
    for(int i = 2; i < N; i++)
        inv[i] = ha - (long long) (ha / i) * inv[ha % i] % ha;
}

void dfs(int u, int fa, bool red){
    long long c = inv[deg[u] - 1], s = red;
    for(int i = h[u]; ~i; i = e[i].next){
        int v = e[i].v;
        if(v == fa) continue;
        dfs(v, u, e[i].red);
        int fv = e[i].red ? 1 : f[v];
        f[u] = (f[u] + c * fv) % ha;
        ans = (ans - s * fv % ha * c % ha + ha) % ha;
        s = (s + fv) % ha;
    }
}

int work(){
    int n, k;
    scanf("%d%d", &n, &k);
    sum = -1;
    memset(h, -1, sizeof(int) * (n + 1));
    for(int i = 1, u, v; i < n; i++){
        scanf("%d%d", &u, &v);
        ++deg[u]; ++deg[v];
        add_edge(u, v);
    }
    ans = k;
    for(int i = 1, x; i <= k; i++){
        scanf("%d", &x); --x;
        e[x<<1].red = e[x<<1|1].red = true;
    }
    dfs(1, 0, 0);
    for(int i = 1; i <= n; i++)
        ans = (long long) ans * fac[deg[i] - 1] % ha;
    memset(f, 0, sizeof(int) * (n + 1));
    memset(deg, 0, sizeof(int) * (n + 1));
    return ans;
}

int main(){
    init();
    int c, T;
    scanf("%d%d", &c, &T);
    while(T--)
        cout << work() << endl;
    return 0;
}