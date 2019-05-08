#include<bits/stdc++.h>
using namespace std;

const int INF=0x3f3f3f3f;
const int N=10010;
struct Edge{int v,w;};
struct Node
{
    int u,d,w;
    Node(int _u=0,int _d=0,int _w=0):u(_u),d(_d),w(_w){}
    bool operator < (const Node &b) const{return w>b.w;}
};
vector<Edge> g[N];
bool vis[N][30];
int val[N],dis[N][30];
int qwq,n,m,k,a,b;

int dijkstra()
{
    memset(vis,0,sizeof(vis));
    memset(dis,0x3f,sizeof(dis));
    priority_queue<Node> pq;
    pq.emplace(a,val[a],0);
    dis[a][val[a]+15]=0;
    while(!pq.empty())
    {
        Node tmp=pq.top();pq.pop();
        int u=tmp.u,d=tmp.d;
        if(vis[u][d+15]) continue;
        vis[u][d+15]=1;
        for(auto e : g[u])
            if(d+val[e.v]>=-k&&d+val[e.v]<=k&&dis[u][d+15]+e.w<dis[e.v][d+val[e.v]+15])
            {
                dis[e.v][d+val[e.v]+15]=dis[u][d+15]+e.w;
                pq.emplace(e.v,d+val[e.v],dis[e.v][d+val[e.v]+15]);
            }
    }
    int ans=INF;
    for(int i=-k;i<=k;i++)
        ans=min(ans,dis[b][i+15]);
    return ans<INF?ans:-1;
}

int main()
{
    scanf("%d",&qwq);
    while(qwq--)
    {
        scanf("%d%d%d",&n,&m,&k);
        for(int i=1,x;i<=n;i++)
            scanf("%d",&x),val[i]=(x==1)?1:-1;
        for(int i=1;i<=m;i++)
        {
            static int u,v,w;
            scanf("%d%d%d",&u,&v,&w);
            g[u].push_back({v,w});
            g[v].push_back({u,w});
        }
        scanf("%d%d",&a,&b);
        printf("%d\n",dijkstra());
        for(int i=1;i<=n;i++) g[i].clear();
    }
    return 0;
}