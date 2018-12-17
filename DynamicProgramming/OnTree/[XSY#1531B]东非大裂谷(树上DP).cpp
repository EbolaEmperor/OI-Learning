#include<bits/stdc++.h>
#define FR first
#define SE second
using namespace std;

typedef long long LL;
typedef pair<LL,LL> pll;
const int N=100010;
vector<int> G[N];
pll f[N],g[N];
LL h[N],w[N],n;

void dfs(int u)
{
    for(int v : G[u]) dfs(v),h[u]+=h[v];
    f[u]=g[u]=pll(w[u],h[u]);
    for(int v : G[u])
    {
        LL rest=h[u]-h[v];
        if(w[u]>=w[v])
        {
            pll pfv(f[v].FR,rest+f[v].SE);
            if(pfv.SE-pfv.FR>f[u].SE-f[u].FR) f[u]=pfv;
        }
        if(w[u]<=w[v])
        {
            pll pgv(g[v].FR,rest+g[v].SE);
            if(pgv.SE+pgv.FR>g[u].SE+g[u].FR) g[u]=pgv;
        }
    }
    h[u]=max(f[u].SE-f[u].FR+w[u],g[u].SE+g[u].FR-w[u]);
}

int main()
{
    scanf("%lld",&n);
    for(int i=1;i<=n;i++)
        scanf("%lld",w+i);
    for(int i=1,u,v;i<n;i++)
    {
        scanf("%d%d",&u,&v);
        G[u].push_back(v);
    }
    dfs(1);
    printf("%lld\n",h[1]);
    return 0;
}