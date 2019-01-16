#include<bits/stdc++.h>
using namespace std;

const int N=100010;
vector<int> G[N];
int fa[20][N],dep[20][N],ch[20][N];
int trdep[N],trfa[N],fr[N];
int sz[N],mxsz[N],rt,sum;
int mxd=0,mxdf=0,rtdep;
bool done[N],light[N];
char s[N];
int n,m;

int* newarr(int len)
{
    static int mmp[4000000],*now=mmp,cnt;
    int *tmp=now;now+=len;
    return tmp;
}

struct BIT
{
    int *b,n;
    BIT(){}
    BIT(int m){n=m+1;b=newarr(n+1);}
    inline int lowbit(const int &x){return x&-x;}
    void add(int p,int x){for(p++;p<=n;p+=lowbit(p)) b[p]+=x;}
    int sum(int p){int res=0;for(p=min(p+1,n);p;p-=lowbit(p)) res+=b[p];return res;}
} b1[N],b2[N];

void find(int u,int f)
{
    sz[u]=1;mxsz[u]=0;
    for(int v : G[u])
    {
        if(done[v]||v==f) continue;
        find(v,u);sz[u]+=sz[v];
        mxsz[u]=max(mxsz[u],sz[v]);
    }
    mxsz[u]=max(mxsz[u],sum-sz[u]);
    if(mxsz[u]<mxsz[rt]) rt=u;
}

void dfs1(int u,int f)
{
    sz[u]=1;
    mxd=max(mxd,dep[rtdep][u]);
    mxdf=max(mxdf,dep[rtdep-1][u]);
    for(int v : G[u])
    {
        if(done[v]||v==f) continue;
        if(light[v]) ch[rtdep][u]++;
        dep[rtdep][v]=dep[rtdep][u]+1;
        fa[rtdep][v]=u;
        dfs1(v,u);
        sz[u]+=sz[v];
    }
}

void dfs2(int u)
{
    if(light[u]&&!light[fa[rtdep][u]]) b1[rt].add(dep[rtdep][u],1);
    if(light[u]&&(dep[rtdep-1][u]<=1||!light[fa[rtdep-1][u]])) b2[rt].add(dep[rtdep-1][u],1);
    for(int v : G[u]) if(!done[v]&&v!=fa[rtdep][u]) dfs2(v);
}

void build(int u,int f)
{
    done[u]=1;trfa[u]=f;
    trdep[u]=trdep[f]+1;
    mxd=mxdf=0;rtdep=trdep[u];
    dfs1(u,0);
    b1[u]=BIT(mxd);
    b2[u]=BIT(mxdf);
    dfs2(u);
    for(int v : G[u])
    {
        if(done[v]) continue;
        sum=sz[v];rt=0;find(v,u);
        fr[rt]=v;build(rt,u);
    }
}

void update(int x)
{
    light[x]^=1;
    for(int i=trdep[x],y=x;y;y=trfa[y],i--)
    {
        if(!light[fa[i][x]]) b1[y].add(dep[i][x],light[x]?1:-1);
        b1[y].add(dep[i][x]+1,light[x]?-ch[i][x]:ch[i][x]);
        ch[i][fa[i][x]]+=light[x]?1:-1;
        if(!trfa[x]) break;
        if(dep[i-1][x]<=1||!light[fa[i-1][x]]) b2[y].add(dep[i-1][x],light[x]?1:-1);
        b2[y].add(dep[i-1][x]+1,light[x]?-ch[i-1][x]:ch[i-1][x]);
    }
}

int query(int x,int d)
{
    int ans=0,flag=0;
    if(light[x]) update(x),flag=1;
    for(int y=x,i=trdep[x];y;y=trfa[y],i--)
    {
        if(d>=dep[i][x]) ans+=b1[y].sum(d-dep[i][x]);
        if(!trfa[y]) break;
        if(d-dep[i-1][x]>=0)
        {
            if(d==dep[i-1][x]) ans-=(light[fr[y]]&&light[trfa[y]]);
            ans-=b2[y].sum(d-dep[i-1][x]);
        }
    }
    if(flag) update(x);
    return ans;
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
    scanf("%s",s+1);
    for(int i=1;i<=n;i++)
        light[i]=(s[i]=='1');
    rt=0;sum=n;mxsz[0]=n+1;
    find(1,0);build(rt,0);
    int opt,x,d;
    while(m--)
    {
        scanf("%d%d",&opt,&x);
        if(opt==1) update(x);
        else scanf("%d",&d),printf("%d\n",query(x,d));
    }
    return 0;
}