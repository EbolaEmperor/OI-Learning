#include<bits/stdc++.h>
using namespace std;

typedef long long LL;
const int N=200010;
int ffa[N],nxt[N],tail[N],pos[N];
int n,QAQ,fa[N];
LL w[N],wson[N],ans[N];
vector<int> son[N];

struct group
{
    LL x,y;int v;
    group(LL _x=0,LL _y=0,int _v=0):x(_x),y(_y),v(_v){}
    bool operator < (const group &a) const
    {
        if((x<0)^(a.x<0)) return x<a.x;
        if(x>=0) return (y-x==a.y-a.x)?(v<a.v):(y-x>a.y-a.x);
        return (y==a.y)?(v<a.v):(y<a.y);
    }
} g[N];
set<group> S;

int find(int x){return ffa[x]==x?x:ffa[x]=find(ffa[x]);}

void merge_group(int x,int y)
{
    ffa[x]=y;
    nxt[tail[y]]=x;
    tail[y]=tail[x];
    if(S.find(g[y])==S.end()) return;
    S.erase(g[y]);
    g[y]=group(g[y].x+g[x].x,max(g[x].y,g[x].x+g[y].y),y);
    S.insert(g[y]);
}

void get_order()
{
    for(int i=1;i<=n;i++) ffa[i]=tail[i]=i;
    for(int i=1;i<=n;i++)
    {
        group tmp=*S.rbegin();S.erase(tmp);
        merge_group(tmp.v,find(fa[tmp.v]));
    }
    for(int i=1,c=n;i;i=nxt[i]) pos[i]=c--;
}

LL mx[N*20],sum[N*20];
int rt[N],lc[N*20],rc[N*20],tot=0;

void maintain(int o)
{
    sum[o]=sum[lc[o]]+sum[rc[o]];
    mx[o]=max(mx[lc[o]],sum[lc[o]]+mx[rc[o]]);
}

void update(int &o,int l,int r,int k,LL a,LL b)
{
    if(!o) o=++tot;
    if(l==r){sum[o]=a;mx[o]=b;return;}
    int mid=(l+r)/2;
    if(k<=mid) update(lc[o],l,mid,k,a,b);
    else update(rc[o],mid+1,r,k,a,b);
    maintain(o);
}

int merge(int x,int y)
{
    if(!x||!y) return x+y;
    lc[x]=merge(lc[x],lc[y]);
    rc[x]=merge(rc[x],rc[y]);
    maintain(x);
    return x;
}

void dfs(int u)
{
    update(rt[u],1,n,pos[u],w[u]-wson[u],w[u]);
    for(int v : son[u])
        dfs(v),rt[u]=merge(rt[u],rt[v]);
    ans[u]=mx[rt[u]];
}

int main()
{
    scanf("%d%d",&QAQ,&n);
    for(int i=2;i<=n;i++) scanf("%d",fa+i),son[fa[i]].emplace_back(i);
    for(int i=1;i<=n;i++) scanf("%lld",w+i),wson[fa[i]]+=w[i];
    for(int i=1;i<=n;i++) S.insert(g[i]=group(w[i]-wson[i],w[i],i));
    get_order();dfs(1);
    for(int i=1;i<=n;i++)
        printf("%lld ",ans[i]);
    return puts(""),0;
}