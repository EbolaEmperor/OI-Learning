#include<bits/stdc++.h>
using namespace std;

typedef pair<int,int> pii;
const int N=1010,M=N*10;
vector<int> g[N],nxt[N],tmp;
bool vis1[N],vis2[N],no[N];
int n,m1,m2,fa[N],rt;
vector<pii> lim1,lim2;

void dfs2(int u)
{
    vis2[u]=1;
    tmp.emplace_back(u);
    for(int v : g[u])
        if(!vis1[v]&&!vis2[v]) dfs2(v);
}

void dfs1(int u,int la)
{
    memset(no,0,sizeof(no));
    memset(vis2,0,sizeof(vis2));
    tmp.clear();dfs2(u);
    for(auto pr : lim1)
        if(vis2[pr.first]&&vis2[pr.second])
            no[pr.second]=1;
    for(auto pr : lim2)
        if(vis2[pr.first]&&vis2[pr.second])
            no[pr.first]=1;
    int cur;
    for(int i=1;i<=n;i++)
        if(vis2[i]&&!no[i]){cur=i;break;}
    fa[cur]=la;
    vis1[cur]=1;
    nxt[cur]=tmp;
    for(int v : nxt[cur])
        if(!vis1[v]) dfs1(v,cur);
}

int main()
{
    scanf("%d%d%d",&n,&m1,&m2);
    for(int i=1,u,v;i<=m1;i++)
    {
        scanf("%d%d",&u,&v);
        lim1.emplace_back(pii(u,v));
        g[u].emplace_back(v);
        g[v].emplace_back(u);
        no[v]=1;
    }
    for(int i=1,u,v;i<=m2;i++)
    {
        scanf("%d%d",&u,&v);
        lim2.emplace_back(pii(u,v));
        no[u]=1;
    }
    for(int i=1;i<=n;i++)
        if(!no[i]){rt=i;break;}
    for(int i=1;i<=n;i++)
    {
        if(i==rt) continue;
        g[rt].emplace_back(i);
        g[i].emplace_back(rt);
        lim1.emplace_back(pii(rt,i));
    }
    dfs1(rt,0);
    for(int i=1;i<=n;i++)
        printf("%d ",fa[i]);
    return 0;
}