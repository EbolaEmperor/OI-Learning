#include<bits/stdc++.h>
using namespace std;

const int N=450010;
int mn[N<<2],mnc[N<<2],tag[N<<2];
int n,m,a[N];
int mmp[N<<1],*cnt=mmp+N;
int T,M;

void maintain(int o)
{
    mnc[o]=0;
    mn[o]=min(mn[o<<1],mn[o<<1|1]);
    if(mn[o<<1]==mn[o]) mnc[o]+=mnc[o<<1];
    if(mn[o<<1|1]==mn[o]) mnc[o]+=mnc[o<<1|1];
}

void pushdown(int o)
{
    if(!tag[o]) return;
    mn[o<<1]+=tag[o];
    tag[o<<1]+=tag[o];
    mn[o<<1|1]+=tag[o];
    tag[o<<1|1]+=tag[o];
    tag[o]=0;
}

void build(int o,int l,int r)
{
    mn[o]=0;
    mnc[o]=r-l+1;
    if(l==r) return;
    int mid=(l+r)/2;
    build(o<<1,l,mid);
    build(o<<1|1,mid+1,r);
}

void update(int o,int l,int r,int nl,int nr,int x)
{
    if(nl<1||nr>M||nl>nr) return;
    if(l>=nl&&r<=nr){mn[o]+=x;tag[o]+=x;return;}
    int mid=(l+r)/2;pushdown(o);
    if(nl<=mid) update(o<<1,l,mid,nl,nr,x);
    if(nr>mid) update(o<<1|1,mid+1,r,nl,nr,x);
    maintain(o);
}

int query(int o,int l,int r,int nl,int nr)
{
    if(mn[o]>0) return 0;
    if(l>=nl&&r<=nr) return mnc[o];
    int mid=(l+r)/2,res=0;pushdown(o);
    if(nl<=mid) res+=query(o<<1,l,mid,nl,nr);
    if(nr>mid) res+=query(o<<1|1,mid+1,r,nl,nr);
    return res;
}

int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++) scanf("%d",a+i);
    for(int i=1;i<=n;i++) cnt[a[i]]++;
    T=max(n,m);M=max(n,m)+n+m+2;
    build(1,1,M);
    int p,x;
    for(int i=1;i<=n;i++)
        for(int j=0;j<cnt[i];j++)
            update(1,1,M,i-j+T,i-j+T,1);
    int move=0;
    while(m--)
    {
        scanf("%d%d",&p,&x);
        if(p==0&&x>0)
        {
            update(1,1,M,-move-cnt[-move]+1+T,-move+T,1);
            update(1,1,M,n-move-cnt[n-move]+1+T,n-move+T,-1);
            move++;
        }
        else if(p==0&&x<0)
        {
            move--;
            update(1,1,M,-move-cnt[-move]+1+T,-move+T,-1);
            update(1,1,M,n-move-cnt[n-move]+1+T,n-move+T,1);
        }
        else
        {
            x-=move;
            if(a[p]+move>=1&&a[p]+move<=n)
                update(1,1,M,a[p]-cnt[a[p]]+1+T,a[p]-cnt[a[p]]+1+T,-1);
            cnt[a[p]]--;a[p]=x;cnt[a[p]]++;
            update(1,1,M,a[p]-cnt[a[p]]+1+T,a[p]-cnt[a[p]]+1+T,1);
        }
        printf("%d\n",query(1,1,M,T-move+1,T-move+n));
    }
    return 0;
}