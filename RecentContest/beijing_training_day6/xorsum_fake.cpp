#include<bits/stdc++.h>
using namespace std;
 
typedef long long LL;
LL l,r;int T,n;
 
int main()
{
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d%lld%lld",&n,&l,&r);
        if(n==1) printf("%lld\n",r-l+1);
        else
        {
            long long ans=r-l+1;
            int k;
            for(k=60;k>=0;k--)
                if((r>>k)!=(l>>k)) break;
            long long tmp=max(r%(1ll<<k)+1,l%(1ll<<k));
            ans+=(1ll<<k)-tmp;
            printf("%lld\n",ans);
        }
    }
    return 0;
}
