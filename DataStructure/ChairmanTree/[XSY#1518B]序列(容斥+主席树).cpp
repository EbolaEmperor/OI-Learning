#include<bits/stdc++.h>
using namespace std;

typedef long long LL;
const int N=100010,P=N*40;
int rt[N],lc[P],rc[P],val[P],tot;
int n,m,a[N],sum[N];

void insert(int &o,int p,int l,int r,int x)
{
    val[o=++tot]=val[p]+1;
    lc[o]=lc[p];rc[o]=rc[p];
    if(l==r) return;
    int mid=(l+r)/2;
    if(x<=mid) insert(lc[o],lc[p],l,mid,x);
    else insert(rc[o],rc[p],mid+1,r,x);
}

int query(int L,int R,int l,int r,int x)
{
    if(l==r) return val[R]-val[L];
    int mid=(l+r)/2;
    if(x<=mid) return query(lc[L],lc[R],l,mid,x);
    return val[lc[R]]-val[lc[L]]+query(rc[L],rc[R],mid+1,r,x);
}

LL solve(int len,int x)
{
    LL res=0;
    tot=0;memset(rt,0,sizeof(rt));
    memset(lc,0,sizeof(lc));
    memset(rc,0,sizeof(rc));
    memset(val,0,sizeof(val));
    for(int i=1;i<=n;i++)
    {
        if(a[i]<=x) sum[i]=-1;
        else sum[i]=1;
        sum[i]+=sum[i-1];
        insert(rt[i],rt[i-1],0,n<<1,n+sum[i]);
    }
    for(int i=1;i<=n;i++)
        res+=query(rt[i-1],rt[min(i+len-1,n)],0,n<<1,n+sum[i-1]);
    return res;
}

int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++) scanf("%d",a+i);
    scanf("%d",&m);
    while(m--)
    {
        int l1,r1,l2,r2;
        scanf("%d%d%d%d",&l1,&r1,&l2,&r2);
        LL ans=solve(r2,r1);
        ans-=solve(l2-1,r1);
        ans-=solve(r2,l1-1);
        ans+=solve(l2-1,l1-1);
        printf("%lld\n",ans);
    }
    return 0;
}