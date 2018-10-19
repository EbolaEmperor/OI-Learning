#include<bits/stdc++.h>
using namespace std;

const int ha=1000000007;
const int N=10000010;
bool vis[N];
int l,r,sum=0;
int fac[N],ifac[N];

int Pow(int a,int b)
{
    int ans=1;
    for(;b;b>>=1,a=1ll*a*a%ha)
        if(b&1) ans=1ll*ans*a%ha;
    return ans;
}

void Init(int n)
{
    fac[0]=1;
    for(int i=1;i<=n;i++)
        fac[i]=1ll*fac[i-1]*i%ha;
    ifac[n]=Pow(fac[n],ha-2);
    for(int i=n-1;i>=0;i--)
        ifac[i]=1ll*ifac[i+1]*(i+1)%ha;
}

inline int C(int n,int m){return n<m?0:1ll*fac[n]*ifac[m]%ha*ifac[n-m]%ha;}

int main()
{
    cin>>l>>r;Init(r);
    for(int i=l;i<=r;i++)
    {
        if(vis[i]) continue;
        sum++;
        for(int j=i;j<=r;j+=i)
            vis[j]=1;
    }
    int ans=0,n=r-l+1;
    for(int i=1;i<=n;i++)
    {
        int res=1ll*i*sum%ha;
        res=1ll*res*C(n-sum,n-i)%ha;
        res=1ll*res*fac[n-i]%ha;
        res=1ll*res*fac[i-1]%ha;
        ans=(ans+res)%ha;
    }
    cout<<ans<<endl;
    return 0;
}