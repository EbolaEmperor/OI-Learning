#include<bits/stdc++.h>
using namespace std;

const int ha=64123;
const int N=1680;
vector<int> G[N];
int n,k,w,d[N],idx[N],f[N][N];

void add(int &x,const int &y){x=x+y>=ha?x+y-ha:x+y;}
void dfs(int u,int fa,int rt)
{
    if(fa) memcpy((d[u]>d[rt]||d[u]==d[rt]&&u<rt)?(f[u]+1):f[u],f[fa],sizeof(int)*(k+1));
    for(int v : G[u]) if(v!=fa) dfs(v,u,rt);
    for(int i=0;i<k;i++) add(f[fa][i],f[u][i]);
}

int main()
{
    scanf("%d%d%d",&n,&k,&w);
    for(int i=1;i<=n;i++) scanf("%d",d+i);
    for(int i=1,u,v;i<n;i++)
    {
        scanf("%d%d",&u,&v);
        G[u].push_back(v);
        G[v].push_back(u);
    }
    for(int i=1;i<=n;i++) idx[i]=i;
    stable_sort(idx+1,idx+1+n,[](int x,int y){return d[x]>d[y];});
    int ans=0;
    for(int i=k;i<=n;i++)
    {
        int u=idx[i];
        for(int i=1;i<=n;i++)
            memset(f[i],0,sizeof(int)*(k+1));
        f[u][0]=1;dfs(u,0,u);
        ans=(ans+1ll*d[u]*f[u][k-1])%ha;
    }
    printf("%d\n",ans);
    return 0;
}