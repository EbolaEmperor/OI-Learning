#include<bits/stdc++.h>
using namespace std;

typedef long double LD;
const int N=200010,P=N*60;
int lc[P],rc[P],sz[P],rt[N],rev[N],tot=0,n,m;
LD sum[P];

void maintain(int o)
{
    sz[o]=sz[lc[o]]+sz[rc[o]];
    sum[o]=sum[lc[o]]+sum[rc[o]];
}

void insert(int &o,int l,int r,int k)
{
    sz[o=++tot]=1;
    sum[o]=log10((LD)k);
    if(l==r) return;
    int mid=(l+r)/2;
    if(k<=mid) insert(lc[o],l,mid,k);
    else insert(rc[o],mid+1,r,k);
}

LD qsum1(int o,int l,int r,int k)
{
    if(k<=0) return 0;
    if(sz[o]<=k) return sum[o];
    if(l==r) return log10((LD)l)*k;
    int mid=(l+r)/2;LD sum=0;
    sum+=qsum1(rc[o],mid+1,r,k-sz[lc[o]]);
    sum+=qsum1(lc[o],l,mid,k);
    return sum;
}

LD qsum2(int o,int l,int r,int k)
{
    if(k<=0) return 0;
    if(sz[o]<=k) return sum[o];
    if(l==r) return log10((LD)l)*k;
    int mid=(l+r)/2;LD sum=0;
    sum+=qsum2(lc[o],l,mid,k-sz[rc[o]]);
    sum+=qsum2(rc[o],mid+1,r,k);
    return sum;
}

int merge(int p1,int p2,int l,int r)
{
    if(!p1||!p2) return p1|p2;
    if(l==r){sum[p1]+=sum[p2];sz[p1]+=sz[p2];return p1;}
    int mid=(l+r)/2;
    lc[p1]=merge(lc[p1],lc[p2],l,mid);
    rc[p1]=merge(rc[p1],rc[p2],mid+1,r);
    maintain(p1);
    return p1;
}

void split1(int &o,int &p,int l,int r,int k)
{
    if(k<=0){o=0;return;}
    if(sz[p]<=k){o=p,p=0;return;}
    if(l==r)
    {
        sz[p]-=k;
        sz[o=++tot]=k;
        sum[o]=log10((LD)l)*k;
        sum[p]-=sum[o];
        return;
    }
    int mid=(l+r)/2;o=++tot;
    split1(rc[o],rc[p],mid+1,r,k-sz[lc[p]]);
    split1(lc[o],lc[p],l,mid,k);
    maintain(o);maintain(p);
}

void split2(int &o,int &p,int l,int r,int k)
{
    if(k<=0){o=0;return;}
    if(sz[p]<=k){o=p,p=0;return;}
    if(l==r)
    {
        sz[p]-=k;
        sz[o=++tot]=k;
        sum[o]=log10((LD)l)*k;
        sum[p]-=sum[o];
        return;
    }
    int mid=(l+r)/2;o=++tot;
    split2(lc[o],lc[p],l,mid,k-sz[rc[p]]);
    split2(rc[o],rc[p],mid+1,r,k);
    maintain(o);maintain(p);
}

LD val[N<<2];
set<int> rts;

void build(int o,int l,int r)
{
    if(l==r){val[o]=sum[rt[l]];return;}
    int mid=(l+r)/2;
    build(o<<1,l,mid);
    build(o<<1|1,mid+1,r);
    val[o]=val[o<<1]+val[o<<1|1];
}

void update(int o,int l,int r,int k,LD v)
{
    if(l==r){val[o]=v;return;}
    int mid=(l+r)/2;
    if(k<=mid) update(o<<1,l,mid,k,v);
    else update(o<<1|1,mid+1,r,k,v);
    val[o]=val[o<<1]+val[o<<1|1];
}

LD qsum(int o,int l,int r,int nl,int nr)
{
    if(nl>nr) return 0;
    if(l>=nl&&r<=nr) return val[o];
    int mid=(l+r)/2;LD res=0;
    if(nl<=mid) res+=qsum(o<<1,l,mid,nl,nr);
    if(nr>mid) res+=qsum(o<<1|1,mid+1,r,nl,nr);
    return res;
}

int query(int l,int r)
{
    int rt1=*(--rts.lower_bound(l));
    int rt2=*(--rts.upper_bound(r));
    if(rt1==rt2)
    {
        LD ans=rev[rt1]?qsum2(rt[rt1],1,n,r-rt1+1):qsum1(rt[rt1],1,n,r-rt1+1);
        ans-=rev[rt1]?qsum2(rt[rt1],1,n,l-rt1):qsum1(rt[rt1],1,n,l-rt1);
        return (int)(pow(10,ans-floor(ans))+1e-9);
    }
    LD ans=qsum(1,1,n,max(rt1+sz[rt[rt1]],1),rt2-1);
    if(!rev[rt1]) ans+=qsum2(rt[rt1],1,n,sz[rt[rt1]]-(l-rt1));
    else ans+=qsum1(rt[rt1],1,n,sz[rt[rt1]]-(l-rt1));
    if(!rev[rt2]) ans+=qsum1(rt[rt2],1,n,r-rt2+1);
    else ans+=qsum2(rt[rt2],1,n,r-rt2+1);
    return (int)(pow(10,ans-floor(ans))+1e-9);
}

void sort(int l,int r,int x)
{
    int rt1=*(--rts.lower_bound(l));
    int rt2=*(--rts.upper_bound(r)),nrt=0,nrt2=0;
    if(rt1==rt2)
    {
        if(!rev[rt1]) split2(rt[l],rt[rt1],1,n,sz[rt[rt1]]-(l-rt1));
        else split1(rt[l],rt[rt1],1,n,sz[rt[rt1]]-(l-rt1));
        rev[l]=x^1;rts.insert(l);
        update(1,1,n,rt1,sum[rt[rt1]]);
        update(1,1,n,l,sum[rt[l]]);
        if(l+sz[rt[l]]-1==r) return;
        if(!rev[rt1]) split2(rt[r+1],rt[l],1,n,sz[rt[l]]-(r-l+1));
        else split1(rt[r+1],rt[l],1,n,sz[rt[l]]-(r-l+1));
        rev[r+1]=rev[rt1];rts.insert(r+1);
        update(1,1,n,r+1,sum[rt[r+1]]);
        update(1,1,n,l,sum[rt[l]]);
        return;
    }
    if(!rev[rt1]) split2(nrt,rt[rt1],1,n,sz[rt[rt1]]-(l-rt1));
    else split1(nrt,rt[rt1],1,n,sz[rt[rt1]]-(l-rt1));
    if(!rev[rt2]) split2(nrt2,rt[rt2],1,n,sz[rt[rt2]]-(r-rt2+1));
    else split1(nrt2,rt[rt2],1,n,sz[rt[rt2]]-(r-rt2+1));
    if(nrt2)
    {
        rt[r+1]=nrt2;
        rev[r+1]=rev[rt2];
        rts.insert(r+1);
        update(1,1,n,r+1,sum[rt[r+1]]);
    }
    update(1,1,n,rt1,sum[rt[rt1]]);
    update(1,1,n,rt2,0);
    for(auto it=rts.lower_bound(l);it!=rts.end()&&*it<=r;)
    {
        nrt=merge(nrt,rt[*it],1,n);
        update(1,1,n,*it,0);rt[*it]=0;
        auto tmp=it;it++;
        rts.erase(tmp);
    }
    rt[l]=nrt;rts.insert(l);
    update(1,1,n,l,sum[rt[l]]);
    rev[l]=x^1;
}

int main()
{
    scanf("%d%d",&n,&m);
    rts.insert(0);
    for(int i=1,x;i<=n;i++)
    {
        scanf("%d",&x);
        insert(rt[i],1,n,x);
        rts.insert(i);
    }
    build(1,1,n);
    int opt,l,r,x;
    while(m--)
    {
        scanf("%d%d%d",&opt,&l,&r);
        if(opt==2) printf("%d\n",query(l,r));
        else scanf("%d",&x),sort(l,r,x);
    }
    return 0;
}