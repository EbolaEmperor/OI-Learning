#include<bits/stdc++.h>
using namespace std;

const int S=(1<<20)+5;
char buf[S],*H,*T;
inline char Get()
{
    if(H==T) T=(H=buf)+fread(buf,1,S,stdin);
    if(H==T) return -1;return *H++;
}
inline int read()
{
    int x=0,fg=1;char c=Get();
    while(!isdigit(c)&&c!='-') c=Get();
    if(c=='-') fg=-1,c=Get();
    while(isdigit(c)) x=x*10+c-'0',c=Get();
    return x*fg;
}

typedef long long LL;
const int N=100010;
const LL INF=1ll<<60;
struct Info{LL val;int fa;} mn[N<<2][2];
struct Event{int x,l,r,w;} opt[N<<2];
int fa[N],n,m,cnt=0;
LL tag[N<<2],ans=0;

inline bool operator < (const Info &a,const Info &b){return a.val<b.val;}
inline bool operator < (const Event &a,const Event &b){return a.x<b.x;}

int find(int x){return fa[x]==x?x:fa[x]=find(fa[x]);}

void maintain(int o)
{
    int lc=o<<1,rc=o<<1|1;
    if(mn[lc][0].val>mn[rc][0].val) swap(lc,rc);
    mn[o][0]=min(mn[lc][0],mn[rc][0]);
    if(find(mn[lc][0].fa)!=find(mn[rc][0].fa)) mn[o][1]=min(mn[lc][1],mn[rc][0]);
    else mn[o][1]=min(mn[lc][1],mn[rc][1]);
    mn[o][0].val+=tag[o];mn[o][1].val+=tag[o];
}

void build(int o,int l,int r)
{
    tag[o]=0;
    if(l==r)
    {
        mn[o][0]={0,find(l)};
        mn[o][1]={INF,0};
        return;
    }
    int mid=(l+r)/2;
    build(o<<1,l,mid);
    build(o<<1|1,mid+1,r);
    maintain(o);
}

void add(int o,int l,int r,int nl,int nr,int x)
{
    if(l>=nl&&r<=nr)
    {
        mn[o][0].val+=x;
        mn[o][1].val+=x;
        tag[o]+=x;
        return;
    }
    int mid=(l+r)/2;
    if(nl<=mid) add(o<<1,l,mid,nl,nr,x);
    if(nr>mid) add(o<<1|1,mid+1,r,nl,nr,x);
    maintain(o);
}

bool gao()
{
    build(1,1,n);
    static Info g[N];
    for(int i=1;i<=n;i++) g[i].val=INF;
    for(int i=1,p=0;i<=n;i++)
    {
        while(p<4*m&&opt[p+1].x<=i) p++,add(1,1,n,opt[p].l,opt[p].r,opt[p].w);
        g[find(i)]=min(g[find(i)],(find(mn[1][0].fa)==find(i))?mn[1][1]:mn[1][0]);
    }
    for(int i=1;i<=n;i++)
    {
        int x=find(i),y=find(g[x].fa);
        if(x==y) continue;
        ans+=g[x].val;
        fa[x]=y;cnt++;
    }
    return cnt<n-1;
}

int main()
{
    int x1,x2,y1,y2,w;
    n=read();m=read();
    for(int i=1;i<=m;i++)
    {
        x1=read();x2=read();y1=read();y2=read();w=read();
        opt[4*i-3]={x1,y1,y2,w};
        opt[4*i-2]={x2+1,y1,y2,-w};
        opt[4*i-1]={y1,x1,x2,w};
        opt[4*i]={y2+1,x1,x2,-w};
    }
    sort(opt+1,opt+1+4*m);
    for(int i=1;i<=n;i++) fa[i]=i;
    while(gao());
    printf("%lld\n",ans);
    return 0;
}