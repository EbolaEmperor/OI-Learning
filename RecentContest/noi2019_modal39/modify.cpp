#include<bits/stdc++.h>
using namespace std;

const int N=100010;
struct E{int v,w;};
vector<E> g[N];
int n,q,root;
int dis[N],fa[N],top[N];
int lson[N],mxd[N];
int sum[N],tps[N],idx[N],tot;
int go[20][N];

void getroot(int u,int la)
{
    if(dis[u]>dis[root]) root=u;
    for(auto e : g[u])
    {
        if(e.v==la) continue;
        dis[e.v]=dis[u]+e.w;
        getroot(e.v,u);
    }
}

void dfs1(int u)
{
    mxd[u]=dis[u];
    for(auto e : g[u])
    {
        if(e.v==fa[u]) continue;
        dis[e.v]=dis[u]+e.w;
        fa[e.v]=u;dfs1(e.v);
        if(mxd[e.v]>mxd[u])
            lson[u]=e.v,mxd[u]=mxd[e.v];
    }
}

void dfs2(int u,int tp)
{
    top[u]=tp;
    if(lson[u]) dfs2(lson[u],tp);
    for(auto e : g[u])
        if(e.v!=fa[u]&&e.v!=lson[u])
            dfs2(e.v,e.v);
}

int query(int x,int y)
{
    int m=2*y-1;
    if(m>tot) return sum[tot];
    if(idx[x]<=m) return sum[m];
    int u=x;
    for(int i=17;i>=0;i--)
        if(idx[go[i][u]]>m) u=go[i][u];
    u=fa[top[u]];
    return sum[m]+(mxd[x]-dis[u])-min(sum[m]-sum[m-1],min(mxd[u]-dis[u],dis[u]));
}

int main()
{
    scanf("%d%d",&n,&q);
    for(int i=1,u,v,w;i<n;i++)
    {
        scanf("%d%d%d",&u,&v,&w);
        g[u].emplace_back((E){v,w});
        g[v].emplace_back((E){u,w});
    }
    getroot(1,0);
    dis[root]=0;dfs1(root);
    dfs2(root,root);
    for(int i=1;i<=n;i++) if(top[i]==i) tps[++tot]=i;
    sort(tps+1,tps+1+tot,[](int a,int b){return mxd[a]-dis[fa[a]]>mxd[b]-dis[fa[b]];});
    for(int i=1;i<=tot;i++) idx[tps[i]]=i;
    for(int i=1;i<=tot;i++) sum[i]=sum[i-1]+mxd[tps[i]]-dis[fa[tps[i]]];
    for(int i=1;i<=n;i++) idx[i]=idx[top[i]];
    for(int i=1;i<=n;i++) go[0][i]=fa[top[i]];
    for(int k=1;k<=17;k++)
        for(int i=1;i<=n;i++)
            go[k][i]=go[k-1][go[k-1][i]];
    int x,y,ans=0;
    while(q--)
    {
        scanf("%d%d",&x,&y);
        x=(x+ans-1)%n+1;
        y=(y+ans-1)%n+1;
        ans=query(x,y);
        printf("%d\n",ans);
    }
    return 0;
}