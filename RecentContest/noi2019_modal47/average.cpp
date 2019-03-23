#include<bits/stdc++.h>
using namespace std;

const int ha=998244353;
const int N=500010;
int sum[N<<2],mnp[N<<2],tag[N<<2];
int inv[N],sv[N],ssv[N],n;
vector<int> pos[N];

inline int add(const int &x,const int &y){return (x+y>=ha)?(x+y-ha):(x+y);}
inline int mns(const int &x,const int &y){return (x-y<0)?(x-y+ha):(x-y);}

void maintain(int o)
{
    sum[o]=add(sum[o<<1],sum[o<<1|1]);
    mnp[o]=min(mnp[o<<1],mnp[o<<1|1]);
}

void push(int o,int l,int r,int x)
{
    sum[o]=mns(ssv[x-l],ssv[x-1-r]);
    mnp[o]=tag[o]=x;
}

void pushdown(int o,int l,int r)
{
    if(!tag[o]) return;
    int mid=(l+r)/2;
    push(o<<1,l,mid,tag[o]);
    push(o<<1|1,mid+1,r,tag[o]);
    tag[o]=0;
}

void build(int o,int l,int r)
{
    if(l==r){mnp[o]=l;return;}
    int mid=(l+r)/2;
    build(o<<1,l,mid);
    build(o<<1|1,mid+1,r);
    maintain(o);
}

void modify(int o,int l,int r,int nl,int nr,int x)
{
    if(nl>nr) return;
    if(l>=nl&&r<=nr) return push(o,l,r,x);
    int mid=(l+r)/2;pushdown(o,l,r);
    if(nl<=mid) modify(o<<1,l,mid,nl,nr,x);
    if(nr>mid) modify(o<<1|1,mid+1,r,nl,nr,x);
    maintain(o);
}

int find(int o,int l,int r,int p)
{
    if(l==r) return mnp[o]<p?l:0;
    int mid=(l+r)/2,res=0;pushdown(o,l,r);
    if(mnp[o<<1|1]<p) return find(o<<1|1,mid+1,r,p);
    else return find(o<<1,l,mid,p);
}

int main()
{
    scanf("%d",&n);
    for(int i=1,x;i<=n;i++)
        scanf("%d",&x),pos[x].emplace_back(i);
    inv[1]=sv[1]=ssv[1]=1;
    for(int i=2;i<=n;i++)
    {
        inv[i]=1ll*(ha-ha/i)*inv[ha%i]%ha;
        sv[i]=add(sv[i-1],inv[i]);
        ssv[i]=add(ssv[i-1],sv[i]);
    }
    int ans=0;
    build(1,1,n);
    cerr<<"build done."<<endl;
    for(int i=0;i<=500000;i++)
    {
        if(pos[i].empty()) break;
        pos[i].emplace_back(n+1);
        for(int j=0;j<pos[i].size();j++)
        {
            int x=find(1,1,n,pos[i][j]);
            int ql=j?pos[i][j-1]+1:1;
            modify(1,1,n,ql,x,pos[i][j]);
        }
        ans=add(ans,mns(ssv[n],sum[1]));
    }
    printf("%d\n",ans);
    return 0;
}