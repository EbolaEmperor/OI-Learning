#include<bits/stdc++.h>
using namespace std;

typedef long long LL;
typedef pair<int,int> pii;
typedef pair<LL,int> pli;
const int N=100010;
struct Edge{int u,v,w;} edg[N*5];
vector<pii> g[N];
priority_queue<pli> pq;
int n,m,k,s,t,vtx[N];

LL dijkstra()
{
    static bool vis[N];
    static LL dis[N];
    memset(dis,0x3f,sizeof(dis));
    memset(vis,0,sizeof(vis));
    dis[s]=0;pq.push(pli(0,s));
    while(!pq.empty())
    {
        int u=pq.top().second;pq.pop();
        if(vis[u]) continue;vis[u]=1;
        for(pli e : g[u])
            if(dis[u]+e.second<dis[e.first])
            {
                dis[e.first]=dis[u]+e.second;
                pq.push(pli(-dis[e.first],e.first));
            }
    }
    return dis[t];
}

int main()
{
    int T;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d%d%d",&n,&m,&k);
        for(int i=0;i<m;i++)
        {
            static int u,v,w;
            scanf("%d%d%d",&u,&v,&w);
            edg[i]={u,v,w};
        }
        s=0;t=n+1;
        for(int i=0;i<k;i++)
            scanf("%d",vtx+i);
        LL ans=INT64_MAX;
        for(int p=0;p<17;p++)
        {
            for(int i=0;i<n+2;i++) g[i].clear();
            for(int i=0;i<m;i++)
                g[edg[i].u].emplace_back(edg[i].v,edg[i].w);
            for(int i=0;i<k;i++)
                if(i>>p&1) g[s].emplace_back(vtx[i],0);
                else g[vtx[i]].emplace_back(t,0);
            ans=min(ans,dijkstra());
            
            for(int i=0;i<n+2;i++) g[i].clear();
            for(int i=0;i<m;i++)
                g[edg[i].u].emplace_back(edg[i].v,edg[i].w);
            for(int i=0;i<k;i++)
                if(i>>p&1) g[vtx[i]].emplace_back(t,0);
                else g[s].emplace_back(vtx[i],0);
            ans=min(ans,dijkstra());
        }
        printf("%lld\n",ans);
    }
    return 0;
}
