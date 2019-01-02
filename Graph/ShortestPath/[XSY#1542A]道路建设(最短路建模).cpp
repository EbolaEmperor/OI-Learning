#include<bits/stdc++.h>
using namespace std;

typedef long long LL;
const int N=2010;
int G[N][N],n;
LL dis[N];
bool vis[N];

void dijkstra(int n,int s)
{
    memset(dis,0x3f,sizeof(dis));
    dis[s]=0;
    for(int i=1;i<=n;i++)
    {
        int u=0;
        for(int j=1;j<=n;j++)
            if(!vis[j]&&(!u||dis[j]<dis[u])) u=j;
        vis[u]=1;
        for(int j=1;j<=n;j++)
            dis[j]=min(dis[j],dis[u]+G[u][j]);
    }
}

int main()
{
    scanf("%d",&n);
    int minw=INT_MAX;
    for(int i=1;i<=n;i++)
        for(int j=i+1;j<=n;j++)
        {
            scanf("%d",G[i]+j);
            G[j][i]=G[i][j];
            minw=min(minw,G[i][j]);
        }
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++)
            if(i!=j) G[i][j]-=minw;
    for(int i=1;i<=n;i++)
    {
        int minv=INT_MAX;
        for(int j=1;j<=n;j++)
            if(i!=j) minv=min(minv,G[i][j]);
        G[i][n+1]=G[n+1][i]=minv*2;
    }
    dijkstra(n+1,n+1);
    for(int i=1;i<=n;i++)
        printf("%lld\n",dis[i]+(LL)minw*(n-1));
    return 0;
}