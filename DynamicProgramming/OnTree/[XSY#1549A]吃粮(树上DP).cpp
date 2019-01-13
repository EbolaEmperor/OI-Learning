#include<bits/stdc++.h>
using namespace std;

const int ha=998244353;
const int N=100010;
vector<int> G[N];
int n,val[N],deg[N],fa[N];
int k[N],b[N],f[N],g[N];

inline int add(const int &x,const int &y){return (x+y>=ha)?(x+y-ha):(x+y);}
inline int mns(const int &x,const int &y){return (x-y<0)?(x-y+ha):(x-y);}

int Pow(int a,int b)
{
    int ans=1;
    for(;b;b>>=1,a=1ll*a*a%ha)
        if(b&1) ans=1ll*ans*a%ha;
    return ans;
}

void dfs1(int u,int fa)
{
    if(deg[u]==1){k[u]=0;b[u]=val[u];g[u]=1;return;}
    int sumk=0,sumb=0;
    for(int v : G[u])
    {
        if(v==fa) continue;
        dfs1(v,u);
        sumk=add(sumk,k[v]);
        sumb=add(sumb,b[v]);
    }
    k[u]=Pow(mns(deg[u],sumk),ha-2);
    b[u]=1ll*k[u]*add(sumb,1ll*deg[u]*val[u]%ha)%ha;
    f[u]=k[u];g[u]=1ll*deg[u]*k[u]%ha;
}

void dfs2(int u)
{
    for(int v : G[u])
    {
        if(v==fa[u]) continue;
        f[v]=1ll*f[u]*f[v]%ha;
        fa[v]=u;dfs2(v);
    }
}

int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++) scanf("%d",val+i);
    for(int i=1,u,v;i<n;i++)
    {
        scanf("%d%d",&u,&v);
        G[u].push_back(v);
        G[v].push_back(u);
        deg[u]++;deg[v]++;
    }
    dfs1(1,0);dfs2(1);
    printf("%d\n",b[1]);
    int ans=b[1],x,y,m;
    scanf("%d",&m);
    while(m--)
    {
        scanf("%d%d",&x,&y);
        int d=mns(y,val[x]);val[x]=y;
        if(x==1) ans=(ans+1ll*d*g[x])%ha;
        else ans=(ans+1ll*d*g[x]%ha*f[fa[x]])%ha;
        printf("%d\n",ans);
    }
    return 0;
}