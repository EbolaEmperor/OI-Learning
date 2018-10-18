#include<bits/stdc++.h>
#define lowbit(x) (x&-x)
using namespace std;
 
typedef long long LL;
struct Node
{
    int lc,rc;
    int s;
    Node(){lc=rc=0;s=0;}
} nd[10000010];
int root[100010],sz=0;
int a[100010],c[100010],n,m;
int lb[100010],rs[100010],pos[100010];
int nl,nr;
 
void add(int p){for(int i=p;i<=n;i+=lowbit(i)) c[i]++;}
int sum(int p){int res=0;for(int i=p;i>0;i-=lowbit(i)) res+=c[i];return res;}
 
void insert(int &o,int l,int r,int x)
{
    if(!o) o=++sz;
    nd[o].s++;
    if(l==r) return;
    int mid=(l+r)/2;
    if(x<=mid) insert(nd[o].lc,l,mid,x);
    else insert(nd[o].rc,mid+1,r,x);
}
 
LL query(int o,int l,int r)
{
    if(l>=nl&&r<=nr) return nd[o].s;
    LL res=0;
    int mid=(l+r)/2;
    if(nl<=mid) res+=query(nd[o].lc,l,mid);
    if(nr>mid) res+=query(nd[o].rc,mid+1,r);
    return res;
}
 
LL find(int l,int r)
{
    if(nl>nr) return 0;
    LL ans=0;
    for(int i=r;i>0;i-=lowbit(i))
        ans+=query(root[i],1,n);
    for(int i=l;i>0;i-=lowbit(i))
        ans-=query(root[i],1,n);
    return ans;
}
 
int main()
{
    cin>>n>>m;
    LL ans=0;
    int x,y;
    for(int i=1;i<=n;i++)
    {
        scanf("%d",a+i);
        pos[a[i]]=i;
        lb[i]=sum(n)-sum(a[i]);
        ans+=lb[i];
        add(a[i]);
    }
    memset(c,0,sizeof(c));
    for(int i=n;i>=1;i--){rs[i]=sum(a[i]);add(a[i]);}
    for(int i=1;i<=m;i++)
    {
        printf("%lld\n",ans);
        scanf("%d",&x);
        y=pos[x];
        ans-=lb[y]+rs[y];
        nl=x+1;nr=n;
		ans+=find(0,y);
		nl=1;nr=x-1;
		ans+=find(y,n);
        for(int i=y;i<=n;i+=lowbit(i))
            insert(root[i],1,n,x);
    }
    return 0;
}
