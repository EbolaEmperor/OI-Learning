#include<bits/stdc++.h>
using namespace std;

const int ha=998244353;
const int N=100010,M=N*20;
struct E{int v,w;};
vector<E> g[N];
vector<int> pos[N];
int n,m,a[N],val[N],ans=0;
int cnt[M][2][2],lc[M],rc[M],sum[M],rt[N],tot=0;
// cnt[u][1/0][1/0] : u号点的区间中，所有的奇/偶下标中，前缀和为奇/偶的有多少个

void calc(int cnt[2][2],int l,int r)
{
    cnt[l&1][0]=(r-l)/2+1;
    cnt[~l&1][0]=(r-l+1)-cnt[l&1][0];
}

void maintain(int o,int l,int r)
{
    static int cntl[2][2],cntr[2][2];
    memcpy(cntl,cnt[lc[o]],sizeof(cntl));
    memcpy(cntr,cnt[rc[o]],sizeof(cntr));
    int mid=(l+r)/2;
    if(!lc[o]) calc(cntl,l,mid);
    if(!rc[o]) calc(cntr,mid+1,r);
    sum[o]=sum[lc[o]]+sum[rc[o]];
    memcpy(cnt[o],cntl,sizeof(cnt[o]));
    for(int i=0;i<2;i++)for(int j=0;j<2;j++)
        cnt[o][i][j]+=cntr[i][j^(sum[lc[o]]&1)];
}

void insert(int &o,int l,int r,int k)
{
    if(!o) o=++tot;
    if(l==r)
    {
        cnt[o][l&1][1]=1;
        sum[o]=1;
        return;
    }
    int mid=(l+r)/2;
    if(k<=mid) insert(lc[o],l,mid,k);
    else insert(rc[o],mid+1,r,k);
    maintain(o,l,r);
}

int merge(int p1,int p2,int l,int r)
{
    if(!p1||!p2) return p1|p2;
    int mid=(l+r)/2;
    lc[p1]=merge(lc[p1],lc[p2],l,mid);
    rc[p1]=merge(rc[p1],rc[p2],mid+1,r);
    maintain(p1,l,r);
    return p1;
}

void dfs(int u,int fa)
{
    for(auto e : g[u])
    {
        if(e.v==fa) continue;
        val[e.v]=e.w;dfs(e.v,u);
        rt[u]=merge(rt[u],rt[e.v],0,m);
    }
    for(int p : pos[u])
        insert(rt[u],0,m,p);
    int res=0;
    res=(res+1ll*cnt[rt[u]][0][0]*cnt[rt[u]][0][1])%ha;
    res=(res+1ll*cnt[rt[u]][1][0]*cnt[rt[u]][1][1])%ha;
    ans=(ans+1ll*val[u]*res)%ha;
}

int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1,u,v,w;i<n;i++)
    {
        scanf("%d%d%d",&u,&v,&w);
        g[u].emplace_back((E){v,w});
        g[v].emplace_back((E){u,w});
    }
    for(int i=1;i<=m;i++)
        scanf("%d",a+i),pos[a[i]].emplace_back(i);
    dfs(1,0);
    printf("%d\n",ans);
    return 0;
}