#include<bits/stdc++.h>
using namespace std;

const int ha=998244353,qwq=828542813,N=2000010;
long long Ea[N],Ea2[N],Es[N],Es2[N],Esa[N],p[N];

int main()
{
    int n;scanf("%d",&n);
    for(int i=1;i<=n;i++)
    {
        scanf("%lld",p+i);
        p[i]=p[i]*qwq%ha;
        Ea[i]=p[i]*(Ea[i-1]+1)%ha;
        Es[i]=(Es[i-1]+Ea[i])%ha;
        Ea2[i]=p[i]*(Ea2[i-1]+Ea[i-1]*2+1)%ha;
        Esa[i]=p[i]*(Esa[i-1]+Es[i-1]+Ea2[i-1])%ha;
        Es2[i]=(Es2[i-1]+Ea2[i]+Esa[i]*2)%ha;
    }
    printf("%lld\n",Es2[n]);
    return 0;
}