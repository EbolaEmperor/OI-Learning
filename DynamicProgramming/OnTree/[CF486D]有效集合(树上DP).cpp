#include<bits/stdc++.h>
using namespace std;

const int ha=1e9+7;
const int N=2010;
struct Edge{int to,next;} e[N<<1];
int h[N],sum=0,f[N],val[N],n,d;

void add_edge(int u,int v)
{
    e[++sum].to=v;
    e[sum].next=h[u];
    h[u]=sum;
}

void dfs(int u,int fa,int root)
{
    f[u]=1;
    for(int t=h[u];t;t=e[t].next)
    {
        int v=e[t].to;
        if(v==fa) continue;
        if(val[v]>val[root]||val[v]==val[root]&&v>root)
        {
            if(val[v]-val[root]>d) continue;
            dfs(v,u,root);
            f[u]=1ll*f[u]*(f[v]+1)%ha;
        }
    }
}

int main()
{
    int u,v;
    scanf("%d%d",&d,&n);
    for(int i=1;i<=n;i++) scanf("%d",val+i);
    for(int i=1;i<n;i++)
    {
        scanf("%d%d",&u,&v);
        add_edge(u,v);
        add_edge(v,u);
    }
    int ans=0;
    for(int i=1;i<=n;i++)
    {
        dfs(i,0,i);
        ans=(ans+f[i])%ha;
    }
    printf("%d\n",ans);
    return 0;
}