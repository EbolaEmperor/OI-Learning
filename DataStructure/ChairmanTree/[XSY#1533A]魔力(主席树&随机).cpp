#include<bits/stdc++.h>
using namespace std;

typedef long long LL;
const int ha=1e9+7;
const int N=100010;
int sum[N*20],lc[N*20],rc[N*20],rt[N],tot=0;
int cnt=0,n,m;
char Hash[N],s[N];
LL val[300],hs[N];
LL presum[N];

void insert(int &o,int p,int l,int r,int k)
{
    sum[o=++tot]=sum[p]+1;
    lc[o]=lc[p];rc[o]=rc[p];
    if(l==r) return;
    int mid=(l+r)/2;
    if(k<=mid) insert(lc[o],lc[p],l,mid,k);
    else insert(rc[o],rc[p],mid+1,r,k);
}

int query(int L,int R,int l,int r,int k)
{
    if(l==r) return sum[R]-sum[L];
    int mid=(l+r)/2;
    if(k<=mid) return query(lc[L],lc[R],l,mid,k);
    else return query(rc[L],rc[R],mid+1,r,k);
}

int main()
{
    srand(19260817);
    scanf("%d%s",&n,s+1);
    for(int i=1;i<=n;i++) Hash[i]=s[i];
    sort(Hash+1,Hash+1+n);
    m=unique(Hash+1,Hash+1+n)-(Hash+1);
    for(int i=1;i<m;i++)
    {
        val[Hash[i]]=rand();
        val[Hash[m]]-=val[Hash[i]];
    }
    for(int i=1;i<=n;i++)
        hs[i]=presum[i]=presum[i-1]+val[s[i]];
    sort(hs+1,hs+2+n);
    m=unique(hs+1,hs+2+n)-(hs+1);
    presum[0]=lower_bound(hs+1,hs+1+m,presum[0])-hs;
    for(int i=1;i<=n;i++)
    {
        presum[i]=lower_bound(hs+1,hs+1+m,presum[i])-hs;
        insert(rt[i],rt[i-1],1,m,presum[i]);
    }
    LL ans=0;
    for(int i=0;i<n;i++)
        ans+=query(rt[i],rt[n],1,m,presum[i]);
    printf("%lld\n",ans%ha);
    return 0;
}