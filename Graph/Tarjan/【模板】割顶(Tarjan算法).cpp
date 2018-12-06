#include<bits/stdc++.h>
using namespace std;

const int N=20010;
struct Edge{int to,next;} e[N*10];
int h[N],sum=0,n,m,child;
int dfn[N],low[N],dfc=0;
bool cut[N];

void add_edge(int u,int v)
{
    e[++sum].to=v;
    e[sum].next=h[u];
    h[u]=sum;
}

void dfs(int u,int root)
{
    dfn[u]=low[u]=++dfc;
    for(int t=h[u];t;t=e[t].next)
    {
        int v=e[t].to;
        if(!dfn[v])
        {
            dfs(v,root);
            low[u]=min(low[u],low[v]);
            if(u==root) child++;
            else if(low[v]>=dfn[u]) cut[u]=1;
        }
        else low[u]=min(low[u],dfn[v]);
    }
    if(u==root&&child>1) cut[u]=1;
}

int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1,u,v;i<=m;i++)
    {
        scanf("%d%d",&u,&v);
        add_edge(u,v);
        add_edge(v,u);
    }
    for(int i=1;i<=n;i++)
        if(!dfn[i]) child=0,dfs(i,i);
    int ans=0;
    for(int i=1;i<=n;i++) ans+=cut[i];
    printf("%d\n",ans);
    for(int i=1;i<=n;i++)
        if(cut[i]) printf("%d ",i);
    return 0;
}