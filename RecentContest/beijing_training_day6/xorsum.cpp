#include<bits/stdc++.h>
using namespace std;

typedef long long LL;
typedef pair<LL,LL> pll;
pll nmsl[3];
LL l,r;
int T,n;

LL merge(int tot)
{
    sort(nmsl,nmsl+tot);
    LL ans=0,cur=0;
    for(int i=0;i<tot;i++)
        if(nmsl[i].second>=cur)
        {
            ans+=nmsl[i].second-max(cur,nmsl[i].first)+1;
            cur=nmsl[i].second+1;
        }
    return ans;
}

int main()
{
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d%lld%lld",&n,&l,&r);
        if(n==1||l==r) printf("%lld\n",r-l+1);
        else
        {
            int k,tot=0;
            LL lcp=0;
            nmsl[tot++]=pll(l,r);
            for(k=60;k>=0;k--)
                if((r>>k)!=(l>>k)) break;
            lcp=r>>k+1;
            LL lcp1=(lcp<<1|1)<<k;
            r%=(1ll<<k);l%=(1ll<<k);
            nmsl[tot++]=pll(lcp1+l,lcp1+(1ll<<k)-1);
            int nxt=k-1;
            for(;nxt>=0;nxt--)
                if((r>>nxt)&1) break;
            if(nxt>=0) nmsl[tot++]=pll(lcp1,lcp1+(1ll<<nxt+1)-1);
            printf("%lld\n",merge(tot));
        }
    }
    return 0;
}
