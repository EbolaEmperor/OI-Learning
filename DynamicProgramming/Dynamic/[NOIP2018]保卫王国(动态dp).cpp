#include<bits/stdc++.h>
using namespace std;

typedef long long LL;
const LL INF=1ll<<60;
const int N=100010;

struct Matrix
{
    LL m[2][2];
    Matrix(){m[0][0]=m[0][1]=m[1][0]=m[1][1]=INF;}
    LL* operator [] (const int &x){return m[x];}
    
    Matrix operator * (const Matrix &A)
    {
        Matrix C;
        for(int i=0;i<2;i++)
            for(int j=0;j<2;j++)
                for(int k=0;k<2;k++)
                    C[i][j]=min(C[i][j],m[i][k]+A.m[k][j]);
        return C;
    }
} val[N<<2],vl[N];

struct Edge{int to,next;} e[N<<1];
int h[N],n,m,sum=0;
int fa[N],hson[N],top[N],btm[N];
int dfn[N],idx[N],dfc=0;
int siz[N],dep[N];
LL f[N][2],g[N][2],p[N];

void add_edge(int u,int v)
{
    e[++sum].to=v;
    e[sum].next=h[u];
    h[u]=sum;
}

void dfs1(int u)
{
    siz[u]=1;
    for(int t=h[u];t;t=e[t].next)
    {
        int v=e[t].to;
        if(v==fa[u]) continue;
        dep[v]=dep[u]+1;
        fa[v]=u;dfs1(v);
        siz[u]+=siz[v];
        if(siz[v]>siz[hson[u]]) hson[u]=v;
    }
}

void dfs2(int u,int tp)
{
    top[u]=tp;
    idx[dfn[u]=++dfc]=u;
    if(hson[u])
    {
        dfs2(hson[u],tp);
        btm[u]=btm[hson[u]];
    }
    else btm[u]=u;
    for(int t=h[u];t;t=e[t].next)
        if(e[t].to!=fa[u]&&e[t].to!=hson[u])
            dfs2(e[t].to,e[t].to);
}

void dp(int u)
{
    f[u][1]=g[u][1]=p[u];
    for(int t=h[u];t;t=e[t].next)
    {
        int v=e[t].to;
        if(v==fa[u]) continue;
        dp(v);
        f[u][0]+=f[v][1];
        f[u][1]+=min(f[v][0],f[v][1]);
        if(v==hson[u]) continue;
        g[u][0]+=f[v][1];
        g[u][1]+=min(f[v][0],f[v][1]);
    }
}

void build(int o,int l,int r)
{
    if(l==r)
    {
        int u=idx[l];
        val[o][0][0]=INF;
        val[o][0][1]=g[u][0];
        val[o][1][0]=g[u][1];
        val[o][1][1]=g[u][1];
        vl[l]=val[o];
        return;
    }
    int mid=(l+r)/2;
    build(o<<1,l,mid);
    build(o<<1|1,mid+1,r);
    val[o]=val[o<<1]*val[o<<1|1];
}

void modify(int o,int l,int r,int k)
{
    if(l==r){val[o]=vl[l];return;}
    int mid=(l+r)/2;
    if(k<=mid) modify(o<<1,l,mid,k);
    else modify(o<<1|1,mid+1,r,k);
    val[o]=val[o<<1]*val[o<<1|1];
}

Matrix query(int o,int l,int r,int nl,int nr)
{
    if(l==nl&&r==nr) return val[o];
    int mid=(l+r)/2;
    if(nr<=mid) return query(o<<1,l,mid,nl,nr);
    else if(nl>mid) return query(o<<1|1,mid+1,r,nl,nr);
    else return query(o<<1,l,mid,nl,mid)*query(o<<1|1,mid+1,r,mid+1,nr);
}

void change(int u,LL x)
{
    vl[dfn[u]][1][0]+=x-p[u];
    vl[dfn[u]][1][1]+=x-p[u];
    p[u]=x;
    while(u)
    {
        int tp=top[u];
        Matrix pre=query(1,1,n,dfn[tp],dfn[btm[tp]]);
        modify(1,1,n,dfn[u]);
        Matrix now=query(1,1,n,dfn[tp],dfn[btm[tp]]);
        if(!(u=fa[tp])) break;
        vl[dfn[u]][0][1]+=now[1][1]-pre[1][1];
        vl[dfn[u]][1][0]+=min(now[0][1],now[1][1])-min(pre[0][1],pre[1][1]);
        vl[dfn[u]][1][1]=vl[dfn[u]][1][0];
    }
}

void gao(int a,int x,int b,int y)
{
    if(x==0&&y==0&&(fa[a]==b||fa[b]==a)){puts("-1");return;}
    LL pa=p[a],pb=p[b];
    change(a,x?pa-INF:pa+INF);
    change(b,y?pb-INF:pb+INF);
    Matrix tmp=query(1,1,n,dfn[1],dfn[btm[1]]);
    LL res=min(tmp[0][1],tmp[1][1]);
    res+=(x?INF:0)+(y?INF:0);
    printf("%lld\n",res);
    change(a,pa);change(b,pb);
}

int main()
{
    char ak[10];
    scanf("%d%d%s",&n,&m,ak);
    for(int i=1;i<=n;i++) scanf("%lld",p+i);
    for(int i=1,u,v;i<n;i++)
    {
        scanf("%d%d",&u,&v);
        add_edge(u,v);
        add_edge(v,u);
    }
    dep[1]=1;dfs1(1);dfs2(1,1);
    dp(1);build(1,1,n);
    for(int a,b,x,y;m;m--)
    {
        scanf("%d%d%d%d",&a,&x,&b,&y);
        gao(a,x,b,y);
    }
    return 0;
}