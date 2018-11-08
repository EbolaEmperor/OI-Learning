#include<bits/stdc++.h>
using namespace std;

const int N=10010;
vector<int> g1[N],g2[N];
int n,m,pre[N],low[N],dfc=0;
int scc[N],deg[N],tot=0;
int a[N],val[N],f[N];
stack<int> stk;

void dfs(int u)
{
    stk.push(u);
    pre[u]=low[u]=++dfc;
    for(int i=0;i<g1[u].size();i++)
    {
        int v=g1[u][i];
        if(!pre[v]) dfs(v),low[u]=min(low[u],low[v]);
        else if(!scc[v]) low[u]=min(low[u],pre[v]);
    }
    if(low[u]==pre[u])
    {
        int o;tot++;
        do{
            o=stk.top();
            scc[o]=tot;
            val[tot]+=a[o];
            stk.pop();
        } while(o!=u);
    }
}

void dp(int u)
{
    if(f[u]) return;
    int mx=0;f[u]=val[u];
    for(int i=0;i<g2[u].size();i++)
    {
        int v=g2[u][i];dp(v);
        mx=max(mx,f[v]);
    }
    f[u]+=mx;
}

int main()
{
    int u,v;
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++) scanf("%d",a+i);
    for(int i=1;i<=m;i++)
    {
        scanf("%d%d",&u,&v);
        g1[u].push_back(v);
    }
    for(int i=1;i<=n;i++)
        if(!pre[i]) dfs(i);
    for(int i=1;i<=n;i++)
        for(int j=0;j<g1[i].size();j++)
        {
            int v=g1[i][j];
            if(scc[i]==scc[v]) continue;
            g2[scc[i]].push_back(scc[v]);
        }
    int ans=0;
    for(int i=1;i<=tot;i++)
        if(!f[i]) dp(i),ans=max(ans,f[i]);
    printf("%d\n",ans);
    return 0;
}