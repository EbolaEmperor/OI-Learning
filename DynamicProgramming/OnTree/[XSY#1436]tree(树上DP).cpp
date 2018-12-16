#include<bits/stdc++.h>
using namespace std;

const int N=100010;
struct Edge{int to,capa,next;} e[N<<1];
int h[N],sum=0;
int n,a,b,col[N];
long long f[N][3];

void add_edge(int u,int v,int w)
{
    e[++sum].to=v;
    e[sum].capa=w;
    e[sum].next=h[u];
    h[u]=sum;
}

void dfs(int u,int fa)
{
    if(col[u]==1) f[u][0]=f[u][2]=1ll<<60;
    if(col[u]==2) f[u][0]=f[u][1]=1ll<<60;
    for(int t=h[u];t;t=e[t].next)
    {
        int v=e[t].to,w=e[t].capa;
        if(v==fa) continue;
        dfs(v,u);
        f[u][0]+=min(f[v][0],min(f[v][1],f[v][2])+w);
        f[u][1]+=min(f[v][2]+w,min(f[v][0],f[v][1]));
        f[u][2]+=min(f[v][1]+w,min(f[v][0],f[v][2]));
    }
}

int main()
{
    scanf("%d",&n);
    for(int i=1,u,v,w;i<n;i++)
    {
        scanf("%d%d%d",&u,&v,&w);
        add_edge(u,v,w);
        add_edge(v,u,w);
    }
    scanf("%d",&a);
    for(int i=1,x;i<=a;i++)
        scanf("%d",&x),col[x]=1;
    scanf("%d",&b);
    for(int i=1,x;i<=b;i++)
        scanf("%d",&x),col[x]=2;
    dfs(1,0);
    printf("%lld\n",min(f[1][0],min(f[1][1],f[1][2])));
    return 0;
}