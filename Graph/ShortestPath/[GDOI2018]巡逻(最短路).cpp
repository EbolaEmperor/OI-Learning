#include<bits/stdc++.h>
#define FR first
#define SE second
using namespace std;

typedef pair<int,int> pii;
const int INF=0x3f3f3f3f;
const int N=410;
int G[N][N],n,Q;
bool closed[N],vis[N];
pii dis[N][2];

void dijkstra(int s)
{
    for(int i=1;i<=n;i++)
        dis[i][0]=dis[i][1]=pii(INF,0);
    dis[s][0]=dis[s][1]=pii(0,0);
    memset(vis,0,sizeof(vis));
    while(true)
    {
        int u=0;
        for(int i=1;i<=n;i++)
            if(!vis[i]&&!closed[i]&&(!u||dis[i][0].FR<dis[u][0].FR)) u=i;
        if(!u) break;vis[u]=1;
        for(int v=1;v<=n;v++)
        {
            if(G[u][v]==INF) continue;
            for(int k=0;k<2;k++)
            {
                pii tmp(dis[u][k].FR+G[u][v],dis[u][k].SE);
                if(u==s) tmp.SE=v;
                if(tmp.FR<dis[v][0].FR)
                {
                    if(tmp.SE!=dis[v][0].SE)
                        dis[v][1]=dis[v][0];
                    dis[v][0]=tmp;
                }
                else if(tmp.FR<dis[v][1].FR&&tmp.SE!=dis[v][0].SE) dis[v][1]=tmp;
            }
        }
    }
}

int gao(int s)
{
    dijkstra(s);
    int ans=INF;
    for(int i=1;i<=n;i++)
        if(!closed[i]&&i!=s)
            ans=min(ans,dis[i][0].FR+dis[i][1].FR);
    return ans<INF?ans:-1;
}

int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++)
        {
            scanf("%d",G[i]+j);
            if(G[i][j]==-1) G[i][j]=INF;
        }
    int opt,x;
    for(scanf("%d",&Q);Q;Q--)
    {
        scanf("%d%d",&opt,&x);
        if(opt==1) closed[x]^=1;
        else printf("%d\n",gao(x));
    }
    return 0;
}