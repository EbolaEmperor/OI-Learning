#include<bits/stdc++.h>
using namespace std;

typedef long long LL;
const int N=110,M=2010;
LL mat[N][N],eg[M][N];
LL a[N][N],b[N][N],dr[N][N],ans[M],aaa[N],rec[M],p;
int e[N][N],idx[N][N],n,m,fa[N],dep[N],tot=0;
bool vis[N];

inline LL mul(const LL &a,const LL &b){return (__int128)a*b%p;}
inline LL add(const LL &a,const LL &b){return (a+b>=p)?(a+b-p):(a+b);}
inline LL mns(const LL &a,const LL &b){return (a-b<0)?(a-b+p):(a-b);}

LL Pow(LL a,LL b)
{
    LL ans=1;
    for(;b;b>>=1,a=mul(a,a))
        if(b&1) ans=mul(ans,a);
    return ans;
}

void gauss()
{
    for(int i=1;i<n;i++)
    {
        int pos=i;
        while(!mat[pos][i]) pos++;
        for(int j=1;j<=n;j++) swap(mat[i][j],mat[pos][j]);
        LL inv=Pow(mat[i][i],p-2);
        for(int j=1;j<=n;j++)
        {
            if(i==j) continue;
            LL t=mul(mat[j][i],inv);
            for(int k=1;k<=n;k++)
                mat[j][k]=mns(mat[j][k],mul(t,mat[i][k]));
        }
    }
}

void dfs(int u)
{
    vis[u]=1;
    for(int v=1;v<=n;v++)
        if(e[u][v]&&!vis[v])
        {
            idx[u][v]=idx[v][u]=v-1;
            dep[v]=dep[u]+1;
            fa[v]=u;dfs(v);
        }
}

void gao(int u,int v)
{
    if(dep[u]<dep[v]) swap(u,v);
    int id=e[u][v],x=u,y=v;
    LL inv=Pow(b[v][u],p-2),sum=a[v][u];
    rec[id]=dr[v][u];
    while(dep[u]>dep[v])
    {
        sum=add(sum,a[u][fa[u]]);
        eg[id][idx[u][fa[u]]]=mul(b[u][fa[u]],dr[u][fa[u]]);
        u=fa[u];
    }
    while(u!=v)
    {
        sum=add(sum,a[u][fa[u]]);
        eg[id][idx[u][fa[u]]]=mul(b[u][fa[u]],dr[u][fa[u]]);
        sum=add(sum,a[fa[v]][v]);
        eg[id][idx[fa[v]][v]]=mul(b[fa[v]][v],dr[fa[v]][v]);
        u=fa[u];v=fa[v];
    }
    eg[id][n]=sum;
    for(int i=1;i<=n;i++)
        eg[id][i]=mul(p-eg[id][i],inv);
    for(int k=1;k<=n;k++)
        mat[y][k]=add(mat[y][k],eg[id][k]);
    for(int k=1;k<=n;k++)
        mat[x][k]=mns(mat[x][k],eg[id][k]);
}

LL getans(int id)
{
    LL res=p-eg[id][n];
    for(int i=1;i<n;i++)
        res=add(res,mul(eg[id][i],aaa[i]));
    return mul(res,rec[id]);
}

int main()
{
    scanf("%d%d%lld",&n,&m,&p);
    for(int i=1,u,v;i<=m;i++)
    {
        scanf("%d%d",&u,&v);
        e[u][v]=e[v][u]=i;
        dr[u][v]=1;dr[v][u]=p-1;
        scanf("%lld",a[u]+v);
        a[v][u]=p-a[u][v];
        scanf("%lld",b[u]+v);
        b[v][u]=b[u][v];
    }
    dfs(1);
    for(int u=1;u<=n;u++)
        for(int v=1;v<=n;v++)
        {
            if(!e[u][v]) continue;
            if(fa[v]==u) mat[u][v-1]=dr[u][v];
            else if(fa[u]==v) mat[u][u-1]=dr[u][v];
        }
    for(int u=1;u<=n;u++)
        for(int v=u;v<=n;v++)
            if(e[u][v]&&fa[u]!=v&&fa[v]!=u)
                gao(u,v);
    gauss();
    for(int i=1;i<n;i++)
        aaa[i]=ans[e[i+1][fa[i+1]]]=mul(mat[i][n],Pow(mat[i][i],p-2));
    for(int u=1;u<=n;u++)
        for(int v=1;v<=n;v++)
            if(e[u][v]&&fa[u]!=v&&fa[v]!=u)
                ans[e[u][v]]=getans(e[u][v]),e[u][v]=e[v][u]=0;
    for(int i=1;i<=m;i++)
        printf("%lld\n",ans[i]);
    return 0;
}