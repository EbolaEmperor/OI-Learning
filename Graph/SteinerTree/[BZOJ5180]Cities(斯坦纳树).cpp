#include<bits/stdc++.h>
using namespace std;

typedef long long LL;
typedef pair<LL,int> pli;
const int N=100010;
const LL INF=0x3f3f3f3f3f3f3f3fLL;
struct Edge{int to,capa,next;} e[N<<2];
int h[N],sum=0,n,m,tot;
priority_queue<pli> q;
bool vis[N];
LL f[35][N];

void add_edge(int u,int v,int w)
{
    e[++sum].to=v;
    e[sum].capa=w;
    e[sum].next=h[u];
    h[u]=sum;
}

void dijkstra(int s)
{
    memset(vis,0,sizeof(vis));
    while(!q.empty())
    {
        int u=q.top().second;q.pop();
        if(vis[u]) continue;vis[u]=1;
        for(int t=h[u];t;t=e[t].next)
        {
            int v=e[t].to;
            if(f[s][u]+e[t].capa<f[s][v])
            {
                f[s][v]=f[s][u]+e[t].capa;
                q.push(pli(-f[s][v],v));
            }
        }
    }
}

int main()
{
    int x,u,v,w;
    scanf("%d%d%d",&n,&tot,&m);
    memset(f,0x3f,sizeof(f));
    for(int i=0;i<tot;i++)
    {
        scanf("%d",&x);
        f[1<<i][x]=0;
    }
    for(int i=1;i<=m;i++)
    {
        scanf("%d%d%d",&u,&v,&w);
        add_edge(u,v,w);
        add_edge(v,u,w);
    }
    for(int s=1;s<(1<<tot);s++)
    {
        for(int i=1;i<=n;i++)
        {
            for(int t=(s-1)&s;t;t=(t-1)&s)
                f[s][i]=min(f[s][i],f[t][i]+f[s^t][i]);
            if(f[s][i]<INF) q.push(pli(-f[s][i],i));
        }
        dijkstra(s);
    }
    LL ans=INF;
    for(int i=1;i<=n;i++)
        ans=min(ans,f[(1<<tot)-1][i]);
    printf("%lld\n",ans);
    return 0;
}