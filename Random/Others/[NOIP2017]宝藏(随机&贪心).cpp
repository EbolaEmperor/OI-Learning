#include<bits/stdc++.h>
using namespace std;

typedef long long LL;
const int N=15;
const int INF=0x7f7f7f7f;
int dis[N][N],dep[N],n,m;
LL ans=1ll<<60;

LL work()
{
    int p[N];LL res=0;
    for(int i=1;i<=n;i++) p[i]=i;
    random_shuffle(p+1,p+1+n);
    dep[p[1]]=1;
    for(int i=2;i<=n;i++)
    {
        LL now=1ll<<60;int d;
        for(int j=1;j<i;j++)
        {
            if(dis[p[j]][p[i]]==INF) continue;
            LL tmp=1ll*dep[p[j]]*dis[p[j]][p[i]];
            if(tmp<now) now=tmp,d=dep[p[j]];
        }
        res+=now;dep[p[i]]=d+1;
    }
    return res;
}

int main()
{
    srand(time(0));
    scanf("%d%d",&n,&m);
    memset(dis,0x7f,sizeof(dis));
    for(int i=1,u,v,w;i<=m;i++)
    {
        scanf("%d%d%d",&u,&v,&w);
        dis[u][v]=min(dis[u][v],w);
        dis[v][u]=min(dis[v][u],w);
    }
    for(int i=1;i<=5000;i++)
        ans=min(ans,work());
    printf("%lld\n",ans);
    return 0;
}