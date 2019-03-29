#include<bits/stdc++.h>
using namespace std;

const int N=200010,P=N*30;
int lc[P],rc[P],val[P],rt[N],rtt,tot=0;
int n,k,m,aa[N],bb[N],a[N],b[N],t[N],vt[N*3],hs[N*3];

void build(int &o,int l,int r)
{
    o=++tot;
    if(l==r){val[o]=vt[l];return;}
    int mid=(l+r)/2;
    build(lc[o],l,mid);
    build(rc[o],mid+1,r);
    val[o]=max(val[lc[o]],val[rc[o]]);
}

void insert(int &o,int p,int l,int r,int k)
{
    val[o=++tot]=val[p]+1;
    lc[o]=lc[p];rc[o]=rc[p];
    if(l==r) return;
    int mid=(l+r)/2;
    if(k<=mid) insert(lc[o],lc[p],l,mid,k);
    else insert(rc[o],rc[p],mid+1,r,k);
}

int query(int o,int l,int r,int nl,int nr)
{
    if(l>=nl&&r<=nr) return val[o];
    int mid=(l+r)/2,res=0;
    if(nl<=mid) res+=query(lc[o],l,mid,nl,nr);
    if(nr>mid) res+=query(rc[o],mid+1,r,nl,nr);
    return res;
}

int qmax(int o,int l,int r,int nl,int nr)
{
    if(nl>nr) return 0;
    if(l>=nl&&r<=nr) return val[o];
    int mid=(l+r)/2,res=0;
    if(nl<=mid) res=max(res,qmax(lc[o],l,mid,nl,nr));
    if(nr>mid) res=max(res,qmax(rc[o],mid+1,r,nl,nr));
    return res;
}

int gao(int x)
{
    int r=qmax(rtt,1,m,a[x],b[x]-1);
    int cnt=query(rt[max(r,1)],1,m,b[x],m);
    if(!r) return (cnt&1)?bb[x]:aa[x];
    return hs[(cnt&1)?a[x]:b[x]];
}

int main()
{
    scanf("%d%d",&n,&k);
    for(int i=1;i<=n;i++)
    {
        scanf("%d%d",aa+i,bb+i);
        a[i]=min(aa[i],bb[i]);
        b[i]=max(aa[i],bb[i]);
        hs[++m]=a[i];
        hs[++m]=b[i];
    }
    for(int i=1;i<=k;i++)
        scanf("%d",t+i),hs[++m]=t[i];
    sort(hs+1,hs+1+m);
    m=unique(hs+1,hs+1+m)-(hs+1);
    for(int i=1;i<=n;i++)
    {
        a[i]=lower_bound(hs+1,hs+1+m,a[i])-hs;
        b[i]=lower_bound(hs+1,hs+1+m,b[i])-hs;
    }
    for(int i=k;i>=1;i--)
    {
        t[i]=lower_bound(hs+1,hs+1+m,t[i])-hs;
        insert(rt[i],rt[i+1],1,m,t[i]);
        if(!vt[t[i]]) vt[t[i]]=i;
    }
    build(rtt,1,m);
    long long ans=0;
    for(int i=1;i<=n;i++) ans+=gao(i);
    printf("%lld\n",ans);
    return 0;
}