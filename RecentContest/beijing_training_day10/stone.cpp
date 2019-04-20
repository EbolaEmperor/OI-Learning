#include<bits/stdc++.h>
using namespace std;

typedef long long LL;
const int N=500010;
LL sum[N<<2],smin[N<<2],smax[N<<2];
int n,q,X,Y,s,b[N];

void mdf(int o,int p)
{
    sum[o]=b[p];
    smin[o]=min(b[p],0);
    smax[o]=max(b[p],0);
    return;
}

void maintain(int o)
{
    sum[o]=sum[o<<1]+sum[o<<1|1];
    smin[o]=min(smin[o<<1],sum[o<<1]+smin[o<<1|1]);
    smax[o]=max(smax[o<<1],sum[o<<1]+smax[o<<1|1]);
}

void build(int o,int l,int r)
{
    if(l==r){mdf(o,l);return;}
    int mid=(l+r)/2;
    build(o<<1,l,mid);
    build(o<<1|1,mid+1,r);
    maintain(o);
}

void modify(int o,int l,int r,int k)
{
    if(l==r){mdf(o,l);return;}
    int mid=(l+r)/2;
    if(k<=mid) modify(o<<1,l,mid,k);
    else modify(o<<1|1,mid+1,r,k);
    maintain(o);
}

int merge(int o,int pre)
{
    int cur=pre;
    if(pre+smin[o]<=0) cur=-smin[o];
    if(pre+smax[o]>=s) cur=s-smax[o];
    return cur+sum[o];
}

int query(int o,int l,int r)
{
    if(l==r) return max(0,min(s,(int)sum[o]));
    int mid=(l+r)/2;
    if(smax[o<<1|1]-smin[o<<1|1]>=s) return query(o<<1|1,mid+1,r);
    else return merge(o<<1|1,query(o<<1,l,mid));
}

int main()
{
    scanf("%d%d%d%d",&n,&q,&X,&Y);
    s=X+Y;b[0]=X;
    for(int i=1;i<=n;i++)
        scanf("%d",b+i),b[i]=(i&1)?b[i]:-b[i];
    build(1,0,n);
    int opt,x,y;
    while(q--)
    {
        scanf("%d%d",&opt,&x);
        if(opt==1) X=x,s=X+Y,b[0]=X,modify(1,0,n,0);
        if(opt==2) Y=x,s=X+Y;
        if(opt==3)
        {
            scanf("%d",&y);
            b[x]=(x&1)?y:-y;
            modify(1,0,n,x);
        }
        printf("%d\n",query(1,0,n));
    }
    return 0;
}
