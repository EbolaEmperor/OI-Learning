#include<bits/stdc++.h>
using namespace std;

const int N=500010;
int mn[N<<2],tag[N<<2];
int n,a[N],cnt[N],used[N];
int fa[N],sz[N],ans[N];
bool fuck[N];

void pushdown(int o)
{
    if(!tag[o]) return;
    mn[o<<1]+=tag[o];
    mn[o<<1|1]+=tag[o];
    tag[o<<1]+=tag[o];
    tag[o<<1|1]+=tag[o];
    tag[o]=0;
}

void build(int o,int l,int r)
{
    if(l==r){mn[o]=l;return;}
    int mid=(l+r)/2;
    build(o<<1,l,mid);
    build(o<<1|1,mid+1,r);
    mn[o]=min(mn[o<<1],mn[o<<1|1]);
}

void add(int o,int l,int r,int nl,int nr,int x)
{
    if(l>=nl&&r<=nr)
    {
        mn[o]+=x;tag[o]+=x;
        return;
    }
    int mid=(l+r)/2;
    pushdown(o);
    if(nl<=mid) add(o<<1,l,mid,nl,nr,x);
    if(nr>mid) add(o<<1|1,mid+1,r,nl,nr,x);
    mn[o]=min(mn[o<<1],mn[o<<1|1]);
}

int query(int o,int l,int r,int k)
{
    if(l==r) return mn[o]>=k?l:l+1;
    int mid=(l+r)/2;
    pushdown(o);
    if(mn[o<<1|1]>=k) return query(o<<1,l,mid,k);
    else return query(o<<1|1,mid+1,r,k);
}

int main()
{
    double k;
    scanf("%d%lf",&n,&k);
    for(int i=1;i<=n;i++)
    {
        scanf("%d",a+i);
        fa[i]=(int)floor(i/k);
        sz[i]=1;
    }
    for(int i=n;i>=1;i--) sz[fa[i]]+=sz[i];
    sort(a+1,a+1+n,[](int x,int y){return x>y;});
    for(int i=n;i>=1;i--)
        cnt[i]=(a[i+1]==a[i])?(cnt[i+1]+1):1;
    build(1,1,n);
    for(int i=1;i<=n;i++)
    {
        if(fa[i]&&!fuck[fa[i]])
        {
            add(1,1,n,ans[fa[i]],n,sz[fa[i]]-1);
            fuck[fa[i]]=1;
        }
        int x=query(1,1,n,sz[i]);
        x+=cnt[x]-1;used[x]++;
        ans[i]=(x-=used[x]-1);
        add(1,1,n,x,n,-sz[i]);
    }
    for(int i=1;i<=n;i++)
        printf("%d ",a[ans[i]]);
    return 0;
}