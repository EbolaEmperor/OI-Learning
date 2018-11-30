// 模板题号：洛谷P4319
#include<bits/stdc++.h>
using namespace std;

const int INF=0x3f3f3f3f;
const int N=100010;
vector<int> G[N];
int hson[N],top[N],btm[N];
int dfn[N],idx[N],dfc=0;
int siz[N],fa[N];
int n,m,a[N],f[N][2],g[N][2];

struct Matrix
{
    int m[2][2];
    Matrix(){m[0][0]=m[0][1]=m[1][0]=m[1][1]=-INF;}
    int* operator [] (const int &x){return m[x];}
    Matrix operator * (const Matrix &B)
    {
        Matrix C;
        for(int i=0;i<2;i++)
            for(int j=0;j<2;j++)
                for(int k=0;k<2;k++)
                    C[i][j]=max(C[i][j],m[i][k]+B.m[k][j]);
        return C;
    }
} val[N],tr[N<<2];

void build(int o,int l,int r)
{
    if(l==r){tr[o]=val[idx[l]];return;}
    int mid=(l+r)/2;
    build(o<<1,l,mid);
    build(o<<1|1,mid+1,r);
    tr[o]=tr[o<<1]*tr[o<<1|1];
}

void modify(int o,int l,int r,int k)
{
    if(l==r){tr[o]=val[idx[l]];return;}
    int mid=(l+r)/2;
    if(k<=mid) modify(o<<1,l,mid,k);
    else modify(o<<1|1,mid+1,r,k);
    tr[o]=tr[o<<1]*tr[o<<1|1];
}

Matrix query(int o,int l,int r,int nl,int nr)
{
    if(l==nl&&r==nr) return tr[o];
    int mid=(l+r)/2;
    if(nr<=mid) return query(o<<1,l,mid,nl,nr);
    if(nl>mid) return query(o<<1|1,mid+1,r,nl,nr);
    return query(o<<1,l,mid,nl,mid)*query(o<<1|1,mid+1,r,mid+1,nr);
}

void dfs(int u)
{
    siz[u]=1;
    for(int v : G[u])
    {
        if(v==fa[u]) continue;
        fa[v]=u;dfs(v);
        siz[u]+=siz[v];
        if(siz[v]>siz[hson[u]]) hson[u]=v;
    }
}

void dfs(int u,int tp)
{
    top[u]=tp;
    idx[dfn[u]=++dfc]=u;
    if(hson[u])
    {
        dfs(hson[u],tp);
        btm[u]=btm[hson[u]];
    }
    else btm[u]=u;
    for(int v : G[u])
        if(v!=fa[u]&&v!=hson[u])
            dfs(v,v);
}

int gao(int x,int v)
{
    val[x][1][0]+=v-a[x];a[x]=v;
    while(top[x]!=1)
    {
        int tp=top[x];
        Matrix pre=query(1,1,n,dfn[tp],dfn[btm[x]]);
        modify(1,1,n,dfn[x]);
        Matrix now=query(1,1,n,dfn[tp],dfn[btm[x]]);
        val[fa[tp]][1][0]+=now[0][0]-pre[0][0];
        val[fa[tp]][0][0]-=max(pre[0][0],pre[1][0]);
        val[fa[tp]][0][0]+=max(now[0][0],now[1][0]);
        val[fa[tp]][0][1]=val[fa[tp]][0][0];
        x=fa[tp];
    }
    modify(1,1,n,dfn[x]);
    Matrix t=query(1,1,n,1,dfn[btm[1]]);
    return max(t[0][0],t[1][0]);
}

void dp(int u)
{
    f[u][1]=g[u][1]=a[u];
    for(int v : G[u])
    {
        if(v==fa[u]) continue;
        dp(v);
        f[u][1]+=f[v][0];
        f[u][0]+=max(f[v][0],f[v][1]);
        if(v==hson[u]) continue;
        g[u][1]+=f[v][0];
        g[u][0]+=max(f[v][0],f[v][1]);
    }
    val[u][0][0]=g[u][0];
    val[u][0][1]=g[u][0];
    val[u][1][0]=g[u][1];
    val[u][1][1]=0;
}

int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++)
        scanf("%d",a+i);
    for(int i=1,u,v;i<n;i++)
    {
        scanf("%d%d",&u,&v);
        G[u].push_back(v);
        G[v].push_back(u);
    }
    dfs(1);dfs(1,1);dp(1);
    build(1,1,n);
    while(m--)
    {
        int x,v;
        scanf("%d%d",&x,&v);
        printf("%d\n",gao(x,v));
    }
    return 0;
}
