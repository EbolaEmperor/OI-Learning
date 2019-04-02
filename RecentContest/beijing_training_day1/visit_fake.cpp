#include<bits/stdc++.h>
#define fr first
#define se second
using namespace std;

typedef long long LL;
typedef pair<int,int> pii;
const LL INF=1e18;
const int N=100010;
vector<pii> g[N];
int n,m,s,t;
LL d1[N],d2[N];
int fa[N],anc[N];

void dijkstra(int s,LL *dis)
{
    static bool vis[N];
    priority_queue<pii> pq;
    memset(vis,0,sizeof(vis));
    memset(dis,0x3f,sizeof(LL)*(n+1));
    pq.push(pii(0,s));dis[s]=0;
    while(!pq.empty())
    {
        int u=pq.top().se;pq.pop();
        if(vis[u]) continue;vis[u]=1;
        for(pii e : g[u])
            if(dis[u]+e.se<dis[e.fr])
            {
                dis[e.fr]=dis[u]+e.se;
                pq.push(pii(-dis[e.fr],e.fr));
            }
    }
}

void build_tree()
{
    queue<int> q;
    for(pii e : g[t])
        if(d2[e.fr]==e.se)
            q.push(e.fr),fa[e.fr]=t,anc[e.fr]=e.fr;
    while(!q.empty())
    {
        int u=q.front();q.pop();
        for(pii e : g[u])
            if(!fa[e.fr]&&d2[e.fr]==d2[u]+e.se)
                fa[e.fr]=u,anc[e.fr]=anc[u],q.push(e.fr);
    }
}

LL gao(int u,int rt)
{
    LL res=INF;
    for(pii e : g[u])
    {
        if(e.fr==fa[u]) continue;
        if(fa[e.fr]==u) res=min(res,gao(e.fr,rt)+e.se);
        else if(anc[e.fr]!=rt) res=min(res,d2[e.fr]+e.se);
    }
    return res;
}

int main()
{
    scanf("%d%d%d%d",&n,&m,&s,&t);
    for(int i=1,u,v,w;i<=m;i++)
    {
        scanf("%d%d%d",&u,&v,&w);
        g[u].emplace_back(v,w);
        g[v].emplace_back(u,w);
    }
    dijkstra(s,d1);
    dijkstra(t,d2);
    build_tree();
    LL ans=INF;
    for(int i=1;i<=n;i++)
        if(fa[i]==t) ans=min(ans,gao(i,i)+d1[i]);
    if(ans==INF) puts("-1");
    else printf("%lld\n",ans);
    return 0;
}