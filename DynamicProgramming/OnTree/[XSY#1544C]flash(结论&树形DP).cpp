#include<bits/stdc++.h>
using namespace std;

typedef long long LL;
const LL INF=1ll<<50;
const int N=2010;
vector<int> G[N];
int n,val[N];
LL dis[N][N];
LL f[N][N],pre[N][N],suf[N][N];

void dfs(int rt,int u,int fa)
{
    dis[rt][u]=dis[rt][fa]+val[u];
    for(int v : G[u]) if(v!=fa) dfs(rt,v,u);
}

void dp(int u,int fa)
{
    for(int i=1;i<=n;i++) f[u][i]=dis[u][i];
    for(int v : G[u])
    {
        if(v==fa) continue;
        dp(v,u);
        for(int j=1;j<=n;j++)
        {
            LL d=dis[u][j],ans=INF;
            ans=min(ans,pre[v][upper_bound(dis[v]+1,dis[v]+1+n,d-val[u])-dis[v]-1]);
            ans=min(ans,suf[v][lower_bound(dis[v]+1,dis[v]+1+n,d+val[v])-dis[v]]);
            f[u][j]+=ans;
        }
    }
    pre[u][0]=suf[u][n+1]=INF;
    for(int i=1;i<=n;i++) pre[u][i]=min(pre[u][i-1],f[u][i]);
    for(int i=n;i>=1;i--) suf[u][i]=min(suf[u][i+1],f[u][i]); 
}

int main()
{
    scanf("%d",&n);
    for(int i=1,u,v;i<n;i++)
    {
        scanf("%d%d",&u,&v);
        G[u].push_back(v);
        G[v].push_back(u);
    }
    for(int i=1;i<=n;i++) scanf("%d",val+i);
    for(int i=1;i<=n;i++) dfs(i,i,i),sort(dis[i]+1,dis[i]+1+n);
    dp(1,0);printf("%lld\n",suf[1][1]);
    return 0;
}