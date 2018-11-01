#include<bits/stdc++.h>
using namespace std;

const int P=10000010;
const int N=300010;
struct Player{int s,t,lca;} pl[N];
int lc[P],rc[P],sum[P],tot=0;
int dfn[N],out[N],dfc=0,n,m;
int fa[20][N],dep[N];
int rt[N<<1];
vector<int> G[N];
int watch[N],ans[N];

void insert(int &o,int l,int r,int k,int x)
{
    if(k<l||k>r) return;
    if(!o) o=++tot;sum[o]+=x;
    if(l==r) return;
    int mid=(l+r)/2;
    if(k<=mid) insert(lc[o],l,mid,k,x);
    else insert(rc[o],mid+1,r,k,x);
}

int query(int o,int l,int r,int nl,int nr)
{
    if(l>=nl&&r<=nr) return sum[o];
    int mid=(l+r)/2,res=0;
    if(nl<=mid) res+=query(lc[o],l,mid,nl,nr);
    if(nr>mid) res+=query(rc[o],mid+1,r,nl,nr);
    return res;
}

void dfs(int u,int la)
{
    dfn[u]=++dfc;
    for(int i=1;i<=18;i++)
        fa[i][u]=fa[i-1][fa[i-1][u]];
    for(int v : G[u])
    {
        if(v==la) continue;
        dep[v]=dep[u]+1;
        fa[0][v]=u;dfs(v,u);
    }
    out[u]=dfc;
}

int lca(int x,int y)
{
    if(dep[x]<dep[y]) swap(x,y);
    for(int i=18;i>=0;i--)
        if(dep[fa[i][x]]>=dep[y]) x=fa[i][x];
    if(x==y) return x;
    for(int i=18;i>=0;i--)
        if(fa[i][x]!=fa[i][y])
            x=fa[i][x],y=fa[i][y];
    return fa[0][x];
}

void work1()
{
    for(int i=1;i<=m;i++)
    {
        insert(rt[dep[pl[i].s]],1,n,dfn[pl[i].s],1);
        insert(rt[dep[pl[i].s]],1,n,dfn[fa[0][pl[i].lca]],-1);
    }
    for(int i=1;i<=n;i++)
        ans[i]=query(rt[dep[i]+watch[i]],1,n,dfn[i],out[i]);
}

void work2()
{
    memset(sum,0,sizeof(sum));
    memset(rt,0,sizeof(rt));
    memset(lc,0,sizeof(lc));
    memset(rc,0,sizeof(rc));
    int* root=rt+N;tot=0;
    for(int i=1;i<=m;i++)
    {
        int tmp=dep[pl[i].s]-2*dep[pl[i].lca];
        insert(root[tmp],1,n,dfn[pl[i].t],1);
        insert(root[tmp],1,n,dfn[pl[i].lca],-1);
    }
    for(int i=1;i<=n;i++)
        ans[i]+=query(root[watch[i]-dep[i]],1,n,dfn[i],out[i]);
}

int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1,u,v;i<n;i++)
    {
        scanf("%d%d",&u,&v);
        G[u].push_back(v);
        G[v].push_back(u);
    }
    dep[1]=1;dfs(1,0);
    for(int i=1;i<=n;i++) scanf("%d",watch+i);
    for(int i=1;i<=m;i++)
    {
        scanf("%d%d",&pl[i].s,&pl[i].t);
        pl[i].lca=lca(pl[i].s,pl[i].t);
    }
    work1();work2();
    for(int i=1;i<=n;i++)
        printf("%d ",ans[i]);
    return 0;
}