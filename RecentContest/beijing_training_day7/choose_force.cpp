#include<bits/stdc++.h>
using namespace std;

const int ha=998244353,N=1050;
int n,k,s,a[N];

namespace Task1
{
    int ans=0;
    void dfs(int d,int c,int gcd,int xorsum)
    {
        if(d==k+1)
        {
            if(xorsum==s) ans=(ans+gcd)%ha;
            return;
        }
        for(int i=c+1;i<=n;i++)
            dfs(d+1,i,__gcd(gcd,a[i]),xorsum^a[i]);
    }
    int main()
    {
        dfs(1,0,0,0);
        printf("%d\n",ans);
        return 0;
    }
}

namespace Task2
{
    int sum[N][N];
    int main()
    {
        for(int i=1;i<=n;i++)
        {
            memcpy(sum[i],sum[i-1],sizeof(sum[i]));
            sum[i][a[i]]++;
        }
        int ans=0;
        for(int i=1;i<=n;i++)
            for(int j=1;j<i;j++)
            {
                int xorsum=a[i]^a[j],gcd=__gcd(__gcd(a[i],a[j]),s^xorsum);
                ans=(ans+1ll*sum[j-1][s^xorsum]*gcd)%ha;
            }
        printf("%d\n",ans);
        return 0;
    }
}

namespace Task3
{
    long long sum[N][N];
    int gcd[N][N];
    int main()
    {
        for(int i=1;i<=1024;i++)
            for(int j=1;j<=1024;j++)
                gcd[i][j]=__gcd(i,j);
        for(int i=1;i<=n;i++)
        {
            memcpy(sum[i],sum[i-1],sizeof(sum[i]));
            sum[i][a[i]]++;
        }
        long long ans=0;
        for(int i=1;i<=n;i++)
            for(int j=1;j<i;j++)
                for(int k=1;k<j;k++)
                {
                    int xorsum=a[i]^a[j]^a[k],g=gcd[gcd[a[i]][a[j]]][gcd[a[k]][s^xorsum]];
                    ans+=sum[k-1][s^xorsum]*g;
                }
        printf("%lld\n",ans%ha);
        return 0;
    }
}

int main()
{
    freopen("choose3.in","r",stdin);
    scanf("%d%d%d",&n,&k,&s);
    for(int i=1;i<=n;i++) scanf("%d",a+i);
    if(n<=40||(n<=1000&&k<=2)) return Task1::main();
    else if(k==3) return Task2::main();
    else return Task3::main();
}
