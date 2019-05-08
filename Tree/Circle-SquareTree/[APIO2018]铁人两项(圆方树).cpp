#include<bits/stdc++.h>
using namespace std;

typedef long long LL;
const int N=200010;
vector<int> g[N],tr[N];
stack<int> stk;
int dfn[N],low[N],dfc=0;
int n,m,tot,w[N];
LL f[N],h[N],sum[N];
bool vis[N];

void dp(int u,int fa)
{
    vis[u]=1;
    if(w[u]<0) sum[u]=1,h[u]=-1;
    for(int v : tr[u])
    {
        if(v==fa) continue;
        dp(v,u);
        f[u]+=f[v]+sum[u]*h[v]+h[u]*sum[v];
        sum[u]+=sum[v];
        h[u]+=h[v]+sum[v]*w[u];
    }
}

void Tarjan(int u)
{
    stk.push(u);
    dfn[u]=low[u]=++dfc;
    for(int v : g[u])
        if(!dfn[v])
        {
            Tarjan(v);
            if(low[v]>=dfn[u])
            {
                int o;
                w[++tot]=1;
                do{
                    o=stk.top();stk.pop();w[tot]++;
                    tr[o].push_back(tot);
                    tr[tot].push_back(o);
                }while(o!=v);
                tr[u].push_back(tot);
                tr[tot].push_back(u);
            }
            low[u]=min(low[u],low[v]);
        }
        else low[u]=min(low[u],dfn[v]);
}

int main()
{
    scanf("%d%d",&n,&m);tot=n;
    for(int i=1,u,v;i<=m;i++)
    {
        scanf("%d%d",&u,&v);
        g[u].push_back(v);
        g[v].push_back(u);
    }
    for(int i=1;i<=n;i++) w[i]=-1;
    for(int i=1;i<=n;i++)
        if(!dfn[i]) Tarjan(i);
    LL ans=0;
    for(int i=1;i<=tot;i++)
        if(!vis[i]) dp(i,0),ans+=f[i]<<1;
    cout<<ans<<endl;
    return 0;
}