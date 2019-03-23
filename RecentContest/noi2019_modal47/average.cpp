#include<bits/stdc++.h>
using namespace std;

const int ha=998244353;
const int N=500010;
int val[N<<2],sum[N<<2],mnp[N<<2],tag[N<<2];
int inv[N],sv[N],ssv[N],n;
vector<int> pos[N];

inline int add(const int &x,const int &y){return (x+y>=ha)?(x+y-ha):(x+y);}
inline int mns(const int &x,const int &y){return (x-y<0)?(x-y+ha):(x-y);}

void maintain(int o)
{
    sum[o]=add(sum[o<<1],sum[o<<1|1]);
    mnp[o]=max(mnp[o<<1],mnp[o<<1|1]);
}

void push(int o,int l,int r,int x)
{
    sum[o]=ssv[x-l]-ssv[x-1-r];
    mnp[o]=tag[o]=x;
}

void pushdown(int o,int l,int r)
{
    if(tag[o]<0) return;
    int mid=(l+r)/2;
    push(o<<1,l,mid,tag[o]);
    push(o<<1|1,mid+1,r,tag[o]);
    tag[o]=-1;
}

void build(int o,int l,int r)
{
    if(l==r){val[o]=ssv[n-l+1];return;}
    int mid=(l+r)/2;
    build(o<<1,l,mid);
    build(o<<1|1,mid+1,r);
    val[o]=add(val[o<<1],val[o<<1|1]);                                                                                                                                             
    maintain(o);
}

void modify(int o,int l,int r,int nl,int nr,int x)
{
    if(l>=nl&&r<=nr) return push(o,l,r,x);
    int mid=(l+r)/2;pushdown(o,l,r);
    if(nl<=mid) modify(o<<1,l,mid,nl,nr,x);
    if(nr>mid) modify(o<<1|1,mid+1,r,nl,nr,x);
    maintain(o);
}

int qsum(int o,int l,int r,int nl,int nr)
{
    if(l>=nl&&r<=nr) return mns(val[o],sum[o]);
    int mid=(l+r)/2,res=0;pushdown(o,l,r);
    if(nl<=mid) res=add(res,qsum(o<<1,l,mid,nl,nr));
    if(nr>mid) res=add(res,qsum(o<<1|1,mid+1,r,nl,nr));
    return res;
}

int find(int o,int l,int r,int nl,int nr,int p)
{
    if(l==r) return mnp[o]>p?l-1:l;
    int mid=(l+r)/2,res=0;pushdown(o,l,r);
    if(l>=nl&&r<=nr) return mnp[o<<1|1]<=p?find(o<<1|1,mid+1,r,nl,nr,p):find(o<<1,l,mid,nl,nr,p);
    if(nr>mid) res=find(o<<1|1,mid+1,r,nl,nr,p);
    if(res>mid) return res;
    if(nl<=mid) res=find(o<<1,l,mid,nl,nr,p);
    return res;
}

int main()
{
    scanf("%d",&n);
    for(int i=1,x;i<=n;i++)
        scanf("%d",&x),pos[x].emplace_back(i);
    inv[1]=1;
    for(int i=2;i<=n;i++)
    {
        inv[i]=1ll*(ha-ha/i)*inv[ha%i]%ha;
        sv[i]=add(sv[i-1],inv[i]);
        ssv[i]=add(ssv[i-1],sv[i]);
    }
    int ans=0,m=n;
    for(int i=0;i<=500000;i++)
    {
        if(pos[i].empty()) continue;
        for(int j=pos[i].size()-1;j>=0;j--)
        {
            if(j==pos[i].size()-1) m=min(m,pos[i][j]);
            int x=find(1,1,n,1,m,pos[i][j]);
            int ql=j?pos[i][j-1]+1:1;
            modify(1,1,n,ql,x,pos[i][j]);
        }
        ans=add(ans,qsum(1,1,n,1,m));
    }
    printf("%d\n",ans);
    return 0;
}