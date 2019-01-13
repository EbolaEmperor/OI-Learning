#include<bits/stdc++.h>
using namespace std;

const int N=510;
int dfn[N],low[N],dfc=0;
int n,m1,m2,val[N],fa[N];
int scc[N],sccn=0,sccv[N];
stack<int> stk;
bool G[N][N],gs[N][N];

int find(int x){return fa[x]==x?x:fa[x]=find(fa[x]);}

void Tarjan(int u)
{
    stk.push(u);
    low[u]=dfn[u]=++dfc;
    for(int v=1;v<=n;v++)
    {
        if(!G[u][v]) continue;
        if(!dfn[v]) Tarjan(v),low[u]=min(low[u],low[v]);
        else if(!scc[v]) low[u]=min(low[u],dfn[v]);
    }
    if(low[u]==dfn[u])
    {
        int o;sccn++;
        do{
            o=stk.top();
            scc[o]=sccn;
            stk.pop();
        }while(o!=u);
    }
}

bool merge()
{
    static vector<int> v[N];
    for(int i=1;i<=sccn;i++) v[i].clear();
    for(int i=1;i<=n;i++)
    {
        int x=find(scc[i]);
        v[x].push_back(val[i]);
    }
    for(int i=1;i<=sccn;i++)
    {
        if(fa[i]!=i) continue;
        sort(v[i].begin(),v[i].end());
        sccv[i]=v[i][v[i].size()/2];
    }
    for(int i=1;i<=sccn;i++)
        if(fa[i]==i)for(int j=1;j<=sccn;j++)
            if(i!=j&&fa[j]==j&&gs[i][j]&&sccv[i]>sccv[j])
            {
                fa[j]=i;
                for(int k=1;k<=sccn;k++)
                {
                    if(gs[j][k]) gs[i][k]=1;
                    if(gs[k][j]) gs[k][i]=1;
                }
                return 1;
            }
    return 0;
}

int main()
{
    scanf("%d%d%d",&n,&m1,&m2);
    for(int i=1;i<=n;i++) scanf("%d",val+i);
    for(int i=1,u,v;i<=m1;i++)
    {
        scanf("%d%d",&u,&v);
        G[u][v]=G[v][u]=1;
    }
    for(int i=1,u,v;i<=m2;i++)
    {
        scanf("%d%d",&u,&v);
        G[u][v]=1;
    }
    for(int i=1;i<=n;i++)
        if(!dfn[i]) Tarjan(i);
    for(int i=1;i<=sccn;i++) fa[i]=i;
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++)
            if(scc[i]!=scc[j]&&G[i][j])
                gs[scc[i]][scc[j]]=1;
    while(merge());
    long long ans=0;
    for(int i=1;i<=n;i++)
        ans+=abs(val[i]-sccv[find(scc[i])]);
    printf("%lld\n",ans);
    return 0;
}