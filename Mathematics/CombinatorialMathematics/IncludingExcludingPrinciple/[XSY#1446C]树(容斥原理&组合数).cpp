#include<bits/stdc++.h>
using namespace std;
 
const int ha=998244353;
const int N=20000010;
int fac[N],ifac[N],n,m;
 
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
    cin>>n>>m;
    n--;Init(n<<1);
    long long ans=C(n<<1,n);
    for(int i=0;i<n;i+=m)
    {
        ans-=C(n<<1,n+i+1);
        ans-=C(n<<1,n+i+m-1);
        ans+=C(n<<1,n+i+m)<<1;
    }
    ans=(ans%ha+ha)%ha;
    cout<<ans<<endl;
    return 0;
}