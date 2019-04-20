#include<bits/stdc++.h>
using namespace std;

const int ha=998244353,N=5010;
int mark[N*N],phi[N*N],prm[N*N/10],tot=0;
vector<int> g[N];
int n,dis[N];

void seive(int n)
{
    phi[1]=1;
    for(int i=2;i<=n;i++)
    {
        if(!mark[i]) prm[++tot]=i,phi[i]=i-1;
        for(int j=1;j<=tot&&i*prm[j]<=n;j++)
        {
            mark[i*prm[j]]=1;
            if(i%prm[j]) phi[i*prm[j]]=phi[i]*phi[prm[j]];
            else{phi[i*prm[j]]=phi[i]*prm[j];break;}
        }
    }
}

void dfs(int u,int fa)
{
    for(int v : g[u])
    {
        if(v==fa) continue;
        dis[v]=dis[u]+1;
        dfs(v,u);
    }
}

int main()
{
    freopen("tree4.in","r",stdin);
    scanf("%d",&n);
    seive(n*n);
    for(int i=1,u,v;i<n;i++)
    {
        scanf("%d%d",&u,&v);
        g[u].push_back(v);
        g[v].push_back(u);
    }
    int ans=0;
    for(int i=1;i<=n;i++)
    {
        dis[i]=0;dfs(i,0);
        for(int j=i+1;j<=n;j++)
            ans=(ans+2ll*phi[i*j]*dis[j])%ha,cerr<<"("<<i<<","<<j<<"): "<<phi[i]*phi[j]*dis[j]<<endl;
    }
    printf("%d\n",ans);
    return 0;
}
