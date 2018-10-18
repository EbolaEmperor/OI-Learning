#include<bits/stdc++.h>
using namespace std;

const int N=20010,P=N<<5;
int root[N],lc[P],rc[P],tot=0;
int lmx[P],rmx[P],sum[P];
int qry[4],a[N],idx[N],n;

void maintain(int o)
{
    sum[o]=sum[lc[o]]+sum[rc[o]];
    lmx[o]=max(lmx[lc[o]],sum[lc[o]]+lmx[rc[o]]);
    rmx[o]=max(rmx[rc[o]],sum[rc[o]]+rmx[lc[o]]);
}

void copynode(int o,int p)
{
    sum[o]=sum[p];
    lmx[o]=lmx[p];
    rmx[o]=rmx[p];
    lc[o]=lc[p];
    rc[o]=rc[p];
}

void build(int &o,int l,int r)
{
    o=++tot;
    sum[o]=lmx[o]=rmx[o]=r-l+1;
    if(l==r) return;
    int mid=(l+r)/2;
    build(lc[o],l,mid);
    build(rc[o],mid+1,r);
}

void modify(int &o,int p,int l,int r,int k)
{
    o=++tot;
    if(l==r){sum[o]=lmx[o]=rmx[o]=-1;return;}
    int mid=(l+r)/2;copynode(o,p);
    if(k<=mid) modify(lc[o],lc[p],l,mid,k);
    else modify(rc[o],rc[p],mid+1,r,k);
    maintain(o);
}

int qsum(int o,int l,int r,int nl,int nr)
{
    if(nl>nr) return 0;
    if(l>=nl&&r<=nr) return sum[o];
    int mid=(l+r)/2;int res=0;
    if(nl<=mid) res+=qsum(lc[o],l,mid,nl,nr);
    if(nr>mid) res+=qsum(rc[o],mid+1,r,nl,nr);
    return res;
}

int qlmx(int o,int l,int r,int nl,int nr)
{
    if(l==nl&&r==nr) return lmx[o];
    int mid=(l+r)/2;
    if(nr<=mid) return qlmx(lc[o],l,mid,nl,nr);
    else if(nl>mid) return qlmx(rc[o],mid+1,r,nl,nr);
    else return max(qlmx(lc[o],l,mid,nl,mid),qsum(lc[o],l,mid,nl,mid)+qlmx(rc[o],mid+1,r,mid+1,nr));
}

int qrmx(int o,int l,int r,int nl,int nr)
{
    if(l==nl&&r==nr) return rmx[o];
    int mid=(l+r)/2;
    if(nr<=mid) return qrmx(lc[o],l,mid,nl,nr);
    else if(nl>mid) return qrmx(rc[o],mid+1,r,nl,nr);
    else return max(qrmx(rc[o],mid+1,r,mid+1,nr),qsum(rc[o],mid+1,r,mid+1,nr)+qrmx(lc[o],l,mid,nl,mid));
}

bool check(int x)
{
    int a=qry[0],b=qry[1],c=qry[2],d=qry[3];
    int res=qsum(root[x],1,n,b+1,c-1);
    res+=qrmx(root[x],1,n,a,b);
    res+=qlmx(root[x],1,n,c,d);
    return res>=0;
}

int main()
{
    //freopen("4.in","r",stdin);
    //freopen("my.out","w",stdout);
    int ans=0,Q;
    scanf("%d",&n);
    build(root[1],1,n);
    for(int i=1;i<=n;i++) scanf("%d",a+i),idx[i]=i;
    sort(idx+1,idx+1+n,[](int x,int y){return a[x]<a[y];});
    for(int i=2;i<=n;i++) modify(root[i],root[i-1],1,n,idx[i-1]);
    scanf("%d",&Q);
    while(Q--)
    {
        for(int i=0;i<4;i++)
        {
            scanf("%d",qry+i);
            qry[i]=(qry[i]+ans)%n+1;
        }
        sort(qry,qry+4);
        int l=1,r=n,mid;
        while(l<=r)
        {
            mid=(l+r)/2;
            if(check(mid)) l=mid+1,ans=a[idx[mid]];
            else r=mid-1;
        }
        printf("%d\n",ans);
    }
    return 0;
}