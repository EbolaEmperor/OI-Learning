#include<bits/stdc++.h>
using namespace std;

const int N=510,M=4010;
struct Edge{int to,next;} e[N<<1];
int h[N],tot=0,n,m,ans=0;
int w[N],c[N],d[N];
int out[N],idx[N],dfc=0;
int sz[N],mx[N];
int f[N][M];
int root,sum;
bool vis[N];

inline void upmax(int &x,const int &y){if(y>x) x=y;}

void add_edge(int u,int v)
{
    e[++tot].to=v;
    e[tot].next=h[u];
    h[u]=tot;
}

void find(int u,int fa)
{
    sz[u]=1;mx[u]=0;
    for(int tmp=h[u];tmp;tmp=e[tmp].next)
    {
        int v=e[tmp].to;
        if(vis[v]||v==fa) continue;
        find(v,u);
        sz[u]+=sz[v];
        upmax(mx[u],sz[v]);
    }
    upmax(mx[u],sum-sz[u]);
    if(mx[u]<mx[root]) root=u;
}

void dfs(int u,int fa)
{
    idx[++dfc]=u;sz[u]=1;
    for(int tmp=h[u];tmp;tmp=e[tmp].next)
        if(!vis[e[tmp].to]&&e[tmp].to!=fa)
            dfs(e[tmp].to,u),sz[u]+=sz[e[tmp].to];
    out[u]=dfc;
}

void dp()
{
    for(int i=1;i<=dfc+1;i++)
        for(int j=0;j<=m;j++)
            f[i][j]=0;
    for(int i=dfc;i>=1;i--)
    {
        int v=idx[i],t=d[v]-1;
        for(int j=m;j>=c[v];j--)
            f[i][j]=f[i+1][j-c[v]]+w[v];
        for(int j=1;j<=t;t-=j,j<<=1)
            for(int k=m;k>=j*c[v];k--)
                upmax(f[i][k],f[i][k-j*c[v]]+j*w[v]);
        for(int j=m;j>=t*c[v];j--)
            upmax(f[i][j],f[i][j-t*c[v]]+t*w[v]);
        for(int j=0;j<=m;j++)   
            upmax(f[i][j],f[out[v]+1][j]);
    }
    upmax(ans,f[1][m]);
}

void gao(int u)
{
    vis[u]=1;dfc=0;dfs(u,0);dp();
    for(int tmp=h[u];tmp;tmp=e[tmp].next)
    {
        int v=e[tmp].to;
        if(vis[v]) continue;
        root=0;sum=sz[v];
        find(v,0);gao(root);
    }
}

int main()
{
    int T,u,v;mx[0]=N;
    for(scanf("%d",&T);T;T--)
    {
        scanf("%d%d",&n,&m);
        for(int i=1;i<=n;i++) scanf("%d",w+i);
        for(int i=1;i<=n;i++) scanf("%d",c+i);
        for(int i=1;i<=n;i++) scanf("%d",d+i);
        memset(h,0,sizeof(h));tot=ans=0;
        memset(vis,0,sizeof(vis));
        for(int i=1;i<n;i++)
        {
            scanf("%d%d",&u,&v);
            add_edge(u,v);
            add_edge(v,u);
        }
        root=0;sum=n;
        find(1,0);gao(root);
        printf("%d\n",ans);
    }
    return 0;
}